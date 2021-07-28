#pragma once
#include "Renderer.h"
namespace Pine {

	class VertexBuffer
	{

	private:
		unsigned int m_ID;


	public:
		VertexBuffer(unsigned int size);
		~VertexBuffer();

		void Bind();
		void Unbind();


	};
}