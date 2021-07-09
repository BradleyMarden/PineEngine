#pragma once
#include <SDL.h>
#include "Log.h"
#include "window.h"
#include <glm.hpp>
#include <glew.h>
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
			CreateRenderer();
		}
		~Renderer() 
		{ 
			
			m_IsInstantiated = false;
			//SDL_DestroyRenderer(m_SDL_Renderer);
		}
		
		//SDL_Renderer* GetRenderer() { return m_SDL_Renderer; }
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
        //load scene from file.
        inline static void InitRendering()
        {
            SDL_Renderer* renderer = Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Renderer;
			PINE_ENGINE_WARN("Rendering loaded");

			//SDL_CreateRenderer(m_WindowTwo->GetMainWindow(), -1, 0);
			SDL_SetRenderDrawColor(renderer, 21, 27, 31, 255);
			SDL_RenderClear(renderer);
            
        }
        static void LoadScene(const char* p_FilePath);
        static void Render();
        static void CreateQuad(const char* p_Name, int p_Width, int p_Height);
        static void CreateQuad(const char* p_Name, int p_Width, int p_Height,GLint m_Texture);
        static void LoadTextureMap(const char* p_FilePath);
        
        static void Flush();
		

	private:

		void CreateRenderer();


		static bool m_IsInstantiated;
        static SDL_Renderer m_Renderer;

	};
}
