#pragma once
#include "Core.h"

namespace Pine{
	class PINE_API Application
	{
	
	public:
		Application();
		// ~Application();
		void Run();
	};

	//to define in client
	Application* CreateApplication();
}

