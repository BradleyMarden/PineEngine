#pragma once
#include "Core.h"

namespace Pine{
	class PINE_API Application
	{
	
	public:
		Application();
		bool Run(Application* game);
		virtual void Update() {};
	};

	//to define in client
	Application* CreateApplication();
	
}

