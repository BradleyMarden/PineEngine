#pragma once
#include <SDL.h>
#include "Log.h"
namespace Pine {
	
	//renderer will only be allowed to, 
	class Renderer
	{
	public:
		//Renderer();
		Renderer()
		{
			PINE_ASSERT("Renderer has already been created, cannot have more than one instance!", !m_IsInstantiated);
			m_IsInstantiated = true;
		}
		~Renderer() { m_IsInstantiated = false; }
		



	private:
		SDL_Renderer* m_SDL_Renderer;
		static bool m_IsInstantiated;

	};
}