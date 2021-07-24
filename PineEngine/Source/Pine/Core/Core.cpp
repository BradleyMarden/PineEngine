#include "Core.h"

namespace Pine 
{

	Core::Core()
	{
	}
	Core::~Core()
	{
	}


	void Core::PineInit(Game* game, uint8_t flags)
	{

		if (game == nullptr)
			return;

		givenGame = game;
#if DEBUG //initialises logging to the console
		Pine::Log::Init();
#endif 
		

		

		PINE_ENGINE_INFO("Welcome To Pine Engine!");
		PINE_ENGINE_INFO("Created By Bradley Marden : Licensed under Apache License");
		PINE_ENGINE_INFO("Refer to Documentation for Engine Use Cases");
		PINE_ENGINE_INFO("Application Starting...");


		//check flags
		if (flags & Pine_Networking)
			PINE_ASSERT("Error Initializing Networking.", Pine::Networking::PineNetworkingInit());

		if (flags & Pine_Server)
			PINE_ASSERT("Error Creating Server.", Pine::Networking::PineServerCreate(2302, 4));
		
		//ComponentSystem::InitComponentSystem();
		
		//start game flow
		givenGame->Initialize();
        
        //maybe we should check if we need atleast one window open
        if (Window::GetMainWindow() == nullptr) 
		{
            PINE_ENGINE_WARN("No window created, creating one automatically...");
            Window::CreateNewWindow("Default Window");
        }

		if (!Renderer::GetIconSet())
			Renderer::SetWindowIcon("Assets/PineEngineTransparent.png");

		Renderer::InitRendering();

		givenGame->GameRun();

		if (!givenGame->IsGameRunning())//if game is initialized
		{
			PINE_ENGINE_INFO("Failed to Run Application");

			givenGame->GameClose();//just for safety

			return;
		}

		// EVENT FUNCTION 
		Pine::EventSystem::RegisterEventCallback(BIND_EVENT(Core::Trigger));
		
	}
	

	
	void Core::PineStart()
	{
		PINE_ENGINE_INFO("Application Started!");

		bool closeGame = false;

		bool hasStarted = false;
		
		while (!closeGame)
		{
			TimeStep();

			switch (givenGame->GetGameState())
			{
				default:
					break;

				case Game::GameState::MENU: 
				{
					break;
				}
				
				case Game::GameState::RUNNING:
				{
					if (!hasStarted)
					{
						PINE_ENGINE_WARN("Starting");
						givenGame->Start();
						hasStarted = true;
					}
					ApplicationRunning();
					HandleEvents();
					break;
				}

				case Game::GameState::GAMEOVER:
					break;

				case Game::GameState::CLOSING:
				{
					PINE_ENGINE_INFO("Application Closing");
					closeGame = true;
					givenGame->Terminate();
					break;
				}
			}

			FPSLimit();
		}
	}

	void Core::ApplicationRunning()
	{
		givenGame->Update(m_StepTime);
	}

	void Core::HandleEvents()//all keyboard and mouse events are handled here
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			static SDL_Event heldE;
			switch (e.type)
			{
				default:
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					givenGame->OnMouseClick();
					Input::MousePressed(&e);
					Pine::MouseButtonDownEvent* event = new Pine::MouseButtonDownEvent(e.button.x, e.button.y, Input::MouseDown(&e), false, SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID)));
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					Input::MouseReleased(&e);
					Pine::MouseButtonUpEvent* event = new Pine::MouseButtonUpEvent(e.button.x, e.button.y, Input::MouseDown(&e), false, SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID)));
					break;
				}
				case SDL_KEYDOWN:
				{
					Input::KeyPressed(&e);
					Pine::KeyDownEvent* event = new Pine::KeyDownEvent(Input::KeyDown(&e));
					break;
				}
				case SDL_KEYUP:
				{
					Pine::KeyUpEvent* event = new Pine::KeyUpEvent(Input::KeyDown(&e));
					break;
				}
				case SDL_MOUSEWHEEL:
				{
					Pine::MouseScrollEvent* event = new Pine::MouseScrollEvent(e.wheel.y);
					break;
				}
			}

			if (e.type == SDL_WINDOWEVENT) 
			{
				switch (e.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
					{
						Pine::WindowResizeEvent* event = new Pine::WindowResizeEvent(e.window.data1, e.window.data2, SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID)));
						Window::GetMainWindow()->s_WindowSize = glm::vec2(e.window.data1, e.window.data2);
						glViewport(0, 0, Window::GetMainWindow()->s_WindowSize.x, Window::GetMainWindow()->s_WindowSize.y);
						
						break;
					}
					case SDL_WINDOWEVENT_CLOSE:
					{	
						SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID));
						Pine::WindowCloseEvent* event = new Pine::WindowCloseEvent(SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID)));
						break;
					}
				}
			}
		}
	}

	
	// EVENT FUNCTION
	void Core::Trigger(PEvent& e)
	{
		if (&e == nullptr) { return; }
		if (e.GetEventType() == Pine::EventType::WindowResize)
		{
			PINE_ENGINE_INFO("------------------------------------- ");

			const char* name = dynamic_cast<Pine::WindowResizeEvent&>(e).GetWindowName();
			PINE_ENGINE_INFO("Window: {0}", name);
			//e.is_Handled = true;

		}

		if (e.GetEventType() == Pine::EventType::WindowClose)
		{
			PINE_ENGINE_INFO("------------------------------------- ");
			const char* name = dynamic_cast<Pine::WindowCloseEvent&>(e).GetWindowName();
			PINE_ENGINE_INFO("Window: {0}", name);

			Window::CloseWindow(name);
			if (Window::GetMainWindow() == nullptr)
			{
				givenGame->GameClose();
			}
			//e.is_Handled = true;
		}
		if (e.GetEventType() == Pine::EventType::MouseButtonDown)
		{
			PINE_ENGINE_INFO("------------------------------------- ");

			const char* name = dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetWindowName();
			PINE_ENGINE_INFO("Window: {0}", name);

			// e.is_Handled = true;

		}
		if (e.GetEventType() == Pine::EventType::MouseButtonUp)
		{
			PINE_ENGINE_INFO("------------------------------------- ");

			const char* name = dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetWindowName();
			PINE_ENGINE_INFO("Window: {0}", name);
			// e.is_Handled = true;
		}
	}
	void Core::PineCloseEngine()
	{

		if (givenGame != nullptr) {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}
		SDL_Quit();
		IMG_Quit();
	}
	void Core::TimeStep()
	{
		//set frame time
		frameStart = SDL_GetTicks();
		m_StepTime = frameStart - m_LastStepTime;
		m_LastStepTime = frameStart;

	}

	void Core::FPSLimit()
	{
		//limit FPS
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime && Renderer::limitFPS)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}
