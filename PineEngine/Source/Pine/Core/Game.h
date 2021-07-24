#pragma once
//#include <sdl2/SDL.h>
#include <Log.h>
#include <SDL.h>
#include <memory>
#include "Scene.h"
#include <map>
#include <utility>

namespace Pine {
	namespace Priv
	{
		inline int GetUniqueSceneID()
		{
			static int _ComponentID = 0;

			_ComponentID++;

			return _ComponentID;

		}
	}

	template<class T> inline int GetSceneID()
	{
		static_assert(std::is_base_of<Scene, T>::value, "object MUST inherit from class Scene");

		static int _SceneID = Priv::GetUniqueSceneID();

		return _SceneID;
	}
	
	class Game
	{
		//the game files. COntroll game play
		///////////////////*Game States*\\\\\\\\\\\\\\\\\\\\\\\\


	public:
		enum GameState { MENU, RUNNING, GAMEOVER, CLOSING };

		inline GameState GetGameState() { return st; }

		inline void GameRun() { SetState(RUNNING); }

		inline void GameOver() { SetState(GAMEOVER); }

		inline void GameClose() { SetState(CLOSING); PINE_ENGINE_WARN("State Close"); }


		inline bool IsGameRunning() { return st == RUNNING; }

		inline bool IsGameOver() { return st == GAMEOVER; }

		inline bool IsGameClosing() { return st == CLOSING; }

		inline bool CheckIfexiting() { return isExiting; }

		///////////////////*Controll Functions*\\\\\\\\\\\\\\\\\\\\\\\\
		
		virtual void Update(int p_StepTime) {};

		virtual void Start() {};

		virtual void Initialize() {};

		virtual void Terminate() {};

		virtual void OnMouseClick() {};

		void CloseScene(std::string p_SceneName);
	protected:

		inline void SetState(GameState STATE) { st = STATE; }

		bool isExiting = false;

	private:
		GameState st;

		std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;

	public:
		//Add Scene to game ready for use
		template<class T> inline void AddScene(std::shared_ptr <T> p_Scene)
		{
			static_assert(std::is_base_of<Scene, T>::value, "object MUST inherit from class Scene");

			int _SceneID = GetSceneID<T>();

			p_Scene->SetID(_SceneID);

			std::string _SceneName = p_Scene->GetName();

			if (!std::get<bool>(m_Scenes.try_emplace(_SceneName, p_Scene)))
			{
				PINE_ENGINE_WARN("Scene '{0}' already exists in Game", _SceneName);
			}
			PINE_ENGINE_WARN("Scene '{0}' added to Game", _SceneName);
		}


		//Load Scene from Game, runs that scene
		template<class T> inline void LoadScene(std::string p_SceneName)
		{
			std::unordered_map<std::string, std::shared_ptr<Scene>>::iterator got = m_Scenes.find(p_SceneName);

			if (got != m_Scenes.end())
			{
				got->second->OnSceneLoad();

				int _NumOfPineObjects = got->second->GetPineObjectCount();

				PINE_ENGINE_WARN("Scene '{0}' Loaded with: {1} PineObjects", p_SceneName, _NumOfPineObjects);
				return;
			}

			PINE_ENGINE_WARN("Scene '{0}' Could not be found in current Game instance", p_SceneName);
		}

		//Get Scene from Game
		template<class T> inline std::weak_ptr<T> GetScene(std::string p_SceneName)
		{
			std::unordered_map<std::string, std::shared_ptr<Scene>>::iterator got = m_Scenes.find(p_SceneName);

			if (got != m_Scenes.end())
			{
				return static_cast<std::weak_ptr<T>>(got->second);
			}

			PINE_ENGINE_WARN("Scene '{0}' Could not be found in current Game context", p_SceneName);

			return std::weak_ptr<T>();
		}
	};
	Game* CreateGame();
}

