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

	void PineECS::AddComponent(PEntity& p_Entity, PComponent p_Component) 
	{
		p_Entity.Components[p_Entity.ComponentCount] = p_Component;
		p_Entity.ComponentCount++;
	
	}

	/*System*/ //MIGHT NOT NEED THE COMPONENT COUNT, CAN USE THE VECTOR SIZE
	void PineECS::CreateSystem(void(*p_SystemFucntion)(PEntity& p_Entity ,std::initializer_list<PComponent>& p_Componenets), int p_ComponentCount, std::vector<char*>p_Components) //parameter pack, for unknown number of components
	{
		PSystem l_System;
		l_System.SystemFunction = p_SystemFucntion;
		l_System.ComponentCount = p_ComponentCount;//not really needed.
		
		for(int i = 0; i< p_Components.size(); i++)
		{
			l_System.ArcheytypedComponents[i] = p_Components[i];
		}
		m_PWorld.Systems[m_PWorld.SystemCount] = l_System;
		m_PWorld.SystemCount++;
	}



	/*ECS Tools*/
	void PineECS::ECSUpdate() 
	{
		for (int i = 0; i < m_PWorld.SystemCount; i++)
		{
			for (size_t k= 0; k < m_PWorld.EntityCount; k++)
			{
				//if the entity has the componenets needed, run the archeytyped function
				//m_PWorld.Entities[k].
				int l_NumOfComponents = m_PWorld.Entities[k]->ComponentCount;
				//for (int f = 0; f < l_NumOfComponents; f++)
				//{
					if (m_PWorld.Systems[i].ComponentCount == l_NumOfComponents)
					{
						m_PWorld.Systems[i].SystemFunction(;
					}
				//}
				


			}
		}
	
	}

	void PineECS::Query() {}
	void PineECS::CheckECSData() {}
	void PineECS::CleanupECS() {}
	void PineECS::InitECS() {}
}