#version 410 core

out vec4 color;

in vec2 vTexCoord;

uniform sampler2D ourTexture;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(ourTexture, vTexCoord).r);
    color = vec4(textColor, 1.0) * sampled;
}