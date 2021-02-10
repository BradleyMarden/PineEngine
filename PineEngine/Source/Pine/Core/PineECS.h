#pragma once
#include "Core.h"
#include <stddef.h>
#define Pine_Max_Components_Allowed 1000
#define Pine_Max_Entities_Allowed 10000

namespace Pine {

	
	struct PComponent
	{
		const char* Name;
		void* data;
	};

	struct PEntity
	{
		int ComponentCount;
		PComponent Components[Pine_Max_Components_Allowed];//Limited amount of components allowed, can be removed.
	};

	struct PSystem//variadic Function
	{
		void (*SystemFunction)(PEntity& p_Entity, std::initializer_list<PComponent>& p_Componenets);//Passed Function for the system to call
		int ComponentCount;//Number of components
		const char* ArcheytypedComponents[Pine_Max_Components_Allowed];//components required for the system fucntion
	};
	struct PECSWorld 
	{
		int EntityCount;
		int SystemCount;
		PSystem* Systems;
		PEntity** Entities; //Double ptr to retain original ptr memory Pos
	};

	
	class PineECS
	{
	public:

		/*Entity*/
		PEntity* CreateEntity();
		void DestroyEntity();
		void QueryEntity();

		/*Component*/
		PComponent CreateComponent(const char* p_Name, void* p_data);//Create a component but is not assigned to anthing
		void AddComponent(PEntity& p_Entity, PComponent p_Component);//Add component to an entity

		/*System*/
		void CreateSystem(void(*p_SystemFucntion)(PEntity& p_Entity, std::initializer_list<PComponent>& p_Componenets), int p_ComponentCount, std::vector<char*>p_Components);//parameter pack, for unknown number of components

		/*ECS Tools*/
		void Query();
		void ECSUpdate();
		void CheckECSData();
		void CleanupECS();
		void InitECS();
	private:
		PECSWorld m_PWorld;

	};
}



