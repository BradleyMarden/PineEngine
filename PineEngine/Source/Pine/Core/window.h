#pragma once

#include "SDL.h"
#include "Log.h"

#define SDL_MAIN_HANDLED
#undef main

#ifdef PINE_PLATFORM_WINDOWS

#include <GL/glew.h>
#include <SDL_opengl.h>

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
		Window(const char* p_WindowName, int p_ScreenAlignmentX, int p_ScreenAlignmentY, int p_WindowPosX, int p_WindowPosY);
		Window(const char* p_WindowName, int p_WindowPosX, int p_WindowPosY);
		Window(const char* p_WindowName);
		~Window();

		int		GetWindowWidth();
		int		GetWindowHeight();
		void	SetWindowWidth();
		void	SetWindowHeight();
		SDL_Window* GetMainWindow();
		SDL_GLContext& GetMainWindowContext();


	private:
		const char* m_WindowName;
		int m_WindowWidth;
		int m_WindowHeight;
		SDL_Window* m_MainWindow = nullptr;
		SDL_GLContext m_MainWindowContext;

	};
}