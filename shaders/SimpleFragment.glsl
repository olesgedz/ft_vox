#version 330 core

out vec4 colour;
in vec2 aUV;
uniform sampler2D texture1;

void main()
{
    colour =  texture(texture1, aUV);
}