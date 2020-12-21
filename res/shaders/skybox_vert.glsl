#version 410 core

layout(location = 0) in vec3 position;

out vec3 vTexCoords;

uniform mat4 u_V;
uniform mat4 u_P;

void main()
{
    vTexCoords = position;
    gl_Position = u_P * u_V * vec4(position, 1.0f);
}