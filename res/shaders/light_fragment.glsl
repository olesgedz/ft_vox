#version 410 core

out vec4 color;

in vec4 vColor;

uniform sampler2D ourTexture;

void main()
{
	color = vColor;
}