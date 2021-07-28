#include "IndexBuffer.h"

namespace Pine {
	IndexBuffer::IndexBuffer(const unsigned int* p_Data, unsigned int p_Count)
		:m_Count(p_Count)
	{

		OPENGL(glGenBuffers(1, &m_ID));
		OPENGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		OPENGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_Count* sizeof(unsigned int), p_Data, GL_STATIC_DRAW));


	}

	IndexBuffer::~IndexBuffer() 
	{

		OPENGL(glDeleteBuffers(1, &m_ID));
	}

	void IndexBuffer::Bind() const
	{
		OPENGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));

	}

	void IndexBuffer::Unbind() const
	{
		OPENGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));


	}
}