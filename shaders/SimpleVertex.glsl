#version 330 core

layout (location = 0) in vec3 inVertexPosition;
layout (location = 2) in vec2 inUV;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;
out vec4 aPos;
out vec2 aUV;

void main()
{
    //
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4 (inVertexPosition.x, inVertexPosition.y, inVertexPosition.z, 1.0);
//    gl_Position =  vec4 (inVertexPosition.x, inVertexPosition.y, inVertexPosition.z, 1.0);
    aPos = gl_Position;
    aUV = inUV;
}