#include "Core.h"


namespace Pine {
	Core::Core()
	{

	}
	Core::~Core()
	{

	}

	void Core::PineInit()//init with window size, flag and f/r
	{
		//init logging

		Pine::Log::Init();
		PINE_ENGINE_INFO("Working");
	}

	Core::Core(const char* m_windowName, unsigned int m_Width, unsigned int m_Height)
	{
		SDL_Init(SDL_INIT_VIDEO);
		m_Window = SDL_CreateWindow(m_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL);
		if (m_Window == NULL)
		{
			auto a = SDL_GetError();
			PINE_ENGINE_ERROR("COULD NOT CREATE WINDOW {a}", a);
		}

		SDL_Surface* screenSurface = NULL;
		//Get window surface
		screenSurface = SDL_GetWindowSurface(m_Window);

		//Fill the surface white
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

		//Update the surface
		SDL_UpdateWindowSurface(m_Window);

		//Wait two seconds
		SDL_Delay(2000);
		
		

	}

	
	void Core::PineOpenWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height)
	{
		SDL_Init(SDL_INIT_VIDEO);
		m_Window = SDL_CreateWindow(m_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	}

	bool Core::PineInit(Game* game, uint8_t flags)
	{

		//setup everything for engine
		Pine::Log::Init();
		PINE_ENGINE_INFO("Welcome To Pine Engine!");
		PINE_ENGINE_INFO("Created By Bradley Marden : Licensed under Apache License");
		PINE_ENGINE_INFO("Refer to Documentation for Engine Use Cases");

		PINE_ENGINE_INFO("Application Starting...");
		if (!game)
		{
			return false;
		}
		else
		{
			givenGame = game;
		}
		if (flags & Pine_Networking)
		{
			PINE_ENGINE_ERROR("RUNNING NETWORKING");
			if (!Pine::Networking::PineNetworkInit())
			{
				PINE_ENGINE_ERROR("Error Loading NETWORKING... closing");
				givenGame->GameOver();
			}
		}
		if (flags & Pine_Server)
		{
			PINE_ENGINE_ERROR("RUNNING SERVER");
			if (!Pine::Networking::PineNetworkInit())
			{
				PINE_ENGINE_ERROR("Error Loading NETWORKING... closing");
				givenGame->GameOver();
			}
			if (Pine::Networking::PineNetworkCreate(2302,4) !=1)
			{
				PINE_ENGINE_ERROR("Error Creating Server... closing");
				givenGame->GameOver();
			}
		}
		
		//start game flow
		givenGame->Initialize();

		givenGame->GameRun();
		if (!givenGame->IsGameRunning())//if game is initialized
		{
			PINE_ENGINE_INFO("Failed to Run Application");
			givenGame->GameClose();//just for safety
			return false;
		}
		

		return true;
	}
	void Core::PineConnect()
	{
		Pine::Networking::PineNetworkConnect("127.0.0.1", 2302);
	}

	void Core::PinePoll()
	{
		Pine::Networking::PineNetworkLoop();

	}
	void Core::PineStart()
	{
		PINE_ENGINE_INFO("Application Started!");
		givenGame->Start();
		bool closeGame = false;
		SDL_Event event;
		while (!closeGame)
		{
			//PinePoll();
				if (givenGame->IsGameOver())
				{
					//PINE_ENGINE_INFO("Application Over");

				}
				if (givenGame->IsGameClosing())
				{

					//PINE_ENGINE_INFO("Application Closing");

					closeGame = true;
					givenGame->Terminate();
				}
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT)
					{
						givenGame->GameClose();
					}
				}
				if (!givenGame->IsGameMenu())//always runs while not in menu for opengl rendering controll
				{
					//PINE_ENGINE_INFO("Application not in Menu");

				}

				if (givenGame->IsGameRunning() || givenGame->IsGameMenu())//run all the time, even if the menu is open
				{
					//PINE_ENGINE_INFO("Application Running");

					givenGame->Update();
				}
		}
	}

	void Core::PineCloseWindow()
	{
		SDL_Delay(3000);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

}