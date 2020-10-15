#include "Application.h"

namespace Pine
{
   


	Application::Application()
	{

	}
    
    //=====================================================================================Public Functions:
    bool Application::CreateNetwork()
    {
        return Pine::Networking::InitNetwork();

    }

    bool Application::CreateRenderer()
    {
    
        return true;
    }

    //=====================================================================================Private Functions:

    Application::~Application()
    {
       
    }

    bool Application::Run(Application* game)
    {
        SetGameInitialize();
        if (isGameInitializing())
        {
            PINE_ENGINE_INFO("APP INITIALIZING");
            PGame = game;
            PGame->Initialize();
            if (!isExiting)
            {
                SetGameStarting();
            }
        }
        SDL_Event event;


#pragma region window


        //WINDOW LAYER=============================================================

        SDL_Window* window;                    // Declare a pointer

        SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

        // Create an application window with the following settings:
        window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
        );

        // Check that the window was successfully created
        if (window == NULL) {
            // In the case that the window could not be made...
            printf("Could not create window: %s\n", SDL_GetError());
            return 1;
        }
        //WINDOW LAYER=============================================================
#pragma endregion

        if (isGameStarted())
        {
            PINE_ENGINE_INFO("APP STARTED");
            game->Start();
            SetGameUpdate();
        }

        if (!isExiting)
        {

            while (isGameRunning())
            {
                PINE_ENGINE_INFO("APP LOOPING");
                if (IsGamePaused())
                {
                    PINE_ENGINE_INFO("APP PAUSED");//TODO add paused Functionality
                    break;

                }
                else if (IsGameOver())
                {
                    PINE_ENGINE_INFO("APP GAME OVER");//TODO add Game Over Functionality
                    break;

                }
                else if (IsGameClosing())
                {
                    PINE_ENGINE_INFO("APP CLOSING");
                    break;
                }


                game->Update();
                while (SDL_PollEvent(&event))//TODO Improve checking
                {
                    // --- Processing of exit events ---
                    if (event.type == SDL_QUIT)
                    {
                        *PState = PGAME_CLOSING;
                        break;
                    }
                }
            }
        }
        PINE_ENGINE_INFO("APP CLOSING");
        SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
        // Close and destroy the window
        SDL_DestroyWindow(window);
        // Clean up
        SDL_Quit();
        return true;
    }

 }
   


