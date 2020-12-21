#ifndef HUMAGL_MATHS_H
#define HUMAGL_MATHS_H

struct vec3
{
    float x;
    float y;
    float z;
    vec3() : x(0.0f), y(0.0f), z(0.0f) {};
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    vec3 operator +(vec3 other)
    {
        return vec3(x + other.x, y + other.y, z + other.z);
    }
    vec3 operator -(vec3 other)
    {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    float length();
};

vec3 operator *(float f, vec3 vector);
vec3 operator *(vec3 vector, float  other);
struct mat4;

vec3  lerp(vec3 v0, vec3 v1, float t);

struct mat3
{
    float mat[9];
    mat3()
    {
        for (int i = 0; i < 9; ++i)
            mat[i] = 0.0f;
    };
    mat3(float f)
    {
        for (int i = 0; i < 9; ++i)
            mat[i] = 0.0f;
        mat[0] = f;
        mat[4] = f;
        mat[8] = f;
    }
    mat3(mat3& other)
    {
        for (int i = 0; i < 9; ++i)
            mat[i] = other.mat[i];
    }
    mat3(mat4& other);
};

struct mat4
{
    float mat[16];
    mat4()
    {
        for (int i = 0; i < 16; ++i)
            mat[i] = 0.0f;
    };
    mat4(float f)
    {
        for (int i = 0; i < 16; ++i)
            mat[i] = 0.0f;
        mat[0] = f;
        mat[5] = f;
        mat[10] = f;
        mat[15] = f;
    }
    mat4(mat4& other)
    {
        for (int i = 0; i < 16; ++i)
            mat[i] = other.mat[i];
    };
    mat4(mat3& other);
    mat4 operator *(mat4 other)
    {
        mat4    result;
        float   ptr[16];
        int		j;
        int		i;
        int		k;

        i = 0;
        k = 0;
        while (i < 16)
        {
            j = -1;
            while (++j < 4)
                ptr[k++] = mat[i] * other.mat[j] + mat[i + 1] * other.mat[j + 4] + mat[i + 2]
                * other.mat[j + 8] + mat[i + 3] * other.mat[j + 12];
            i += 4;
        }
        i = -1;
        while (++i < 16)
            result.mat[i] = ptr[i];
        return result;
    };

//	mat4 operator -(mat4 other)
//	{
//		mat4    result;
//		int		i;
//
//		i = 0;
//		while (i < 16)
//		{
//			result.mat[i] = mat[i] - other.mat[i];
//			i++;
//		}
//		return result;
//	};


};

vec3    normalize(vec3 vector);
vec3    cross(vec3& vector1, vec3& vector2);
float   dot(vec3& vector1, vec3& vector2);
mat4    look_at(vec3 eye, vec3 center, vec3 up);
mat4    perspective(float fov, float ratio, float near, float far);
mat4    translate(mat4 matrix, vec3 vector);
mat4    rotate(mat4 matrix, vec3 vector);
mat4    scale(mat4 matrix, vec3 vector);

#endif //HUMAGL_MATHS_H
