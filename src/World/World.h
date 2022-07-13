//
// Created by Jeromy Black on 1/7/21.
//

#ifndef FT_VOX_WORLD_H
#define FT_VOX_WORLD_H
#include <unordered_map>
#include <memory>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"
#include <thread>
#include "Chunk.h"
#include "camera.h"
#include "Resources.h"

class World
{
	public:
		int radius = 7;
		int octaves = 0;
		float scale1 = 0.2f;
		float scale2 = 0.267f;
		float scale3 = 0.130f;
		int seed = 1337;
		bool need_render = true;
	std::unordered_map<vec3, shared_ptr<Chunk>> world;
		Camera * player_cam;
		glm::vec3 last_player_position = vec3(0,0,0);
		Shader * shader;
		World(World const&) = delete;
		World& operator=(World const&) = delete;
		static std::shared_ptr<World> instance()
		{
			static std::shared_ptr<World> s{new World};
			return s;
		}

		bool NeedRender()
		{
			return(need_render);
		}

		void UpdateWorld()
		{
			vec3 pos  = vec3(int(player_cam->Position.x), int(player_cam->Position.y), int(player_cam->Position.z));
			last_player_position = pos;
			int r_c = radius * 16;
			std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			vec3 pos_start = vec3(pos.x - r_c, pos.y, pos.z - r_c);
			vec3 pos_finish = vec3(pos.x + r_c, pos.y, pos.z + r_c);
            int num =  pos_finish.x - pos_start.x;
            num = num / 4;
            int start = pos_start.x;
			for (;pos_start.x <  pos_finish.x; )
			{
				pos_start.z = pos.z - r_c;
             //   std::thread t1(&World::Rebuild, this, pos_start,  vec3{pos_start.x + num, pos_start.y + num, pos_start.z + num});
                Rebuild(pos_start, pos_finish);
                pos_start.x+=16;
                pos_start.z+=16;
            }
            num += num;
		}

        void Rebuild(vec3 pos_start, vec3 pos_finish) {
                vec3 pos_count = pos_start;
                int n = (pos_finish.z - pos_count.z) / 4;
                for (;pos_count.z < pos_finish.z; pos_count.z += 16) {
                    world.insert(std::pair<vec3, std::shared_ptr<Chunk>>(pos_count,
                                                                         new Chunk(vec3(pos_count.x, 0, pos_count.z))));
                }
            pos_count = pos_start;

            for ( ;pos_count.z < pos_finish.z; ) // Z
            {
//                shared_ptr<Chunk> c = world[pos_count];
//                std::thread t1(&Chunk::generate, world[pos_count]);
//                std::thread t2(&Chunk::generate, world[{pos_count.x, pos_count.y, pos_count.z + 16}]);
//                std::thread t3(&Chunk::generate, world[{pos_count.x, pos_count.y, pos_count.z + 32}]);
//                std::thread t4(&Chunk::generate, world[{pos_count.x, pos_count.y, pos_count.z + 48}]);
//                t1.join();
//                t2.join();
//                t3.join();
//                t4.join();
//                pos_count.z+=16 * 4;

                shared_ptr<Chunk> c = world[pos_count];
                c->generate();
                pos_count.z+=16;
            }

                pos_count = pos_start;
	            for ( ;pos_count.z < pos_finish.z; ) // Z
				{
					shared_ptr<Chunk> c = world[pos_count];
					c->model.meshes[0].bind_shader(shader);
					c->model.meshes[0].shader->use();
					c->model.meshes[0].texture = texture;
					c->model.meshes[0].upload();
                    pos_count.z+=16;
				}
        }
private:
	World() {
        string pathVertex = (Resources::getCurrentPath() / "shaders/SimpleVertex.glsl").string();
        string pathFragment = (Resources::getCurrentPath() / "shaders/SimpleFragment.glsl").string();
        shader =  new Shader(pathVertex.c_str(), pathFragment.c_str());
		shader->use();
		glGenTextures(1, &this->texture);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        string pathAtlas = (Resources::getCurrentPath() / filename).string();
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(pathAtlas.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		//stbi_image_free(data);
		}
    std::array<std::unique_ptr<std::thread>, 4> threads;
	GLuint texture;
	string filename = "resources/textures/spritesheet.png";
	int width, height, nrChannels;
	unsigned char *data ;
};

#endif //FT_VOX_WORLD_H
