#pragma once
//Only to be used by Pine applications
//#include "sdl2/SDL.h"
//#include <stdio.h>
#include "PineAPI.h"
#include "../Logging/Log.h"
#include "Game.h"
#include "sdl2/SDL.h"
#undef main

//#include "../Networking/Networking.h"
//#include "Application.h"

//#include "Pine/Core/EntryPoint.h"




namespace Pine {
	class PINE_API Core
	{

	public:
		Core();
		~Core();
		static void PineInit();
		Core(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);
		void PineCloseWindow();
		void PineOpenWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);
		bool PineInit(Game* game);
		void PineStart();
		

	private:
		SDL_Window* m_Window = nullptr;
		Game* givenGame;
		
	};
}