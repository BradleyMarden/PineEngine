#pragma once
#include "PineECS.h"
#include "PComponent.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <bitset>
#include <type_traits>
#include <array>
#include <iostream>

namespace Pine {

	class PComponent;
	constexpr std::size_t PMaxComponentsAllowed{ 20 };//can be changed
	using PComponentsArray = std::array <PComponent*, PMaxComponentsAllowed>;//components on each PGameObject
	using PComponentBitset = std::bitset<PMaxComponentsAllowed>;

	class PGameObject
	{
		
		
	public:
		PGameObject(const char* p_Name);
		~PGameObject();
		bool IsAlive() { return alive; }
		void Destroy() { alive = false; }
		//Adds a component of Type T to the current PGameObject
		template<typename type> type& AddComponent()
		{
			// check it doesnt already have the component.
			assert(!m_ComponentBitset[hasComponent<type>()]);

			//create raw ptr on the heap
			type* l_comp = new type();
			l_comp->m_PGO = this;

			//create a uptr and give it authority of the raw ptr just created above
			std::unique_ptr<PComponent> ptr{ l_comp };
			//add component to the vector
			Components.emplace_back(std::move(ptr));
			
			//add a component at the bit posotion 
			m_ComponentsAttached[::template GetComponentTypeID<type>()] = l_comp;

			//set the bit position to the id
			m_ComponentBitset[::template GetComponentTypeID<type>()] = true;

			//start the component
			l_comp->Start();

			//return reference
			return *l_comp;
		}
		//Checks to see if a component of Type T is attached to the current PGameObject.
		template <typename t> bool hasComponent()
		{
			return m_ComponentBitset[::template GetComponentTypeID<t>()];
		}

		//Retrieves a component of Type T from the current PGameObject.
		template<typename type> type& GetComponent() 
		{
			
			assert(m_ComponentBitset[hasComponent<type>()]);
			auto ptr(m_ComponentsAttached[::template GetComponentTypeID<type>()]);
			return *static_cast<type*>(ptr);
		}
		bool isAlive()
		{
			return alive;
		}

		void Update();
		void SetName(const char* p_Name) { m_Name = p_Name; }
		const char* GetName() { return m_Name; }

	private:
		PComponentsArray m_ComponentsAttached;
		PComponentBitset m_ComponentBitset;
		bool alive = true;
		bool CheckDestroyed();
		std::vector<std::unique_ptr<PComponent>> Components;
		const char* m_Name;

	};

}
/*
	-Get All Components
	-Get A Component
	-Remove A component
	-Has A Component
	-Set Active/NotActive
	-Update
	-Start
	-Array to hold Components.(Known at compile time)
*/