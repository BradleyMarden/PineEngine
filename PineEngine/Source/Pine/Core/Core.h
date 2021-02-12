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
//#define PINE_ENGINE_INFO
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
#include "ECS/PineECS.h"
namespace Pine {

	typedef std::vector<std::shared_ptr<Pine::PObject>> GameObjects;
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
		

		static PVector2f GetMousePos();//abstarct out to another class
		//std::vector<PObject*>objects;//temp, move back to private!!
		template <typename T> void Instanciate(std::shared_ptr<T> object)//may work using reference but check with a pointer

		{
			//move to an internal function
			//need to add object to list
			objects.push_back(object);
			std::cout << "Instanciated" << std::endl;
			Draw(true);
		}

		void Test();
		int GetObjectCount() { return objects.size(); }

	 SDL_Renderer* GetRenderer() { return  renderer; }
	private:


		SDL_Window* m_Window = nullptr;
		Game* givenGame = nullptr;
		SDL_Renderer* renderer;
		SDL_Rect rect;
		SDL_Texture* text = nullptr;
		void HandleEvents();
		void ApplicationRunning();
		void Draw(bool firstDraw);

		GameObjects objects;
		const int fps = 60;
		const int frameDelay = 1000 / fps;// max time between frames
		Uint32 frameStart;
		int frameTime;


	};
}