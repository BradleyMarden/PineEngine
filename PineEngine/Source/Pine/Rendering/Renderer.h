#pragma once
#include <SDL.h>
#include "Log.h"
#include "window.h"
namespace Pine {
	

	//renderer will only be allowed to, 
	class Renderer
	{
	public:
		//Renderer();
		Renderer(Window& p_Window)
		{
			PINE_ASSERT("Renderer has already been created, cannot have more than one instance!", !m_IsInstantiated);
			m_IsInstantiated = true;
			CreateRenderer();
		}
		~Renderer() 
		{ 
			
			m_IsInstantiated = false;
			SDL_DestroyRenderer(m_SDL_Renderer);
		}
		
		SDL_Renderer* GetRenderer() { return m_SDL_Renderer; }
		/*static void GLClearError()
		{
			while (glGetError() != GL_NO_ERROR);
		}
		static void GLCheckrror()
		{
			while (GLenum error = glGetError())
			{
				PINE_ENGINE_WARN(error);
				std::cout << "GL ERROR: " << error << std::endl;
			}
		}*/

		

	private:

		void CreateRenderer();


		SDL_Renderer* m_SDL_Renderer;
		static bool m_IsInstantiated;

	};
}