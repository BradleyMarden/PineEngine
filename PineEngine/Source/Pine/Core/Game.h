#pragma once
#include "sdl2/SDL.h"
#include <memory>
#include "PineAPI.h"


namespace Pine {
	class PINE_API Game
	{

		///////////////////*Game States*\\\\\\\\\\\\\\\\\\\\\\\\

	private:
		enum GameState { MENU,RUNNING,GAMEOVER,CLOSING};
		GameState st;

	protected:
		inline void SetState(GameState STATE) { st = STATE; }
		bool isExiting = false;

	public:
		inline void GameRun()		   { SetState(RUNNING);     }
		inline void GameOver()		   { SetState(GAMEOVER);    }
		inline void GameClose()        { SetState(CLOSING);     }
		inline void GameMenu()         { SetState(MENU); }
		
		
		inline bool IsGameRunning()    { return st == RUNNING;  }
		inline bool IsGameOver()       { return st == GAMEOVER; }
		inline bool IsGameClosing()    { return st == CLOSING;  }
		inline bool IsGameMenu()       { return st == MENU; }
		//inline GameState CheckGameState() { return st; }
		inline bool CheckIfexiting()   { return isExiting;      }

		///////////////////*Controll Functions*\\\\\\\\\\\\\\\\\\\\\\\\
		
		virtual void Update()      {};
		virtual void Start()       {};
		virtual void Initialize()  {};
		virtual void Terminate()   {};

	};
}


