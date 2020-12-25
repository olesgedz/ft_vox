#version 330 core

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTexturePosition;
layout (location = 2) in vec3 inNormals;


uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;
out vec4 aPos;
out vec3 aNormal;
out vec2 aTextureCoord;
void main()
{
	gl_Position = projMatrix *
	viewMatrix *
	modelMatrix *
	vec4 (inVertexPosition.x, inVertexPosition.y, inVertexPosition.z, 1.0);

	aNormal = mat3(transpose(inverse(viewMatrix * modelMatrix))) * inNormals;
	aTextureCoord = inTexturePosition;
	aPos = gl_Position;
}