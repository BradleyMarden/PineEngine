#include "window.h"

namespace Pine 
{

	Window::Window(const char* p_WindowName, int p_ScreenAlignmentX, int p_ScreenAlignmentY, int p_WindowPosX, int p_WindowPosY)
	{

	}

	Window::Window(const char* p_WindowName, int p_WindowPosX, int p_WindowPosY)
	{

	}


	Window::Window(const char* p_WindowName)
	{
		
#ifdef PINE_PLATFORM_MACOS 
		// Request an OpenGL 4.5 context (should be core)
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Also request a depth buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

#elif PINE_PLATFORM_WINDOWS

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		//Currently not working, new renderer shoud fix
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Also request a depth buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#endif

		SDL_Init(SDL_INIT_VIDEO);

		if (m_Windows[0] == nullptr)
		{
			//create window
			m_Window = SDL_CreateWindow(p_WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
			//create context
			m_WindowContext = SDL_GL_CreateContext(m_Window);
			m_WindowHeight = 600;
			m_WindowWidth = 600;
			m_WindowId = 0;
			WindowData* data = new WindowData(p_WindowName, m_WindowId, this, true);
			m_Windows[0] = data;
		}
		else
		{
			int counter = 0;
			for (size_t i = 0; i < (sizeof(m_Windows) / sizeof(WindowData)); i++)
			{
				if (m_Windows[i] == nullptr)
				{
					//create window
					m_Window = SDL_CreateWindow(p_WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
					//create context
					m_WindowContext = SDL_GL_CreateContext(m_Window);
					m_WindowHeight = 600;
					m_WindowWidth = 600;
					m_WindowId = counter;
					WindowData* data = new WindowData(p_WindowName, m_WindowId, this, false);
					m_Windows[i] = data;
					return;
				}

			}
			
		}
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;

		}
		//needs to be in renderer
		glViewport(0, 0, 600, 600);
		glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	}

	Window::~Window() 
	{
		//remove from list
		m_Windows[m_WindowId] = nullptr;
		SDL_GL_DeleteContext(m_WindowContext);
		SDL_DestroyWindow(m_Window);
		PINE_ENGINE_ERROR("Destoryed");
	}

	Window::WindowData* Window::GetMainWindow() 
	{
		PINE_ASSERT("MAIN WINDOW HAS BOT BEEN CREATED!", m_Windows[0]);
		return m_Windows[0];
	}
	SDL_GLContext& Window::GetWindowContext() 
	{
		PINE_ASSERT("MAIN WINDOW CONTEXT HAS NOT BEEN CREATED!", m_WindowContext);
		return m_WindowContext;
	}
	void Window::CloseWindow(const char* pName) 
	{

		for (size_t i = 0; i < (sizeof(m_Windows) / sizeof(WindowData)); i++)
		{

			//PINE_ENGINE_ERROR(m_Windows[i]->s_WindowName);
			if (m_Windows[i] == nullptr)
			{
				return;
			}
			else if (m_Windows[i] != nullptr)
			{

				PINE_ENGINE_ERROR("HERE");

				if (strcmp(m_Windows[i]->s_WindowName, pName))
				{
					PINE_ENGINE_ERROR(m_Windows[i]->s_WindowName);

					SDL_DestroyWindow(m_Windows[i]->s_Window->m_Window);
					delete m_Windows[i];
					m_Windows[i] = nullptr;
					return;
				}
			}
			
		}
	}
	void Window::CloseAllWindows() 
	{
		for (WindowData* winData : m_Windows)
		{
			if (winData != nullptr)
			{
				std::cout << "WINDOW" << std::endl;
				SDL_DestroyWindow(winData->s_Window->m_Window);
			}
		}
		
	}
}

