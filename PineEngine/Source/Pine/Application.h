#pragma once
#include "Core.h"
#include "sdl2/SDL.h"
#include <stdio.h>
#undef main
namespace Pine{
	class PINE_API Application
	{
	
	public:
		Application();
		bool Run(Application* game);
		virtual void Update() {};
		virtual void Terminate() {};
	};

	//to define in client
	Application* CreateApplication();
	
}

