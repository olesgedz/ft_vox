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

#include "Chunk.h"
#include "camera.h"

class World
{
	public:
		int radius = 3;
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



		void UpdateWorld()
		{
			vec3 pos  = vec3(int(player_cam->Position.x), int(player_cam->Position.y), int(player_cam->Position.z));
			last_player_position = pos;
			int r_c = radius * 16;
			std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			vec3 pos_start = vec3(pos.x - r_c, pos.y, pos.z - r_c);
			vec3 pos_finish = vec3(pos.x + r_c, pos.y, pos.z + r_c);
			for (;pos_start.x < pos_finish.x; )
			{
				pos_start.z = pos.z - r_c;
				for ( ;pos_start.z < pos_finish.z; ) // Z
				{
					world.insert(std::pair<vec3, std::shared_ptr<Chunk>>(pos_start, new Chunk(vec3(pos_start.x, 0, pos_start.z))));
					shared_ptr<Chunk> c = world[pos_start];
					c->generate();
					c->model.meshes[0].bind_shader(shader);
					c->model.meshes[0].shader->use();



					//c->model.meshes[0].load_texture("resources/textures/spritesheet.png");//("resources/textures/Test.png");
//					c->model.meshes[0].bind_texture();
					c->model.meshes[0].texture = texture;
					c->model.meshes[0].upload();
					pos_start.z+=16;
				}
				pos_start.x+=16;

			}
		}
private:
	World() {
		shader =  new Shader("shaders/SimpleVertex.glsl", "shaders/SimpleFragment.glsl");
		shader->use();
		glGenTextures(1, &this->texture);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//		int width, height, nrChannels;
		string s;
		s.append("./");
		s.append(filename);
		stbi_set_flip_vertically_on_load(true);
		cout <<filename <<endl;
		data = stbi_load(s.c_str(), &width, &height, &nrChannels, 0);
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
	GLuint texture;
	string filename = "resources/textures/spritesheet.png";
	int width, height, nrChannels;
	unsigned char *data ;
};

#endif //FT_VOX_WORLD_H
