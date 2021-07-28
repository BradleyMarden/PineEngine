#pragma once
#include "Renderer.h"
namespace Pine {

	class IndexBuffer
	{

	private:
		unsigned int m_ID;
		unsigned int m_Count;


	public:
		IndexBuffer(const unsigned int* p_Data, unsigned int p_Count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
		inline unsigned int GetCount() const{ return m_Count; }
	};
}