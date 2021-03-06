#pragma once
// FLAGS-----------------------------------------------------
//Current flag limit is set as uint8_t, may expand if more flags are needed.
#define Pine_Networking 0x00000001
#define Pine_Server 0x00000002
#define Pine_Release 0x00000004
#define Pine_Debug 0x00000008
//#define PINE_ENGINE_INFO
//-----------------------------------------------------------

#include <vector>
#include <iostream>
#include <chrono>
#include <time.h>
#include <SDL_timer.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <assert.h>
#include <ctime>

#include "SDL.h"
#include "SDL_image.h"


#define SDL_MAIN_HANDLED
#undef main

#ifdef PINE_PLATFORM_WINDOWS

	#include <GL/glew.h>
	#include <GL/GL.h>
	#include <gl/GL.h>
	#include <SDL_opengl.h>

#endif // PINE_PLATFORM_WINDOWS
#ifdef PINE_PLATFORM_MACOS
#include <GL/glew.h>
	#include <OpenGL/gl.h>
#include <SDL_opengl.h>
#endif // PINE_PLATFORM_MACOS


//PINE INCLUDES
#include "Log.h"
#include "Input.h"
#include "Networking.h"
#include "Game.h"
#include "Core.h"
#include "../Rendering/Shader.h"
#include "EventSystem.h"
#include "../Maths/PMaths.h" 

//NEED TO LOOK INTO PRE COMPILED HEADERS


//NEEDS TO BE MOVED INTO A BASE.CPP
#define BIND_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)

//#include "ECS/PineECS.h"
namespace Pine {
	
	
	class Core
	{
	public:
		
						Core();
						~Core();
		void			PineCloseWindow();
		void			PineOpenWindow();
		bool			PineInit(Game* game, uint8_t flags);
		void			PineStart();
		void			Render();
		void			RenderUI();
		static PVector2f	GetMousePos();//abstract out to another class
		SDL_Renderer*		GetRenderer() { return  renderer; }//Move renderer to Renderer class
		std::chrono::steady_clock::time_point m_start;
		void			Trigger(PEvent& e);


	private:
		static inline SDL_Window*	m_Window = nullptr;
		static inline SDL_Window*	m_SecondWindow = nullptr;
		static inline SDL_GLContext m_Context; /* Our opengl context handle */
		Game*			givenGame = nullptr;//we do not own the game, entry point does. 
		SDL_Renderer*	renderer;
		SDL_Rect		rect;
		SDL_Texture*	text = nullptr;
		void			HandleEvents();
		void			ApplicationRunning();
		void			Draw(bool firstDraw);//Deprecated
		const char*		glsl_version = "#version 330";
		//GameObjects objects;//Deprecated
		const int		fps = 60;
		const int		frameDelay = 1000 / fps;// max time between frames
		Uint32			frameStart;
		int				frameTime;
		unsigned int	localshader;
		int				cTime = 0;
		bool			limitFPS = true;


	};
}
