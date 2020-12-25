#version 330 core

out vec4 colour;
in vec4 aPos;
in vec3 aNormal;
in vec2 aTextureCoord;
uniform sampler2D ourTexture;
void main()
{
	colour = texture(ourTexture, aTextureCoord);
}