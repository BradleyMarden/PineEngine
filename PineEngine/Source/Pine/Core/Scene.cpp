#pragma once
#include "Scene.h"

namespace Pine {


	Scene::Scene(std::string p_Name):
		m_SceneName(p_Name)
	{
	
	}


	void Scene::OnSceneLoad()
	{

		if (m_PineObjects.size() == 0)
		{
			PINE_ENGINE_WARN("There are zero PineObjects attached to scene: {0}", m_SceneName);
		}
		for (auto x : m_PineObjects)
		{
			x.second->Start();
			PINE_ENGINE_WARN("Initialized PineObject: {0}", x.second->GetName());
		}
	}

	void Scene::Update(float p_StepTime)
	{

		for (auto x : m_PineObjects) 
		{
			//PINE_WARN(x.first);
			x.second->Update(p_StepTime);
		}
	}

	void Scene::Render()
	{
		_RendererComponents.clear();

		for (auto x : m_PineObjects)
		{
			x.second->Render();

			for (auto _Comp : x.second->GetAllComponentsOfType<RendererComponent>()) 
			{
				_RendererComponents.push_back(_Comp.second);
			}
		}


	}
	void Scene::OnSceneClose() 
	{
		for (auto x : m_PineObjects)
		{
			x.second->OnTerminate();
			//m_PineObjects.erase(x.first);
		}
	}

	
}