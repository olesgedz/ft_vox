//
// Created by Jeromy Black on 12/21/20.
//

#ifndef FT_VOX_MESH_H
#define FT_VOX_MESH_H

#include <string>
#include <vector>
#include "glm/gtx/string_cast.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad.h"
#include "Shader.h"
using namespace std;
using namespace glm;


struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh {
private:
	GLuint vbo_vertices, vbo_normals, vbo_uvs, ibo_elements;
public:
	vector<Texture> textures;
	GLuint voa, ebo;
	GLuint texture;
	GLint textureExists;
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;
	vector<glm::vec3> temp_vertices;
	vector<glm::vec3> temp_normals;
	vector<glm::vec2> temp_uvs;
	Shader *shader;
	vector<GLushort> elements;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	glm::mat4 object2world;
	Mesh() : vbo_vertices(0), vbo_normals(0), ibo_elements(0),vbo_uvs(0), object2world(glm::mat4(1)) {
		this->textureExists = 0;
	}
	Mesh(vector<glm::vec3> vertices, vector<glm::vec3> normals, vector<glm::vec2> uvs) : vbo_vertices(0),
	vbo_normals(0), ibo_elements(0),vbo_uvs(0), object2world(glm::mat4(1)),
	vertices(vertices),normals(normals),uvs(uvs)
	{
		this->textureExists = 0;
	}

	Mesh(vector<glm::vec3> vertices) : vbo_vertices(0),
	vbo_normals(0), ibo_elements(0),vbo_uvs(0), object2world(glm::mat4(1)),
	vertices(vertices)
	{
		this->textureExists = 0;
	}


	~Mesh() {
		if (vbo_vertices != 0)
			glDeleteBuffers(1, &vbo_vertices);
		if (vbo_normals != 0)
			glDeleteBuffers(1, &vbo_normals);
		if (ibo_elements != 0)
			glDeleteBuffers(1, &ibo_elements);
	}
	/**
	* Draw the object
	*/
	void draw();
	void bind_shader(Shader *shader);
	bool load_texture(const char *filename);

	bool bind_texture();

	bool load_obj(const char *filename);


	/**
	 * Store object vertices, normals and/or elements in graphic card
	 * buffers
	 */
	void upload();


	/**
	 * Draw object bounding box
	 */
	void draw_bbox();

};


#endif //FT_VOX_MESH_H
