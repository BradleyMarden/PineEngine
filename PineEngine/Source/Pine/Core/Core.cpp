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
		/*if (Pine::Log::Init() == true)
		{

			if (glewInit() != GLEW_OK)
			{
				PINE_ENGINE_ERROR("OPENGL NO INITIALIZED!");
				//std::cout << "herer";
			}
			else
			{
				PINE_ENGINE_INFO("OPENGL INITIALIZED!");

			}
		}*/
		//std::cout << "herer";

		
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
		if (glewInit() != GLEW_OK)
		{
			PINE_ENGINE_ERROR("OPENGL NO INITIALIZED!");
		}
		else
		{
			PINE_ENGINE_INFO("OPENGL INITIALIZED!");

		}
		//glewInit();
	}

	
	void Core::PineOpenWindow()
	{

		#if DEBUG
			Pine::Log::Init();
		#endif // DEBUG
			
		//SDL_GL_CreateContext()
		SDL_Init(SDL_INIT_VIDEO);
		
		m_Window = SDL_CreateWindow(PINE_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PINE_WINDOW_WIDTH, PINE_WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		m_Context = SDL_GL_CreateContext(m_Window);
		if (glewInit() != GLEW_OK)
		{
			PINE_ENGINE_ERROR("GLEW NOT INITIALIZED!");
		}
		else
		{
			PINE_ENGINE_INFO("GLEW INITIALIZED!");

		}
		
		//glViewport(0, 0, m_Width, m_Height);

	}void Core::PineOpenSecondWindow(const char* m_windowName, unsigned int m_Width, unsigned int m_Height)
	{
		//Pine::Log::Init();

		/*if (glewInit() != GLEW_OK)
		{
			PINE_ENGINE_ERROR("OPENGL NO INITIALIZED!");
		}*/
		//SDL_GL_CreateContext()
		SDL_Init(SDL_INIT_VIDEO);
		

		m_SecondWindow = SDL_CreateWindow(m_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

		SourceShader localShaders = Pine::Shader::LoadShader("Assets/Shaders/default.PineShader");

		localshader = Shader::CreateShader(localShaders.VertexSource, localShaders.FragmentSource);
		glUseProgram(localshader);


		float VertexArray[12] =
		{
			-0.5f, -0.5f,//0
			0.5f, -0.5f,//1
			0.5f,0.5f,//2

			-0.5f,0.5f,//3


		};
		unsigned int indicies[6]
		{
		0,1,2,
		2,3,0
		
		};
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), VertexArray,GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);//vertex position

		unsigned int ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

		int lID = glGetUniformLocation(localshader, "u_Color");
		
		//lID will return -1 if the uniform is not used or set. this is a feature of opengl to cleanup.
		if (lID != -1)
		{
			glUniform4f(lID, 1.0f, 0.5f, 0.2f, 1.0f);

		}
		else
		{
			
			PINE_ENGINE_WARN("Could not find uniform");
		}


		//Setup IMGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(m_Window, m_Context);
		ImGui_ImplOpenGL3_Init(glsl_version);


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
				Render();
				ApplicationRunning();
				//Draw(false);
				break;
			case Game::GameState::GAMEOVER:
				break;
			case Game::GameState::CLOSING:
				PINE_ENGINE_INFO("Application Closing");
				glDeleteProgram(localshader);

				closeGame = true;
				givenGame->Terminate();
				break;
			}

			//limit FPS
			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime && !limitFPS)
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

	void Core::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		RenderUI();
		SDL_GL_SwapWindow(m_Window);
	}

	void Core::RenderUI() 
	{
		
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(m_Window);
		ImGui::NewFrame();

		

		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;


		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		if (ImGui::Button("Limit FPS to 60"))
			limitFPS = !limitFPS;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();


		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
		//Shutdown
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyRenderer(renderer);
		SDL_GL_DeleteContext(m_Context);
		SDL_DestroyWindow(m_Window);
		SDL_DestroyWindow(m_SecondWindow);
		SDL_Quit();
	}

}
