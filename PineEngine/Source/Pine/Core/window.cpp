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
	}


	Window::~Window() 
	{
		//remove from list
		PINE_ENGINE_WARN("DELETE WINDOW");
		PINE_ENGINE_WARN(m_WindowId);
		m_Windows[m_WindowId] = nullptr;
		SDL_GL_DeleteContext(m_GlData.s_Context);

		PINE_ENGINE_WARN(SDL_GetWindowTitle(m_GlData.s_Window));
		SDL_DestroyWindow(m_GlData.s_Window);
	}
	const Window* Window::CreateNewWindow(const char* p_WindowName) 
	{
		InitSDL();


		if (m_Windows[0] == nullptr)
		{
			Window* l_Window = new Window(p_WindowName);
			//create window
			l_Window->m_GlData.s_Window = SDL_CreateWindow(p_WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PINE_MAIN_WINDOW_SIZE, PINE_MAIN_WINDOW_SIZE, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
			//create context
			l_Window->m_GlData.s_Context = SDL_GL_CreateContext(l_Window->m_GlData.s_Window);
            l_Window->m_GlData.s_Renderer =  SDL_CreateRenderer(l_Window->m_GlData.s_Window, -1, 0);
			l_Window->m_WindowHeight = PINE_MAIN_WINDOW_SIZE;
			l_Window->m_WindowWidth = PINE_MAIN_WINDOW_SIZE;
			l_Window->m_WindowId = 0;
			WindowData* data = new WindowData(p_WindowName, l_Window->m_WindowId, l_Window, true);
			m_Windows[0] = data;
			GLenum err = glewInit();
			if (GLEW_OK != err)
				PINE_ENGINE_ERROR("ERROR WITH GLEW");

			return l_Window;
		}
		else
		{
			int counter = 0;
			for (size_t i = 0; i < 10; i++)
			{
				if (m_Windows[i] == nullptr)
				{
					//create window
					Window* l_Window = new Window(p_WindowName);
					l_Window->m_GlData.s_Window = SDL_CreateWindow(p_WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PINE_SECONDARY_WINDOW_SIZE, PINE_SECONDARY_WINDOW_SIZE, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
					//create context
					l_Window->m_GlData.s_Context = SDL_GL_CreateContext(l_Window->m_GlData.s_Window);
					l_Window->m_WindowHeight = PINE_SECONDARY_WINDOW_SIZE;
					l_Window->m_WindowWidth = PINE_SECONDARY_WINDOW_SIZE;
					l_Window->m_WindowId = i;
					WindowData* data = new WindowData(p_WindowName, l_Window->m_WindowId, l_Window, true);
					m_Windows[i] = data;
					return l_Window;
				}
			}
		}

		//needs to be in renderer
		
		return nullptr;

	}

	const Window* Window::CreateNewWindow(const char* p_WindowName, int p_WindowWidthX, int p_WindowWidthY)
	{
		InitSDL();


		if (m_Windows[0] == nullptr)
		{
			Window* l_Window = new Window(p_WindowName);
			//create window
			l_Window->m_GlData.s_Window = SDL_CreateWindow(p_WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_WindowWidthX, p_WindowWidthY, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
			//create context
			l_Window->m_GlData.s_Context = SDL_GL_CreateContext(l_Window->m_GlData.s_Window);
            //l_Window->m_GlData.s_Renderer =  SDL_CreateRenderer(l_Window->m_GlData.s_Window, -1, 0);
			l_Window->m_WindowHeight = p_WindowWidthY;
			l_Window->m_WindowWidth = p_WindowWidthX;
			l_Window->m_WindowId = 0;
			WindowData* data = new WindowData(p_WindowName, l_Window->m_WindowId, l_Window, true);
			m_Windows[0] = data;
			GLenum err = glewInit();
			if (GLEW_OK != err)
				std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return l_Window;
		}
		else
		{
			int counter = 0;
			for (size_t i = 0; i < 10; i++)
			{
				if (m_Windows[i] == nullptr)
				{
					//create window
					Window* l_Window = new Window(p_WindowName);
					l_Window->m_GlData.s_Window = SDL_CreateWindow(p_WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_WindowWidthX, p_WindowWidthY, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
					//create context
					l_Window->m_GlData.s_Context = SDL_GL_CreateContext(l_Window->m_GlData.s_Window);
					l_Window->m_WindowHeight = p_WindowWidthY;
					l_Window->m_WindowWidth = p_WindowWidthX;
					l_Window->m_WindowId = i;
					WindowData* data = new WindowData(p_WindowName, l_Window->m_WindowId, l_Window, true);
					m_Windows[i] = data;
					return l_Window;
				}
			}
		}

		//needs to be in renderer
		//glViewport(0, 0, 600, 600);
		//glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
		return nullptr;
	
	}
	Window::WindowData* Window::GetMainWindow() 
	{
		if (m_Windows[0] != nullptr)
		{
			return m_Windows[0];
		}
		return nullptr;
	}
	
	void Window::CloseWindow(const char* p_WindowName)
	{

		for (size_t i = 0; i <(sizeof(m_Windows)/sizeof(m_Windows[0])); i++)
		{
			if (m_Windows[i] != nullptr)
			{
				if (strcmp(m_Windows[i]->s_WindowName, p_WindowName) == 0)
				{
					delete m_Windows[i];
					return;
				}
			}
			else if (i == (sizeof(m_Windows) / sizeof(m_Windows[0]))-1)
			{
				PINE_ENGINE_WARN("That window does not exits");
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
				SDL_DestroyWindow(winData->s_Window->m_GlData.s_Window);
			}
		}
	}

	bool Window::CheckWindowAlive(const char* p_WindowName) 
	{
		for (WindowData* wind : m_Windows)
		{
			if (wind != nullptr && strcmp(wind->s_WindowName, p_WindowName) ==0)
			{
				return true;
			}
		}
		return false;
	}

	 Window* Window::GetWindow(const char* p_WindowName) 
	{
		for (WindowData* wind : m_Windows)
		{
			if (wind != nullptr && strcmp(wind->s_WindowName, p_WindowName) == 0)
			{
				return wind->s_Window;
			}
		}
		return nullptr;
	}
	
	 Window::WindowGlData* Window::GetWindowGLData(const char* p_WindowName)
	{

		if (Window* wind = GetWindow(p_WindowName))
		{
			//This feels like a really baaaaad thing to do. But, it works so..
			//WindowGlData* data = wind->m_GlData;
			return &wind->m_GlData;
		}
	}

	void Window::InitSDL() 
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
	}
}

