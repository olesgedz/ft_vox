#version 410 core

layout(location = 0) in vec4 vertex;

out vec2 vTexCoord;

uniform mat4 u_P;

void main()
{
    gl_Position = u_P * vec4(vertex.xy, 0.0f, 1.0f);
    vTexCoord = vertex.zw;
}