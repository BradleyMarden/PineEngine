#pragma once

#include "SDL.h"
#include "Log.h"

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
#define PINE_WINDOW_WIDTH Pine::Game::GetWindowWidth()

#define PINE_WINDOW_HEIGHT Pine::Game::GetWindowHeight()

#define PINE_WINDOW_NAME &Pine::Game::GetWindowName()

/*NEW PINE WINDOW MACROS
* 
 #define PINE_WINDOW_WIDTH Pine::Window::GetWindowWidth()

#define PINE_WINDOW_HEIGHT Pine::Window::GetWindowHeight()

#define PINE_WINDOW_NAME &Pine::Window::GetWindowName()

	
*/
	

	class Window
	{
	public:
		struct WindowData
		{
			WindowData(const char* p_Name, int p_ID, Window* p_Window, bool p_IsMainWindow) : s_WindowName(p_Name), s_WindowID(p_ID), s_Window(p_Window), s_IsMainWindow(p_IsMainWindow)
			{

			}
			~WindowData() 
			{
				delete s_Window;
				//delete s_WindowName;
				PINE_ENGINE_WARN("WD Deleted");
			}

			const char* s_WindowName;
			int s_WindowID;
			Window* s_Window;
			bool s_IsMainWindow = false;

		};
		Window(const char* p_WindowName, int p_ScreenAlignmentX, int p_ScreenAlignmentY, int p_WindowPosX, int p_WindowPosY);
		Window(const char* p_WindowName, int p_WindowPosX, int p_WindowPosY);
		Window(const char* p_WindowName);
		~Window();
		void			SetWindowWidth();
		void			SetWindowHeight();

		static int		GetWindowWidth();
		static int		GetWindowHeight();
		static void		CloseAllWindows();
		static SDL_GLContext& GetWindowContext();
		static WindowData* GetMainWindow();
        static void CloseWindow(const char* pName);

		int				GetWindowID() { return m_WindowId; }
		inline static int GetOpenWindowCount() { return (sizeof(m_Windows) / sizeof(WindowData)); }



	private:
		const char* m_WindowName;
		int m_WindowWidth;
		int m_WindowHeight;
		inline static SDL_Window* m_Window = nullptr;
		inline static SDL_GLContext m_WindowContext;
		inline static WindowData* m_Windows[10];
		int m_WindowId = 0;
	};
}
