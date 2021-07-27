#pragma once
#include "Component.h"
#include "MaterialComponent.h"
#include "RendererComponent.h"
#include <utility>
#include <typeinfo>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
//#include "Renderer.h"
namespace Pine
{
	namespace Priv
	{
		inline int GetUniqueComponentID()
		{
			static int _ComponentID = 0;
			_ComponentID++;
			return _ComponentID;

		}
	}

	template<class T> inline int GetComponentID()
	{
		static_assert(std::is_base_of<Component, T>::value, "object MUST inherit from class Component");

		static int _ComponentID = Priv::GetUniqueComponentID();

		return _ComponentID;
	}
	
	 class PineObject
	{
	public:
		 
		 inline const int GetInstanceID() const { return m_InstanceID; }

		 PineObject(std::string p_Name) : m_Name(p_Name){}

		 void SetID(int p_ID) { m_InstanceID = p_ID; }

		 std::string inline GetName() { return m_Name; }

		 void	DestroyPineObject();

		 


	public:

		  virtual void Start() = 0;

		  virtual void Update(float p_StepTime) = 0;

		  virtual void OnTerminate() = 0;

		  virtual void Render() = 0;

		  virtual void UIRender() = 0;

		  virtual void Trigger(PEvent& e) = 0;
	protected:
		std::string m_Name;

	private:
		int m_InstanceID = 0;

		//All Components currently on PineObject
		std::unordered_map<std::string, std::shared_ptr<Component>> m_Components;

	public:


		//Returns unordered map of all Components on PineObject with type T
		template<class T> inline std::unordered_map<std::string, std::shared_ptr<T>> GetAllComponentsOfType()
		{
			//iterator of Component in scene
			std::unordered_map<std::string, std::shared_ptr<Component>>::iterator it = m_Components.begin();
			//map to return
			std::unordered_map<std::string, std::shared_ptr<T>> map;
			//gets id associated with T type
			int _ComponentID = GetComponentID<T>();
			//checks all Component in scene to see if they match type T
			while (it != m_Components.end())
			{
				if (it->second->GetInstanceID() == _ComponentID)
				{
					//match found, adding to return map
					map.try_emplace(it->first, std::static_pointer_cast<T>(it->second));

				}
				it++;
			}
			return map;
		}

		//Add empty Component of type T to PineObject
		template<class T> inline void AddComponentToPineObject(std::string p_ComponentName)
		{

			static_assert(std::is_base_of<Component, T>::value, "object MUST inherit from class Component");

			int _ComponentID = GetComponentID<T>();

			std::shared_ptr <T> _Component = std::make_shared<T>(p_ComponentName);

			_Component->SetID(_ComponentID);

			if (!std::get<bool>(m_Components.try_emplace(p_ComponentName, _Component)))
			{
				PINE_ENGINE_WARN("Component '{0}' already exists on current PineObject: {1}", p_ComponentName, m_Name);
			}
			PINE_ENGINE_WARN("Component '{0}' added to PineObject: {1}", p_ComponentName, m_Name);

		}

		//Add Component of type T to PineObject
		template<class T> inline void AddComponentToPineObject(std::shared_ptr<T> p_Component)
		{

			static_assert(std::is_base_of<Component, T>::value, "object MUST inherit from class Component");

			int _ComponentID = GetComponentID<T>();

			p_Component->SetID(_ComponentID);

			std::string _ComponentName = p_Component->GetName();

			if (!std::get<bool>(m_Components.try_emplace(_ComponentName, p_Component)))
			{
				PINE_ENGINE_WARN("Component '{0}' already exists on current PineObject: {1}", _ComponentName, m_Name);

			}
			PINE_ENGINE_WARN("Component '{0}' aded to PineObject: {1}", _ComponentName, m_Name);

		}

		//Get Component of type T with name p_ComponentName from PineObject
		template<class T> inline std::weak_ptr<T> GetComponent(std::string p_ComponentName)
		{
			std::unordered_map<std::string, std::shared_ptr<Component>>::iterator got = m_Components.find(p_ComponentName);

			if (got != m_Components.end())
			{
				//return static_cast<std::weak_ptr<T>>(got->second);
				return std::static_pointer_cast<T>(got->second);
			}

			PINE_ASSERT("Component '{0}' Could not be found on PineObject: {1}", false, p_ComponentName, m_Name);
			return {};
		}





	};
}