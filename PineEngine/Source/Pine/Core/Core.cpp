#include "Core.h"

namespace Pine 
{
	Core::Core()
	{
	}
	Core::~Core()
	{
		delete m_Window;
		//delete m_PineRenderer;
	}


	void Core::PineInit(Game* game, uint8_t flags)
	{

		if (game == nullptr)
			return;

		#if DEBUG //initialises logging to the console
				Pine::Log::Init();
		#endif 

		givenGame = game;
		
		PINE_ENGINE_INFO("Welcome To Pine Engine!");
		PINE_ENGINE_INFO("Created By Bradley Marden : Licensed under Apache License");
		PINE_ENGINE_INFO("Refer to Documentation for Engine Use Cases");
		PINE_ENGINE_INFO("Application Starting...");
//		printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	//	printf("Renderer: %s\n", glGetString(GL_RENDERER));
		//printf("Version:  %s\n", glGetString(GL_VERSION));

		//check flags
		
		if (flags & Pine_Networking)
		{
			PINE_ASSERT("Error Initializing Networking.", Pine::Networking::PineNetworkingInit());
		}
		if (flags & Pine_Server)
		{
			//PINE_ASSERT("Error Initializing Networking.", Pine::Networking::PineNetworkingInit());
			PINE_ASSERT("Error Creating Server.", Pine::Networking::PineServerCreate(2302, 4));
		}
		
		
		
		//start game flow
		givenGame->Initialize();
        
        //maybe we should check if we need atleast one window open
        if (Window::GetMainWindow() == nullptr) {
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

		
		//Setup IMGUI
		/*IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_Impl
		2_InitForOpenGL(m_Window->GetMainWindow(), &m_Window->GetMainWindowContext());
		ImGui_ImplOpenGL3_Init(glsl_version);*/

		//TEST EVENT FUNCTION 
		Pine::EventSystem::RegisterEventCallback(BIND_EVENT(Core::Trigger));

		
	}
	
	//TEST EVENT FUNCTION
	void Core::Trigger(PEvent& e) 
	{
		if (&e == nullptr) { return; }
		if (e.GetEventType() == Pine::EventType::WindowResize)
		{
			std::cout << "------------------------------------- " << std::endl;

			const char* name = dynamic_cast<Pine::WindowResizeEvent&>(e).GetWindowName();
			std::cout << "Window: " << name << std::endl;
			//e.is_Handled = true;

		}

		if (e.GetEventType() == Pine::EventType::WindowClose)
		{
			std::cout << "------------------------------------- " << std::endl;

			const char* name = dynamic_cast<Pine::WindowCloseEvent&>(e).GetWindowName();
			std::cout << "Window: " << name  << std::endl;
			Window::CloseWindow(name);
			if (Window::GetMainWindow() == nullptr)
			{
				givenGame->GameClose();
			}
			//e.is_Handled = true;
		}
		 if (e.GetEventType() == Pine::EventType::MouseButtonDown)
		{
			 std::cout << "------------------------------------- " << std::endl;

			 const char* name = dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetWindowName();
			 std::cout << "Window: "<< name << std::endl;
			// e.is_Handled = true;

		}
		 if (e.GetEventType() == Pine::EventType::MouseButtonUp)
		{
			 std::cout << "------------------------------------- " << std::endl;

			 const char* name = dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetWindowName();
			 std::cout << "Window: "<< name << std::endl;
			// e.is_Handled = true;
		}
	}
	void Core::PineStart()
	{
		PINE_ENGINE_INFO("Application Started!");
		

		bool closeGame = false;
		bool hasStarted = false;
		while (!closeGame)
		{
			frameStart = SDL_GetTicks();
			switch (givenGame->GetGameState())
			{
				default:
					break;
				case Game::GameState::RUNNING:
					
					if (!hasStarted)
					{
						PINE_ENGINE_WARN("Starting");
						givenGame->Start();
						hasStarted = true;
					}
					ApplicationRunning();
					//Renderer::Flush();
					Renderer::BeginBatch();

					HandleEvents();
					break;
				case Game::GameState::GAMEOVER:
					break;
				case Game::GameState::CLOSING:
					PINE_ENGINE_INFO("Application Closing");
					closeGame = true;
					//Renderer::Shutdown();
					givenGame->Terminate();
					break;
			}
			//limit FPS
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime && Renderer::limitFPS)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}
	}

	void Core::ApplicationRunning()
	{
		//runs Update on the game client
		givenGame->Update();
		//now render graphics
		//Renderer->Render();
		//now ui
		//RenderUI();
	}

	
	void Core::RenderUI() 
	{
		//SDL_SetRenderDrawColor(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Renderer, 21, 27, 31, 255);

	


		/*// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(m_Window->GetMainWindow());
		//IMGUI CREATE FRAME
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(Window::GetMainWindow() <= 1000 ? ImVec2(PINE_WINDOW_WIDTH / 3, PINE_WINDOW_HEIGHT / 3) : ImVec2(350,150), ImGuiCond_Always);

		

		static float f = 0.0f;
		//IMGUI START
		ImGui::Begin("PineEngine");
		ImGui::Text("Window Width: %i", PINE_WINDOW_WIDTH );
		ImGui::Text("Window Height: %i", PINE_WINDOW_HEIGHT);

		if (ImGui::Button("Limit FPS to 60"))
			limitFPS = !limitFPS;
		PVector2f mousePos = Input::GetMousePosition();
		ImGui::Text("Mouse X pos: %f",mousePos.X);
		ImGui::Text("Mouse Y pos: %f",mousePos.Y);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		//IMGUI END

		//IMGUI RENDER
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/


	

		
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
					heldE = e;
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
			}

			if (e.type == SDL_WINDOWEVENT) 
			{
				switch (e.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
					{
						Pine::WindowResizeEvent* event = new Pine::WindowResizeEvent(e.window.data1, e.window.data2, SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID)));
						Window::GetMainWindow()->s_WindowSize = glm::vec2(e.window.data1, e.window.data2);
						
						break;
					}
					case SDL_WINDOWEVENT_CLOSE:
					{	
						SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID));
						Pine::WindowCloseEvent* event = new Pine::WindowCloseEvent(SDL_GetWindowTitle(SDL_GetWindowFromID(e.window.windowID)));
					}
				}
			}
		}
	}

	void Core::PineCloseEngine()
	{

		if (givenGame != nullptr) {
			//ImGui_ImplOpenGL3_Shutdown();
			//ImGui_ImplSDL2_Shutdown();
			//ImGui::DestroyContext();
		}
		SDL_Quit();
	}

}
