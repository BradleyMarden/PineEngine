#pragma once
//Only to be used by Pine applications
//#include "sdl2/SDL.h"
//#include <stdio.h>
//#include "PineAPI.h"
#include "../Logging/Log.h"
#include "../Networking/Networking.h"
#include "Game.h"
#include "sdl2/SDL.h"
#include "sdl2/SDL_image.h"
#include "../Primitives/2D/PCircle.h"
#include"../Primitives/2D/PRect.h"
#include <vector>
#undef main

// FLAGS-----------------------------------------------------
//Current flag limit is set as uint8_t, may expand if more flags are needed.
#define Pine_Networking 0x00000001
#define Pine_Server 0x00000002
#define Pine_Release 0x00000004
#define Pine_Debug 0x00000008

//-----------------------------------------------------------


#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "GL/glew.h"
#include <sdl2/SDL_opengl.h>


namespace Pine {

	//
	class Core
	{

		//the game application.
	public:
		
		Core();
		~Core();
		Core(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);

		static void PineInit();
		static void PineConnect();
		static void PinePoll();

		void    PineCloseWindow();
		void    PineOpenWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);
		bool    PineInit(Game* game, uint8_t flags);
		void    PineStart();


	
	private:

		SDL_Window* m_Window = nullptr;
		Game* givenGame;
		SDL_Renderer* renderer;
		SDL_Rect rect;
		SDL_Texture* text;
		std::vector<PObject>objects;

	};
}