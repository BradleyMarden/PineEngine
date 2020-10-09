#include "Application.h"

namespace Pine
{

	Application::Application()
	{

	}

	
	bool Application::Run(Application* game)
	{
		//while (true);
		//{
		
			//Application::Update();
			game->Update();
			
		//};
		
		return true;
	}
}

