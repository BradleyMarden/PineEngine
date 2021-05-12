#include "Core.h"

namespace Pine {
	Core::Core()
	{

	}
	Core::~Core()
	{
		//hello
	}


	Core::Core(const char* m_windowName, unsigned int m_Width, unsigned int m_Height)
	{
		Pine::Log::Init();

		if (glewInit() != GLEW_OK)
		{
			PINE_ENGINE_ERROR("OPENGL NO INITIALIZED!");
		}
		//SDL_GL_CreateContext()
		SDL_Init(SDL_INIT_VIDEO);
		m_Window = SDL_CreateWindow(m_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (m_Window == NULL)
		{
			auto a = SDL_GetError();
			PINE_ENGINE_ERROR("COULD NOT CREATE WINDOW {a}", a);
		}

		//glViewport(0, 0, m_Width, m_Height);
		SDL_Surface* screenSurface = NULL;
		//Get window surface
		screenSurface = SDL_GetWindowSurface(m_Window);

		SDL_UpdateWindowSurface(m_Window);
		//Wait two seconds
		SDL_Delay(2000);
		//glewInit();
	}

	
	void Core::PineOpenWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height)
	{
		Pine::Log::Init();

		/*if (glewInit() != GLEW_OK)
		{
			PINE_ENGINE_ERROR("OPENGL NO INITIALIZED!");
		}*/
		//SDL_GL_CreateContext()
		SDL_Init(SDL_INIT_VIDEO);
		m_Window = SDL_CreateWindow(m_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		//glViewport(0, 0, m_Width, m_Height);

	}

	bool Core::PineInit(Game* game, uint8_t flags)
	{
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
	

	void Core::PineStart()
	{
		PINE_ENGINE_INFO("Application Started!");
		givenGame->Start();
		SDL_Event event;
		bool closeGame = false;
		
		while (!closeGame)
		{
			frameStart = SDL_GetTicks();
			switch (givenGame->GetGameState())
			{
			default:
				break;
			case Game::GameState::RUNNING:
				HandleEvents();
				ApplicationRunning();
				//Draw(false);
				break;
			case Game::GameState::GAMEOVER:
				break;
			case Game::GameState::CLOSING:
				PINE_ENGINE_INFO("Application Closing");
				closeGame = true;
				givenGame->Terminate();
				break;
			}

			//limit FPS
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}
	}

	void Core::ApplicationRunning()
	{
		

		//runs Update on the game client
		givenGame->Update();

		//now finally render graphics
		
	}
	void Core::Test()
	{
		PINE_ENGINE_INFO("REDRAWING...");
		Draw(false);
	}

	
	void Core::Draw(bool firstDraw)
	{
		SDL_RenderClear(renderer);
		/*if (firstDraw)
		{
			objects[objects.size() - 1]->SetRenderer(renderer);
			objects[objects.size() - 1]->Render();
		}
		else {
			//draws all objects

			for (int i = 0; i < objects.size(); i++)
			{
				//need to fix redrawing the same objects. Huge memory usage, especially with re-drawn images.
				objects[i]->SetRenderer(renderer);
				objects[i]->Render();
			}
		}*/
		SDL_SetRenderDrawColor(renderer, 21, 27, 31, 255);
		SDL_RenderPresent(renderer);
	}

	void Core::HandleEvents()//all keyboard and mouse events are handled here
	{
		SDL_Event e;
		SDL_PollEvent(&e);
		switch (e.type)
		{
		default:
			break;
		case SDL_MOUSEBUTTONDOWN:
		//	PINE_ENGINE_WARN("MOUSE BUTTON PRESSED");
			givenGame->OnMouseClick();
			Input::MousePressed(&e);
			break;
		case SDL_MOUSEBUTTONUP:
		//	PINE_ENGINE_WARN("MOUSE BUTTON RELEASED");
			Input::MouseReleased(&e);
			break;

		case SDL_KEYDOWN:
			Input::KeyPressed(&e);
			break;

		case SDL_QUIT:
			givenGame->GameClose();
			PINE_ENGINE_WARN("CLOSING GAME");
			break;
			
		}
	}

	Pine::PVector2f Core::GetMousePos()
	{
		Pine::PVector2f mousePos;
		int x;
		int y;
		SDL_GetMouseState(&x, &y);

		mousePos.X = x;
		mousePos.Y = y;
		return mousePos;
	}

	void Core::PineCloseWindow()
	{

		//SDL_Delay(3000);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

}
