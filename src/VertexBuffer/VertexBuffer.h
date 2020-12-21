//
// Created by Jeromy Black on 12/21/20.
//

#ifndef FT_VOX_VERTEXBUFFER_H
#define FT_VOX_VERTEXBUFFER_H
#include "glad/glad.h"
#include <string>

template <typename T>
class VertexBuffer
{
private:
	unsigned int m_ID;
	const T* m_Data;
	const size_t m_Size;
public:
	VertexBuffer(const T* data, size_t size)
			: m_Data(data), m_Size(size)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, m_Size * sizeof(T), m_Data, GL_STATIC_DRAW);
	}

	void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, m_Size * sizeof(T), m_Data, GL_STATIC_DRAW);
	}

	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};
#endif //FT_VOX_VERTEXBUFFER_H
