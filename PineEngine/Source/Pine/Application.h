#pragma once
#include "Core.h"
#include "sdl2/SDL.h"
#include "Networking.h"
#include "Log.h"
#include <stdio.h>
#include <iostream>
#include <memory>
#undef main
namespace Pine{
	class PINE_API Application
	{
	
	public:
		Application();
		~Application();

		void SetGameInitialize()   { SetGameState(PGAME_INITIALIZING); }
		void SetGameStarting()     { SetGameState(PGAME_STARTING); }
		void SetGameUpdate()       { SetGameState(PGAME_RUNNING); }
		void SetGamePaused()       { SetGameState(PGAME_PAUSED); }
		void SetGameWon()          { SetGameState(PGAME_WON); }
		void SetGameOver()         { SetGameState(PGAME_GAMEOVER); }
		void SetGameClose()        { SetGameState(PGAME_CLOSING); PGame->Terminate(); isExiting = true; }


		bool isGameInitializing()  { return *PState == PGAME_INITIALIZING; }
		bool isGameStarted()       { return *PState == PGAME_STARTING; }
		bool isGameRunning()       { return *PState == PGAME_RUNNING; }
		bool IsGamePaused()        { return *PState == PGAME_PAUSED; }
		bool IsGameOver()          { return *PState == PGAME_GAMEOVER; }
		bool IsGameClosing()       { return *PState == PGAME_CLOSING; }

		//Inherited Functions
		virtual void Update() {};
		virtual void Start() {};
		virtual void Initialize() {};
		virtual void Terminate() {};

		//game modes
		enum GameState
		{

			PGAME_INITIALIZING,
			PGAME_STARTING,
			PGAME_RUNNING,
			PGAME_PAUSED,
			PGAME_WON,
			PGAME_GAMEOVER,
			PGAME_CLOSING

		};

		bool Run(Application* game);//Called by entrypoint

		Application* GetPGame() { return PGame; }
		

		//TODO: basic network Functionality
		bool CreateNetwork();

		//TODO: basic rendering
		bool CreateRenderer();

	private:
		Application* PGame = nullptr;
		std::shared_ptr<GameState> PState = std::make_unique<GameState>();//create state for the application to be in
		inline std::shared_ptr<GameState> CheckState() { return PState; }//gets the state
		void SetGameState(GameState STATE) { *PState = STATE; }
		bool isExiting = false;

	
	};

	//to define in client
	Application* CreateApplication();
	
}

