#pragma once
//#include <sdl2/SDL.h>
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <memory>
//#include "PineAPI.h"


namespace Pine {
	class Game
	{
		//the game files. COntroll game play
		///////////////////*Game States*\\\\\\\\\\\\\\\\\\\\\\\\


	public:
		enum GameState { RUNNING, GAMEOVER, CLOSING };
		inline GameState GetGameState() { return st; }
		inline void GameRun() { SetState(RUNNING); }
		inline void GameOver() { SetState(GAMEOVER); }
		inline void GameClose() { SetState(CLOSING); }


		inline bool IsGameRunning() { return st == RUNNING; }
		inline bool IsGameOver() { return st == GAMEOVER; }
		inline bool IsGameClosing() { return st == CLOSING; }
		inline bool CheckIfexiting() { return isExiting; }

		///////////////////*Controll Functions*\\\\\\\\\\\\\\\\\\\\\\\\
		
		virtual void Update() {};
		virtual void Start() {};
		virtual void Initialize() {};
		virtual void Terminate() {};
		virtual void OnMouseClick() {};

		//NTS if not set, send event to remind developer.
		inline void SetWindowParameters(int p_Width, int p_Height, const char* p_WindowName) { m_WindowWidth = p_Width; m_WindowHeight = p_Height; m_WindowName = p_WindowName; g_ParametersSet = true; }
		static int GetWindowWidth() { return m_WindowWidth; }
		static int GetWindowHeight() { return m_WindowHeight; }
		static const char& GetWindowName() { return *m_WindowName; }
		static inline int m_WindowWidth;
		static inline int m_WindowHeight;
		static inline bool g_ParametersSet;
		static inline const char* m_WindowName;

	private:

		GameState st;
		


	protected:
		inline void SetState(GameState STATE) { st = STATE; }
		bool isExiting = false;
	};

	Game* CreateGame();
}
#define PINE_WINDOW_WIDTH Pine::Game::GetWindowWidth()

#define PINE_WINDOW_HEIGHT Pine::Game::GetWindowHeight()

#define PINE_WINDOW_NAME &Pine::Game::GetWindowName()

//$//(SolutionDir)PineEngine\Vendor\spdlog\include;$(SolutionDir)PineEngine\Vendor\SDL2-2.0.12\include;$(SolutionDir)PineEngine\Vendor\enet-1.3.16\include;
