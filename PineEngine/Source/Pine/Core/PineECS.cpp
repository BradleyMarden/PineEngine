#include "PineECS.h"
namespace Pine {
	/*Entity*/
	PEntity* PineECS::CreateEntity() 
	{
		PEntity* l_Entity = new PEntity();
		l_Entity->ComponentCount = 0;
		m_PWorld.Entities[m_PWorld.EntityCount] = l_Entity;
		m_PWorld.EntityCount++;
		return l_Entity;

	}
	void PineECS::DestroyEntity(){}
	void PineECS::QueryEntity() {}


	/*Component*/
	PComponent PineECS::CreateComponent(const char* p_Name, void* p_data) 
	{
		PComponent l_Component;
		l_Component.Name = p_Name;
		l_Component.data = &p_data;
		return l_Component;
	}

	void PineECS::AddComponent(PEntity* p_Entity, PComponent p_Component) 
	{
		p_Entity->Components[p_Entity->ComponentCount] = p_Component;
		p_Entity->ComponentCount++;
	
	}

	/*System*/ //MIGHT NOT NEED THE COMPONENT COUNT, CAN USE THE VECTOR SIZE
	void PineECS::CreateSystem(void(*p_SystemFucntion)(), int p_ComponentCount, std::vector<char*>p_s) //parameter pack, for unknown number of components
	{
		PINE_ENGINE_INFO("Creating system with Fucntion: [%p]", p_SystemFucntion);
		PSystem l_System;
		l_System.SystemFunction = p_SystemFucntion;
		l_System.ComponentCount = p_ComponentCount;
		
		for(int i = 0; i<p_s.size(); i++)
		{
			l_System.ArcheytypedComponenets[i] = p_s[i];
		}
		m_PWorld.Systems[m_PWorld.SystemCount] = l_System;
		m_PWorld.SystemCount++;
	}



	/*ECS Tools*/
	void PineECS::Query() {}
	void PineECS::CheckECSData() {}
	void PineECS::CleanupECS() {}
	void PineECS::InitECS() {}
}