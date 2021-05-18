#pragma once
//Only to be used by Pine applications
//#undef main


// FLAGS-----------------------------------------------------
//Current flag limit is set as uint8_t, may expand if more flags are needed.
#define Pine_Networking 0x00000001
#define Pine_Server 0x00000002
#define Pine_Release 0x00000004
#define Pine_Debug 0x00000008
//#define PINE_ENGINE_INFO
//-----------------------------------------------------------

//PINE INCLUDES
#include "Log.h"
#include "Networking.h"
#include "Game.h"
#include "Core.h"


#include "SDL.h"
#include "SDL_image.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <SDL_opengl.h>
#include <chrono>
#include <time.h>
#include <SDL_timer.h>
#include "../Maths/PMaths.h" 
#include "Input.h"
#define SDL_MAIN_HANDLED
#undef main



#ifdef PINE_PLATFORM_WINDOWS
	#include <GL/GL.h>
#endif // PINE_PLATFORM_WINDOWS
#ifdef PINE_PLATFORM_MACOS
	#include <OpenGL/gl.h>
#endif // PINE_PLATFORM_MACOS

/*#include "../Logging/Log.h"
#include "../Networking/Networking.h"
#include "Game.h"
#include "SDL.h"
#include <vector>
#include <iostream>
//#include "EntryPoint.h"




#include <GL/glew.h>
#include "glfw3.h"

#ifdef PINE_PLATFORM_WINDOWS
#include <GL/GL.h>

#endif // PINE_PLATFORM_WINDOWS
#ifdef PINE_PLATFORM_MACOS
#include <OpenGL/gl.h>

#endif // PINE_PLATFORM_MACOS


// FLAGS-----------------------------------------------------
//Current flag limit is set as uint8_t, may expand if more flags are needed.
#define Pine_Networking 0x00000001
#define Pine_Server 0x00000002
#define Pine_Release 0x00000004
#define Pine_Debug 0x00000008
//#define PINE_ENGINE_INFO
//-----------------------------------------------------------

#include <stdio.h>
#include <iostream>
//#include <io.h>
#include <fcntl.h>
//#include <windows.h>
//#include "GL/glew.h"
#include <SDL_opengl.h>
#include <chrono>
#include <time.h>
#include <SDL.h>
#include <SDL_timer.h>
#include "../Maths/PMaths.h" 
#include "Input.h"*/

//#include "ECS/PineECS.h"
namespace Pine {

	//typedef std::vector<std::shared_ptr<Pine::PObject>> GameObjects;//Deprecated
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
		

		static PVector2f GetMousePos();//abstract out to another class
		//std::vector<PObject*>objects;//temp, move back to private!!

		template <typename T> void Instanciate(std::shared_ptr<T> object)//Deprecated
		{
			//move to an internal function
			//need to add object to list
			//objects.push_back(object);
			std::cout << "Instanciated" << std::endl;
			Draw(true);
		}

		void Test();//used for redrawing the screen
		//int GetObjectCount() { return objects.size(); }//Deprecated

		SDL_Renderer* GetRenderer() { return  renderer; }//Move renderer to Renderer class

		private:
		//NEW
		//PECS m_PGameObjectManager;

		SDL_Window* m_Window = nullptr;
		Game* givenGame = nullptr;
		SDL_Renderer* renderer;
		SDL_Rect rect;
		SDL_Texture* text = nullptr;
		void HandleEvents();
		void ApplicationRunning();
		void Draw(bool firstDraw);//Deprecated

		//GameObjects objects;//Deprecated
		const int fps = 60;
		const int frameDelay = 1000 / fps;// max time between frames
		Uint32 frameStart;
		int frameTime;


	};
}
