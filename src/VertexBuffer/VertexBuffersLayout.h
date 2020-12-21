//
// Created by Jeromy Black on 12/21/20.
//

#ifndef FT_VOX_VERTEXBUFFERSLAYOUT_H
#define FT_VOX_VERTEXBUFFERSLAYOUT_H
#include "glad.h"

class VertexBuffersLayout
{
private:
	mutable int m_Count = 0;
public:
	VertexBuffersLayout() = default;
	~VertexBuffersLayout() = default;

	template<typename T>
	void Push(unsigned int amount, unsigned int stride, unsigned int offset) const
	{
		glVertexAttribPointer(m_Count, amount, GL_FLOAT, GL_FALSE, stride * sizeof(T), (void *)(offset * sizeof(T)));
		glEnableVertexAttribArray(m_Count);
		m_Count++;
	}
};

#endif //FT_VOX_VERTEXBUFFERSLAYOUT_H
