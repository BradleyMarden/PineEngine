#pragma once
#include "Player.h"


void Player::Start() 
{
	Pine::EventSystem::RegisterEventCallback(BIND_EVENT(Player::Trigger));
	
	//cache render component
	m_RendComp = GetComponent<Pine::RendererComponent>("RendererComponent");

	//m_RendComp.lock()->LoadTexture("PlayerArt", "Assets/PineEngineText.png");
	m_RendComp.lock()->LoadTexture("Particle", "Assets/Particle1.png");
	m_RendComp.lock()->LoadTexture("PlayerArt", "Assets/PineEngineGold.png");

	m_RendComp.lock()->DrawQuad({ Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName) / 2 - 150,20 }, { 30 ,30 }, "PlayerArt", { 1.0,1.0,1.0,1.0 }, "Player", Pine::RendererComponent::TOP);

	
}

void Player::Update(float p_StepTime) 
{


	if (m_PlayerPos.y < 500 && shoot)//Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName))
	{
		MoveUp(p_StepTime);
	}
	

	std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = m_RendComp.lock()->GetAllQuads();
	glm::vec2 _Pos = m_RendComp.lock()->GetQuad("Player")->s_Pos;
	glm::vec2 _Size = m_RendComp.lock()->GetQuad("Player")->s_Size;

	

	if (Pine::Input::GetKeyDown(SDL_SCANCODE_SPACE))
	{
		m_RendComp.lock()->GetQuad("Player")->s_Pos.y += 0.5 * p_StepTime;
		int x = _Pos.x;
		int y = (rand() % (int)_Size.y / 2 + 1);
		y += _Pos.y;
		m_RendComp.lock()->DrawQuad({ x,y }, { 15 ,15 }, "Particle", { 1.0,1.0,0.0,1.0 }, "Particle", Pine::RendererComponent::NONE);
	}
	else
	{
		m_RendComp.lock()->GetQuad("Player")->s_Pos.y -= 0.5 *p_StepTime;
		int x = _Pos.x;
		int y = (rand()% (int)_Size.y / 2 + 1);
		y += _Pos.y;
		//x += (rand() % 1 + 30);
		//y += (rand() % x + 2);

		m_RendComp.lock()->DrawQuad({ x,y }, { 10 ,10 }, "Particle", { 1.0,1.0,1.0,1.0 }, "Particle", Pine::RendererComponent::NONE);
	}
	m_RendComp.lock()->GetQuad("Player")->s_Pos.y = glm::clamp(m_RendComp.lock()->GetQuad("Player")->s_Pos.y, 50.0f, 400.0f);

	//std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = GetComponent<Pine::RendererComponent>("RendererComponent").lock()->GetAllQuads();
	for (size_t i = 0; i < _Quads.size(); i++)
	{
		if (_Quads[i]->s_Pos.x < -_Quads[i]->s_Size.x / 2)
		{
			m_RendComp.lock()->DeleteQuad(_Quads[i]);

		}
		if (_Quads[i]->s_Name == "Particle")
		{

			_Quads[i]->s_Pos.x -= 2;


		}


	}


 }



void Player::Render() 
{
	
	
}

void Player::UIRender() 
{
	/*glm::vec2 _Pos = m_RendComp.lock()->GetQuad("Player")->s_Pos;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(Pine::Window::GetWindowGLData(Pine::Window::GetMainWindow()->s_WindowName)->s_Window);
	//IMGUI CREATE FRAME
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName)/2), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_Always);

	static float f = 0.0f;
	//IMGUI START
	ImGui::Begin("PLAYER");
	ImGui::Text("Player x pos: %f", _Pos.x);
	ImGui::Text("Player y pos: %f", _Pos.y);
	ImGui::End();
	//IMGUI END

	//IMGUI RENDER
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	*/
}

void Player::MoveUp(float p_StepTime)
{
	m_PlayerPos.y += 0.5 * p_StepTime;

}
void Player::OnTerminate()
{

}

void Player::Trigger(Pine::PEvent& e) 
{

	if (&e == nullptr) { return; }

}
