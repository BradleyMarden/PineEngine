#pragma once
#include "Component.h"
#include "Log.h"


//We need to allocate blocks of memory ready to store components. This way, we can keep components stored next to each other in mem. Also helps for cacheing.
//We could use insertion sort to sort a list of all components at init as component types wont change after runtime, then store in a dictionary the name of the comp type and index first found at. 
namespace Pine
{
	/*namespace Priv
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


	class ComponentSystem
	{
	public:

		static inline void InitComponentSystem() 
		{
		
		
		}
		//Registers component type to contiguous memory
		//static void RegisterComponent(Component* p_CompToRegister);

		template<class T> static inline void RegisterComponent() 
		{

			static_assert(std::is_base_of<Component, T>::value, "object MUST inherit from class Component");

			int _ComponentID = GetComponentID<T>();
			if (std::find(std::begin(m_Components), std::end(m_Components), _ComponentID) != std::end(m_Components))
			{
				std::cout << "Component has already been registered." << std::endl;
			}
			else
			{
				for (size_t i = 0; i < sizeof(m_Components); i++)
				{
					if (m_Components[i] == 0)
					{
						m_Components[i] = _ComponentID;
						return;
					}
				}
			}
		}

		template<class T> static inline void AddComponent(const int p_PineObjectInstanceID) 
		{
		
			T* _Component = new T();

			for (size_t i = 0; i < sizeof(m_ComponentObjects); i++)
			{
				if (m_ComponentObjects[i] == nullptr)
				{
					m_ComponentObjects[i] = _Component;
					return;
				}
			}
		
		}

	private:

		static int m_Components[10];
		static Component* m_ComponentObjects[1000];


	};*/
}