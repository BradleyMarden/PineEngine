#pragma once
//Only to be used by Pine applications

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
#include <chrono>
#include <time.h>
#include <sdl2/SDL_timer.h>
#include "Input.h"

#define fps 60

namespace Pine {

	//
	class Core
	{

		//the game application.
	public:
		
		Core();
		~Core();
		Core(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);

		void		PineCloseWindow();
		void		PineOpenWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height);
		bool		PineInit(Game* game, uint8_t flags);
		void		PineStart();
        void        Instanciate(PObject* object);
		

		static PVector2f GetMousePos();//abstarct out to another class
		
		void Draw();//need to refactyor, causes errors when used on clients. Needs to only be used privately
	
	private:


		SDL_Window* m_Window = nullptr;
		Game* givenGame = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDL_Rect rect;
		SDL_Texture* text = nullptr;

		void ApplicationRunning();
		void HandleEvents();
		std::vector<PObject*>objects;//temp, move back to private!!
		
		//const int fps = 60;
		const int frameDelay = 1000 / fps;// max time between frames
		Uint32 frameStart;
		int frameTime;


	};
}
