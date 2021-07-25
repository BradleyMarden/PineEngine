#pragma once
#include "EventSystem.h"
#include "PineObject.h"
#include <map>
#include <utility>
#include <typeinfo>

namespace Pine {
	namespace Priv
	{
		inline int GetUniqueObjectID()
		{
			static int _ComponentID = 0;

			_ComponentID++;

			return _ComponentID;
		}
	}

	template<class T> inline int GetObjectID()
	{
		static_assert(std::is_base_of<PineObject, T>::value, "object MUST inherit from class Scene");

		static int _ObjectID = Priv::GetUniqueObjectID();

		return _ObjectID;
	}


	class Scene
	{

	public:

				Scene(std::string p_Name);

		void	Update(float p_StepTime);

		void	Init();

		void	OnSceneLoad();

		void	OnSceneClose();

		void	Event(PEvent& e);

		void	DestroyPineObject();

		inline std::string GetName() { return m_SceneName; }

		inline void SetID(int p_ID) { m_ID = p_ID; }

		void Render();	
	

	
		int GetPineObjectCount() { return m_PineObjects.size(); }

		
		inline std::vector<std::shared_ptr<RendererComponent>> GetAllRenderComponentsinScene() { return _RendererComponents; };
		
	protected:

		std::string m_SceneName;

	private:
		int m_ID = 0 ;

		//All PineObjects currently in scene
		std::unordered_map<std::string, std::shared_ptr<PineObject>> m_PineObjects;

		//std::unordered_map<std::string, std::weak_ptr<RendererComponent>> _RendererComponents;
		std::vector<std::shared_ptr<RendererComponent>> _RendererComponents;

	public:
		//Returns unordered map of all PineObjects with type T
		template<class T> inline std::unordered_map<std::string, std::weak_ptr<T>> GetAllPineObjectsOfType()
		{
			//iterator of PineObject in scene
			std::unordered_map<std::string, std::weak_ptr<PineObject>>::iterator it = m_PineObjects.begin();

			//map to return
			std::unordered_map<std::string, std::weak_ptr<T>> map;

			//gets id associated with T type
			int _PineObjectID = GetObjectID<T>();

			//checks all PineObject in scene to see if they match type T
			while (it != m_PineObjects.end())
			{
				if (it->second->GetInstanceID() == _PineObjectID)
				{
					//match found, adding to return map
					map.try_emplace(it->first, static_cast<std::weak_ptr<T>>(it->second));
				}
				it++;
			}
			return map;
		}

		//Add PineObject of type to scene
		template<class T> inline void AddPineObject(std::shared_ptr <T> p_PineObject)
		{
			static_assert(std::is_base_of<PineObject, T>::value, "object MUST inherit from class PineObject");

			int _PineObjectID = GetObjectID<T>();

			p_PineObject->SetID(_PineObjectID);

			std::string _PineObjectName = p_PineObject->GetName();

			if (!std::get<bool>(m_PineObjects.try_emplace(_PineObjectName, p_PineObject)))
			{
				PINE_ENGINE_WARN("Pineobject '{0}' already exists in scene: {1}", _PineObjectName, m_SceneName);
			}
			PINE_ENGINE_WARN("Pineobject '{0}' added to scene: {1}", _PineObjectName, m_SceneName);
		}

		//Add empty PineObject of type T to scene
		template<class T> inline std::weak_ptr<T> AddPineObject(std::string p_ObjectName)
		{
			static_assert(std::is_base_of<PineObject, T>::value, "object MUST inherit from class PineObject");

			int _PineObjectID = GetObjectID<T>();

			std::shared_ptr <T> p_PineObject = std::make_shared<T>(p_ObjectName);

			p_PineObject->SetID(_PineObjectID);

			if (!std::get<bool>(m_PineObjects.try_emplace(p_ObjectName, p_PineObject)))
			{
				PINE_ENGINE_WARN("Pineobject '{0}' already exists in current scene: {1}", p_ObjectName, m_SceneName);
			}

			return static_cast<std::weak_ptr<T>>(p_PineObject);
		}


		//Get PineObject of type T from Scene
		template<class T> inline std::weak_ptr<T> GetPineObject(std::string p_PineObjectName)
		{
			std::unordered_map<std::string, std::shared_ptr<PineObject>>::iterator got = m_PineObjects.find(p_PineObjectName);

			if (got != m_PineObjects.end())
			{
				return std::static_pointer_cast<T>(got->second);
			}

			PINE_ASSERT("Pineobject '{0}' Could not be found in current scene: {1}", false, p_PineObjectName, m_SceneName);

			return {};
		}


	};
}