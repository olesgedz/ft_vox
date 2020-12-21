#version 330 core

out vec4 colour;
in vec2 passTextureCoords;
uniform sampler2D ourTexture;
void main()
{
    colour = texture(ourTexture, passTextureCoords);
}