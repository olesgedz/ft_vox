//
// Created by Jeromy Black on 12/21/20.
//

#ifndef FT_VOX_VERTEXARRAY_H
#define FT_VOX_VERTEXARRAY_H
#include "glad.h"

class VertexArray
{
private:
	unsigned int m_ID;
public:
	VertexArray()
	{
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
	}

	~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void Unbind() const
	{
		glBindVertexArray(0);
	}

};

#endif //FT_VOX_VERTEXARRAY_H
