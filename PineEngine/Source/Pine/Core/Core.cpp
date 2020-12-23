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

		//Pine::Log::Init();
		//PINE_ENGINE_INFO("Working");
	}

	Core::Core(const char* m_windowName, unsigned int m_Width, unsigned int m_Height)
	{
		if (glewInit() != GLEW_OK)
		{
			PINE_ENGINE_ERROR("OPENGL NO INITIALIZED!");
		}
		//SDL_GL_CreateContext()
		SDL_Init(SDL_INIT_VIDEO);
		m_Window = SDL_CreateWindow(m_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL);
		if (m_Window == NULL)
		{
			auto a = SDL_GetError();
			PINE_ENGINE_ERROR("COULD NOT CREATE WINDOW {a}", a);
		}

		glViewport(0, 0, m_Width, m_Height);
		SDL_Surface* screenSurface = NULL;
		//Get window surface
		screenSurface = SDL_GetWindowSurface(m_Window);

		//Fill the surface white
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		//Update the surface
		SDL_UpdateWindowSurface(m_Window);
		//Wait two seconds
		SDL_Delay(2000);
		glewInit();
	}

	
	void Core::PineOpenWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height)
	{
		SDL_Init(SDL_INIT_VIDEO);
		m_Window = SDL_CreateWindow(m_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	}

	bool Core::PineInit(Game* game, uint8_t flags)
	{
		Pine::Log::Init();
		if (!game)
		{
			return false;
		}
		else
		{
			givenGame = game;
		}
		
		PINE_ENGINE_INFO("Welcome To Pine Engine!");
		PINE_ENGINE_INFO("Created By Bradley Marden : Licensed under Apache License");
		PINE_ENGINE_INFO("Refer to Documentation for Engine Use Cases");

		PINE_ENGINE_INFO("Application Starting...");
		
		if (flags & Pine_Networking)
		{
			PINE_ENGINE_ERROR("RUNNING NETWORKING");
			if (!Pine::Networking::PineNetworkingInit())
			{
				PINE_ENGINE_ERROR("Error Loading NETWORKING... closing");
				givenGame->GameOver();
			}
		}
		if (flags & Pine_Server)
		{
			PINE_ENGINE_ERROR("RUNNING SERVER");
			if (!Pine::Networking::PineNetworkingInit())
			{
				PINE_ENGINE_ERROR("Error Loading NETWORKING... closing");
				givenGame->GameOver();
			}
			if (Pine::Networking::PineServerCreate(2302,4) !=1)
			{
				PINE_ENGINE_ERROR("Error Creating Server... closing");
				givenGame->GameOver();
			}
		}
		
		renderer = SDL_CreateRenderer(m_Window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 21, 27, 31, 255);
		SDL_RenderClear(renderer);

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
		Pine::Networking::PineServerConnect("127.0.0.1", 2302);
	}

	void Core::PinePoll()
	{
		//Pine::Networking::PineServerNetworkLoop();

	}
	void Core::PineStart()
	{
		PINE_ENGINE_INFO("Application Started!");
		givenGame->Start();
		bool closeGame = false;
		SDL_Event event;
		rect.w = 100;
		rect.h = 100;
		
		//text = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
		while (!closeGame)
		{
			//PinePoll();
				if (givenGame->IsGameOver())
				{
					//PINE_ENGINE_INFO("Application Over");

				}
				if (givenGame->IsGameClosing())
				{

					PINE_ENGINE_INFO("Application Closing");

					closeGame = true;
					givenGame->Terminate();
				}
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT)
					{
						givenGame->GameClose();
					}
					if (event.type ==SDL_MOUSEBUTTONUP)
					{
						PINE_ENGINE_INFO("MOUSE PRESSED");
						Pine::PVector2f mousePos;
						int x;
						int y;
						SDL_GetMouseState(&x, &y);
						//PCircle c(300, 250, 300, rand() % 255, rand() % 255, rand() % 255);
						PRect r(Pine::PVector2f(x-32,y-32), Pine::PVector2f(64, 64));

						objects.push_back(r);
						PINE_ENGINE_ERROR(objects.size());
						if (objects.size() >3)
						{
							objects.erase(objects.begin() +2);
							PINE_ENGINE_ERROR(objects.size());


						}
						//if (IMG_LoadTexture(renderer, "res/grass.jpg") == NULL)
						//{
						//	PINE_ENGINE_ERROR("COULD NOT LOAD IMAGE");
						//}
						//SDL_Rect src;
						////draw here
						//src.x = 0;
						//src.y = 0;
						//src.w = 959;
						//src.h = 828;
						//SDL_Rect dst;
						//dst.x = x - 32;
						//dst.y = y - 32;
						//dst.w = 32*4;
						//dst.h = 32*4;

						//SDL_Texture* text = IMG_LoadTexture(renderer, "res/grass.jpg");
						//SDL_RenderCopy(renderer, text, &src, &dst);
						//r.SetTexture(IMG_LoadTexture(renderer, "res/grass.jpg"));
						r.SetColour(Pine::PColourf(rand() % 255, rand() % 255, rand() % 255, 255));
						r.Render(renderer);
						//c.Render(renderer);
						givenGame->OnMouseClick();


					}
				}
				if (!givenGame->IsGameMenu())//always runs while not in menu for opengl rendering controll
				{
					//PINE_ENGINE_INFO("Application not in Menu");

				}

				if (givenGame->IsGameRunning() || givenGame->IsGameMenu())//run all the time, even if the menu is open
				{
					//PINE_ENGINE_INFO("Application Running");
					

					//test circle



					givenGame->Update();
					//rect.x = rand() % 500;
					//rect.y = rand() % 500;
					//SDL_SetRenderTarget(renderer, text);
					//SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
					//SDL_RenderClear(renderer);
					//SDL_RenderDrawRect(renderer, &rect);
					//SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
					//SDL_RenderFillRect(renderer, &rect);
					//SDL_SetRenderTarget(renderer, NULL);
					//SDL_RenderCopy(renderer, text, NULL, NULL);
					SDL_RenderPresent(renderer);
				}
		}
	}

	void Core::PineCloseWindow()
	{

		SDL_Delay(3000);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

}