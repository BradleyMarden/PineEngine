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
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>




//PINE INCLUDES
#include "Log.h"
#include "Input.h"
#include "Networking.h"
#include "Game.h"
#include "Core.h"
#include "../Rendering/Shader.h"
#include "EventSystem.h"
#include "../Maths/PMaths.h" 
#include "window.h"
#include "Renderer.h"

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
		void			PineCloseEngine();
		void			PineInit(Game* game, uint8_t flags);
		void			PineStart();
		void			RenderUI();
		void			Trigger(PEvent& e);

	private:
		static inline Window*	m_Window = nullptr;
		Renderer*				m_PineRenderer = nullptr;

		Game*			givenGame = nullptr;//we do not own the game, entry point does. 
		void			HandleEvents();
		void			ApplicationRunning();
		const char*		glsl_version = "#version 330";
		const int		fps = 60;
		const int		frameDelay = 1000 / fps;// max time between frames
		Uint32			frameStart;
		int				frameTime;
		bool			limitFPS = true;
		Pine::Window* FourthWindow = nullptr;


	};
}
