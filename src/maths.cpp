//
// Created by Esmeralda Bednar on 12/19/20.
//

#include <math.h>
#include "maths.h"

float vec3::length()
{
    return  sqrt(x * x + y * y + z * z);
}

vec3 normalize(vec3 vector)
{
    float length = vector.length();
    return vec3(vector.x / length, vector.y / length, vector.z / length);
}

vec3 cross(vec3& vector1, vec3& vector2)
{
    float x = vector1.y * vector2.z - vector1.z * vector2.y;
    float y = vector1.z * vector2.x - vector1.x * vector2.z;
    float z = vector1.x * vector2.y - vector1.y * vector2.x;
    return vec3(x, y, z);
}

float dot(vec3& vector1, vec3& vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

vec3 operator *(float f, vec3 vector)
{
    return vec3(vector.x * f, vector.y * f, vector.z * f);
}

vec3 operator *(vec3 vector, float  other)
{
	return vec3(vector.x * other,vector.y * other, vector.z * other);
}
vec3  lerp(vec3 v0, vec3 v1, float t) {
return (v0 * (1 - t) + v1 * t);
}

mat3::mat3(mat4 &other)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mat[i * 3 + j] = other.mat[i * 4 + j];
}

mat4::mat4(mat3 &other)
{
    for (int i = 0; i < 16; ++i)
        mat[i] = 0.0f;
    mat[0] = 1.0f;
    mat[5] = 1.0f;
    mat[10] = 1.0f;
    mat[15] = 1.0f;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mat[i * 4 + j] = other.mat[i * 3 + j];
}

mat4 look_at(vec3 eye, vec3 center, vec3 up)
{
    mat4 matrix;
    vec3 x, y, z;

    z = eye - center;
    z = normalize(z);
    y = up;
    x = cross(y, z);
    y = cross(z, x);
    x = normalize(x);
    y = normalize(y);
    matrix.mat[0] = x.x;
    matrix.mat[4] = x.y;
    matrix.mat[8] = x.z;
    matrix.mat[12] = -dot(x, eye);
    matrix.mat[1] = y.x;
    matrix.mat[5] = y.y;
    matrix.mat[9] = y.z;
    matrix.mat[13] = -dot(y, eye);
    matrix.mat[2] = z.x;
    matrix.mat[6] = z.y;
    matrix.mat[10] = z.z;
    matrix.mat[14] = -dot(z, eye);
    matrix.mat[3] = 0.0f;
    matrix.mat[7] = 0.0f;
    matrix.mat[11] = 0.0f;
    matrix.mat[15] = 1.0f;
    return matrix;
}

mat4    perspective(float fov, float ratio, float near, float far)
{
    mat4 persp;

    float right = near * tanf(fov / 2.0f);
    float left = -right;
    float top = right * ratio;
    float bottom = - top;
    persp.mat[0] = near / top;
    persp.mat[5] = near / right;
    persp.mat[10] = -(far + near)/(far - near);
    persp.mat[11] = -1.0f;
    persp.mat[14] = -(2.0f * far * near) / (far - near);

    return persp;
}

mat4    translate(mat4 matrix, vec3 vector)
{
   	//matrix.mat[0] = 1.0f;
    matrix.mat[12] += vector.x;
   	//matrix.mat[5] = 1.0f;
    matrix.mat[13] += vector.y;
   	//matrix.mat[10] = 1.0f;
    matrix.mat[14] += vector.z;
    matrix.mat[15] = 1.0f;
    return matrix;
}

mat4 rotate_x(mat4& matrix, float angle)
{
    matrix.mat[5] = cos(angle);
    matrix.mat[6] = sin(angle);
    matrix.mat[9] = -sin(angle);
    matrix.mat[10] = cos(angle);
    return matrix;
}

mat4 rotate_y(mat4& matrix, float angle)
{
    matrix.mat[0] = cos(angle);
    matrix.mat[2] = -sin(angle);
    matrix.mat[8] = sin(angle);
    matrix.mat[10] = cos(angle);
    return matrix;
}

mat4 rotate_z(mat4& matrix, float angle)
{
    matrix.mat[0] = cos(angle);
    matrix.mat[1] = sin(angle);
    matrix.mat[4] = -sin(angle);
    matrix.mat[5] = cos(angle);
    return matrix;
}

mat4    rotate(mat4 matrix, vec3 vector)
{
    mat4 m1(1.0f);
    mat4 m2(1.0f);
    mat4 m3(1.0f);
    m1 = rotate_x(m1, vector.x * M_PI / 180.0f);
    m2 = rotate_y(m2, vector.y * M_PI / 180.0f);
    m3 = rotate_z(m3, vector.z * M_PI / 180.0f);
    matrix = m1 * matrix;
    matrix = m2 * matrix;
    matrix = m3 * matrix;
    return matrix;
}
mat4    scale(mat4 matrix, vec3 vector)
{
    mat4 m1(1.0f);
    m1.mat[0] = vector.x;
    m1.mat[5] = vector.y;
    m1.mat[10] = vector.z;
    matrix = m1 * matrix;
    return matrix;
}