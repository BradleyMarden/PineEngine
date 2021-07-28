#pragma once
#include "Obstacles.h"


void Obstacles::Start()
{
	Pine::EventSystem::RegisterEventCallback(BIND_EVENT(Obstacles::Trigger));

	//cache render component
	m_RendComp = GetComponent<Pine::RendererComponent>("RendererComponent");

	m_RendComp.lock()->LoadTexture("Triangle", "Assets/BottomTriangle.png");
	m_RendComp.lock()->LoadTexture("TriangleTop", "Assets/TopTriangle.png");


	float _Height = Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) - 180;
	float _Width = Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName) - 180;
	m_LastPos = _Width;
	m_RendComp.lock()->DrawQuad({ _Width+40, 0 },	{ 200 ,320.0f }, "Triangle", m_BottomTriColor,"ObstacleB", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 450, 0 }, { 200 ,200.0f }, "Triangle",m_BottomTriColor,"ObstacleB",Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 800, 0 }, { 200 ,300.0f }, "Triangle",m_BottomTriColor,"ObstacleB",Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 500, 0 }, { 200 ,300.0f }, "Triangle",m_BottomTriColor,"ObstacleB",Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 100, 0 }, { 200 ,300.0f }, "Triangle",m_BottomTriColor,"ObstacleB",Pine::RendererComponent::NONE);

	m_RendComp.lock()->DrawQuad({ _Width + 50, _Height }, { 200 ,180 }, "TriangleTop",	m_TopTriColor, "ObstacleT", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 600, _Height }, { 200 ,180 }, "TriangleTop", m_TopTriColor, "ObstacleT", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 400, _Height }, { 200 ,180 }, "TriangleTop", m_TopTriColor, "ObstacleT", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 200, _Height }, { 200 ,180 }, "TriangleTop", m_TopTriColor, "ObstacleT", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ _Width + 900, _Height }, { 200 ,180 }, "TriangleTop", m_TopTriColor, "ObstacleT", Pine::RendererComponent::NONE);



}

void Obstacles::Update(float p_StepTime)
{
	std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = GetComponent<Pine::RendererComponent>("RendererComponent").lock()->GetAllQuads();
	for (size_t i = 0; i < _Quads.size(); i++)
	{
		//Obstacle off screen
		if (_Quads[i]->s_Pos.x < -_Quads[i]->s_Size.x/2)
		{
			if (_Quads[i]->s_Name == "ObstacleT")
			{
				_Quads[i]->s_Pos.x = m_LastPos;
				_Quads[i]->s_Size.y = _Quads[i]->s_Size.x = (rand() % 90 + 140);
				_Quads[i]->s_Pos.y = Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) - _Quads[i]->s_Size.y;
				m_PassedScreenCounter++;

				

			}
			if (_Quads[i]->s_Name == "ObstacleB")
			{
				_Quads[i]->s_Pos.x = m_LastPos;
				_Quads[i]->s_Size.y = _Quads[i]->s_Size.x = (rand() % 90 + 140);
				m_PassedScreenCounter++;

			}
		

		}
		//scroll obstacle
		_Quads[i]->s_Pos.x -= m_ScrollSpeed;

		//set obstacle color
		if (_Quads[i]->s_Name == "ObstacleT")
		{
			_Quads[i]->s_Color = m_TopTriColor;
		}
		if (_Quads[i]->s_Name == "ObstacleB")
		{
			_Quads[i]->s_Color = m_BottomTriColor;

		}
	}
	//some game logic
	if (m_PassedScreenCounter > m_SpeedIncreaseRequirement)
	{
	
		m_ScrollSpeed += 0.5f;
		m_PassedScreenCounter = 0;
		m_SpeedIncreaseRequirement += 10;

		if (m_SpeedIncreaseRequirement > 10)
		{
			m_BottomTriColor = {0.0f,1.0f,1.0f,1.0f};
			m_TopTriColor = { 1.0f,1.0f,0.0f,1.0f };

		}
	}
}

void Obstacles::Reset()
{
	std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = GetComponent<Pine::RendererComponent>("RendererComponent").lock()->GetAllQuads();
	for (size_t i = 0; i < _Quads.size(); i++)
	{

			if (_Quads[i]->s_Name == "ObstacleT")
			{
				_Quads[i]->s_Pos.x += m_LastPos;
				_Quads[i]->s_Size.y = _Quads[i]->s_Size.x = (rand() % 90 + 140);
				_Quads[i]->s_Pos.y = Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) - _Quads[i]->s_Size.y;

			}
			if (_Quads[i]->s_Name == "ObstacleB")
			{
				_Quads[i]->s_Pos.x += m_LastPos;
				_Quads[i]->s_Size.y = _Quads[i]->s_Size.x = (rand() % 90 + 140);
			}


		
	}
	m_LastPos = Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName) - 180;
	m_PassedScreenCounter = 0;
	m_SpeedIncreaseRequirement = 0;
	m_ScrollSpeed = 1;
	m_BottomTriColor = { 1.0,1.0f,1.0f,1.0f };
	m_TopTriColor = { 1.0,1.0f,1.0f,1.0f };
}




void Obstacles::Render()
{


}

void Obstacles::UIRender()
{
	ImGui::SetNextWindowPos(ImVec2(0, Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) / 2), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_Always);

	static float f = 0.0f;
	//IMGUI START
	ImGui::Begin("Obstacles");
	ImGui::SliderFloat4("Top Tri Colors", &m_TopTriColor.r, 0.0f, 1.0f);
	ImGui::SliderFloat4("Bottom Tri Colors", &m_BottomTriColor.r, 0.0f, 1.0f);
	ImGui::SliderInt("ScrollSpeed", &m_ScrollSpeed, 0.0f, 10.0f);
	ImGui::Text("Score: %i", m_PassedScreenCounter);
	ImGui::End();
	//IMGUI END
}

void Obstacles::OnTerminate()
{

}

void Obstacles::Trigger(Pine::PEvent& e)
{

	if (&e == nullptr) { return; }

}
