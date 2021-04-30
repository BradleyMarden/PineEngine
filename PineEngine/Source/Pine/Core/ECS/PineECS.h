#pragma once
#include "../../Logging/Log.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <bitset>
#include <type_traits>
#include <iostream>
#include "PGameObject.h"
#include "PComponent.h"
namespace Pine
{
	class PComponent;
	class PGameObject;
	using PComponentID = std::size_t;
	namespace priv {
		inline PComponentID GetComponentUniqueTypeID() noexcept
		{
			//This is where the ID is generated.
			static PComponentID l_TypeID{ 0u };
			return l_TypeID++;
		}
	}
	
	//gets the type of component
	template<typename T> inline PComponentID GetComponentTypeID() noexcept
	{
		static_assert(std::is_base_of<PComponent, T>::value, "Object must inherit from Component!");//error checking
		/*
		Because this is static, when a component is called(T), that specific component type will only generate a ID once,
		as a result all subsequent components of the same type(T) that call this will return the same type ID


		EG:
		Player.Transform.GetComponentTypeID(); = 0
		Mesh.GetComponentTypeID(); =1
		Box.Transform.GetComponentTypeID(); = 0

		transform has been allocated the type of 0 and Mesh has been allocated 1.
		this system needs re-working as it could cause issues with networking.
		*/
		
		static PComponentID l_TypeID{ priv::GetComponentUniqueTypeID() };
		return l_TypeID;
	}

	
	class PECS
	{


	public:
		PECS();
		~PECS();
		static PGameObject& CreateGameObject(const char* p_Name);

		 void Refresh();

		 static std::vector<std::unique_ptr<PGameObject>> m_PGameObjects;

		void Update();
	private:


		
		

	};

}

/*
	The aim of this ECS is to allow the users to the engine to create PObjects, made up of a series of Components. 
	These components will be comprised of Pre-Made ones, however the user will be able to create their own ones, if need be. We then want the user to be able to:

	In the case of the PObject:
	-Get All Components
	-Get A Component
	-Remove A component
	-Has A Component
	-Set Active/NotActive
	-Update
	-Start
	-Array to hold Components.(Known at compile time)

	In the case of the Component:
	-Set the Entity(On Construction)
	-Update(Virtual)
	-Start(Virtual)


	In the case of the Pine Entity Component System:
	-Refresh to remove non-active PGameObject
	-Add PGameObject 
	-Remove PGameObject 
	-Get all PGameObjects
	-Vector to hold PObjects(Not Known at compile time)

	PGameObject myObj
	PECS.CreatePObject(&myObj);


*/

