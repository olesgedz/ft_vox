#version 410 core

out vec4 color;

in vec3 vTexCoords;

uniform samplerCube skybox;

void main()
{
	color = texture(skybox, vTexCoords);
}