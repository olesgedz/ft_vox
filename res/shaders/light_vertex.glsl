#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normCoord;

out vec4 vColor;

uniform mat4 u_M;
uniform mat4 u_V;
uniform mat4 u_P;

void main()
{
    gl_Position = u_P * u_V * u_M * vec4(position, 1.0f);
    vColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}