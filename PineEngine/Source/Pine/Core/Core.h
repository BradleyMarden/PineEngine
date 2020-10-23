#pragma once
//Only to be used by Pine applications
//#include "sdl2/SDL.h"
//#include <stdio.h>
//#include "PineAPI.h"
#include "../Logging/Log.h"
#include "../Networking/Networking.h"
#include "Game.h"
#include "sdl2/SDL.h"
#undef main

// FLAGS-----------------------------------------------------
//Current flag limit is set as uint8_t, may expand if more flags are needed.
#define Pine_Networking 0x00000001
#define Pine_Server 0x00000002
#define Pine_Release 0x00000004
#define Pine_Debug 0x00000008

//-----------------------------------------------------------

//#include "../Networking/Networking.h"
//#include "Application.h"

//#include "Pine/Core/EntryPoint.h"




namespace Pine {


	class Core
	{

		

	public:
		
		Core();
		~Core();
		static void PineInit();
		Core(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);
		void PineCloseWindow();
		static void PineConnect();
		void PineOpenWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);
		bool PineInit(Game* game, uint8_t flags);
		void PineStart();
		static void PinePoll();
	private:
		SDL_Window* m_Window = nullptr;
		Game* givenGame;
		
	};
}