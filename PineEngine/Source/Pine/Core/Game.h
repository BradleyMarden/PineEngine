#pragma once
//#include <sdl2/SDL.h>
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
		inline GameState GetGameState(){ return st;				}
		inline void GameRun()		   { SetState(RUNNING);     }
		inline void GameOver()		   { SetState(GAMEOVER);    }
		inline void GameClose()        { SetState(CLOSING);     }
		
		
		inline bool IsGameRunning()    { return st == RUNNING;  }
		inline bool IsGameOver()       { return st == GAMEOVER; }
		inline bool IsGameClosing()    { return st == CLOSING;  }
		inline bool CheckIfexiting()   { return isExiting;      }

		///////////////////*Controll Functions*\\\\\\\\\\\\\\\\\\\\\\\\
		
		virtual void Update()      {};
		virtual void Start()       {};
		virtual void Initialize()  {};
		virtual void Terminate()   {};
		virtual void OnMouseClick()   {};

	private:

		GameState st;

	protected:
		inline void SetState(GameState STATE) { st = STATE; }
		bool isExiting = false;
	};
}

//$//(SolutionDir)PineEngine\Vendor\spdlog\include;$(SolutionDir)PineEngine\Vendor\SDL2-2.0.12\include;$(SolutionDir)PineEngine\Vendor\enet-1.3.16\include;
