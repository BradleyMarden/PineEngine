#include "VertexBuffer.h"

namespace Pine {
	VertexBuffer::VertexBuffer(unsigned int p_Size)
	{
		//OPENGL(glGenBuffers(1, &m_ID));
		OPENGL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		OPENGL(glBufferData(GL_ARRAY_BUFFER, p_Size , GL_DYNAMIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
	
		OPENGL(glDeleteBuffers(1, &m_ID));
	}

	void VertexBuffer::Bind() 
	{
		OPENGL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));

	}

	void VertexBuffer::Unbind() 
	{
		OPENGL(glBindBuffer(GL_ARRAY_BUFFER, 0));

	
	}
}