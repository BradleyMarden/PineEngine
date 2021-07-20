#pragma once

#include "SDL.h"
#include "Log.h"
#include <glm.hpp>



#include <SDL_image.h>
#define SDL_MAIN_HANDLED
#undef main

#ifdef PINE_PLATFORM_WINDOWS

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <string>

#endif // PINE_PLATFORM_WINDOWS
#ifdef PINE_PLATFORM_MACOS
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <SDL_opengl.h>
#endif // PINE_PLATFORM_MACOS


namespace Pine {

#ifndef PINE_DEFAULT_WINDOW_SIZES
	#define PINE_DEFAULT_WINDOW_SIZES
	#define PINE_MAIN_WINDOW_SIZE 600
	#define PINE_SECONDARY_WINDOW_SIZE 400
#endif // !PINE_DEFAULT_WINDOW_SIZES

	class Window
	{
	public:
		struct WindowData
		{
			WindowData(const char* p_Name, int p_ID, Window* p_Window, bool p_IsMainWindow, glm::vec2 p_WindowSize) : s_WindowName(p_Name), s_WindowID(p_ID), s_Window(p_Window), s_IsMainWindow(p_IsMainWindow), s_WindowSize(p_WindowSize)
			{
				PINE_ENGINE_WARN(SDL_GetWindowTitle(s_Window->m_GlData.s_Window));
			}
			~WindowData() 
			{
				delete s_Window;
			}

			const char* s_WindowName;
			Window*		s_Window;
			bool		s_IsMainWindow = false;
			int			s_WindowID;
			glm::vec2   s_WindowSize;
		};

		struct WindowGlData 
		{
			SDL_Window* s_Window = nullptr;
			SDL_GLContext s_Context;
            SDL_Renderer* s_Renderer = nullptr;
		};
		Window(const char* p_WindowName, int p_ScreenAlignmentX, int p_ScreenAlignmentY, int p_WindowPosX, int p_WindowPosY);
		Window(const char* p_WindowName, int p_WindowPosX, int p_WindowPosY);
		Window(const char* p_WindowName);
		~Window();
		//Width in pixels of const Window*. Will return 0 if no window found
		const int		GetWidth() const { return  m_WindowWidth; }
		//Height in pixels of const Window*. Will return 0 if no window found
		const int		GetHeight() { return m_WindowHeight; }
		//void			SetWindowWidth();
		//void			SetWindowHeight();
		int				GetWindowID() { return m_WindowId; }
	

		//Returns struct containing sdl window and context.
        static WindowGlData* GetWindowGLData(const char* p_WindowName);
        //static void             SetRenderer();
		//Create window with p_WindowName. Returns const window*
		static const Window*	CreateNewWindow(const char* p_WindowName);
		//Create window with p_WindowName, with width and height. Returns const window*
		static const Window*	CreateNewWindow(const char* p_WindowName, int p_WindowPosX, int p_WindowPosY);
		//Returns const * to p_WindowName. If not found, will return nullptr.
		static Window*	GetWindow(const char* p_WindowName);
		//Returns raw * to main window. If not found, will return nullptr.
		static WindowData*		GetMainWindow();
		//Closes all windows that are open
		static void				CloseAllWindows();
		//Checks to see if p_WindowName is alive/open. Returns true if alive, and false if not
		static bool				CheckWindowAlive(const char* p_WindowName);
		//If found, closes window p_WindowName
        static void				CloseWindow(const char* p_WindowName);

		static void				SetWindowToRendeer(const char* p_WindowName);
		

		//Width in pixels of p_WindowName. Will return 0 if no window found
		inline static int		GetWindowWidth(const char* p_WindowName)
		{
			if (CheckWindowAlive(p_WindowName))
			{
				return GetWindow(p_WindowName)->m_WindowWidth;
			}
			return 0;
		}
		//Height in pixels of p_WindowName. Will return 0 if no window found
		inline static int		GetWindowHeight(const char* p_WindowName)
		{
			if (CheckWindowAlive(p_WindowName))
			{
				return GetWindow(p_WindowName)->m_WindowHeight;
			}
		}
		//Current count of all windows open
		inline static int		GetOpenWindowCount()
		{ 
			int l_NumOfWindows = 0;
			for (size_t i = 0; i < (sizeof(m_Windows)/sizeof(m_Windows[0])); i++)
			{
				if (m_Windows[i] != nullptr)
				{
					l_NumOfWindows++;
				}
			}
			return l_NumOfWindows;
		}



	private:
		inline static WindowData* m_Windows[10];
		static void	InitSDL();

		WindowGlData	m_GlData;
		const char*		m_WindowName;
		int				m_WindowWidth;
		int				m_WindowHeight;
		int				m_WindowId = 0;
	};
}
