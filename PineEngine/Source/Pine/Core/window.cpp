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

		//create window
		m_MainWindow = SDL_CreateWindow(p_WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,600,600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		//create context
		m_MainWindowContext = SDL_GL_CreateContext(m_MainWindow);
		m_WindowHeight = 600;
		m_WindowWidth = 600;

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
		
	}

	SDL_Window* Window::GetMainWindow() 
	{
		PINE_ASSERT("MAIN WINDOW HAS BOT BEEN CREATED!", m_MainWindow);
		return m_MainWindow;
	}
	SDL_GLContext& Window::GetMainWindowContext() 
	{
		PINE_ASSERT("MAIN WINDOW CONTEXT HAS NOT BEEN CREATED!", m_MainWindowContext);
		return m_MainWindowContext;
	}

}

