#pragma once
#include "Player.h"


void Player::Start() 
{
	Pine::EventSystem::RegisterEventCallback(BIND_EVENT(Player::Trigger));
	
	//cache render component
	m_RendComp = GetComponent<Pine::RendererComponent>("RendererComponent");

	m_RendComp.lock()->LoadTexture("PineLogo", "Assets/PineEngineText.png");
	m_RendComp.lock()->LoadTexture("Triangle", "Assets/tri.png");
	m_RendComp.lock()->LoadTexture("TriangleTop", "Assets/triTop.png");

	m_RendComp.lock()->LoadTexture("BG", "Assets/Background.png");
	m_RendComp.lock()->LoadTexture("Vinette", "Assets/Vinette.png");

	m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 0.0,1.0,0.0,1.0 }, "thing", Pine::RendererComponent::TOP);
	m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 1.0,0.0,0.0,1.0 }, "thing1", Pine::RendererComponent::TOP);
	m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 0.0,0.0,1.0,1.0 }, "thing2", Pine::RendererComponent::TOP);
	m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 0.0,1.0,1.0,1.0 }, "thing3", Pine::RendererComponent::TOP);

	m_RendComp.lock()->DrawQuad({ 40, 20 },	{ 200 ,320.0f }, "Triangle", { 1.0,1.0,1.0,1.0 },"ob", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ 300, 20 }, { 200 ,200.0f }, "Triangle", { 1.0,1.0,1.0,1.0 },"ob",Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ 800, 20 }, { 200 ,300.0f }, "Triangle", { 1.0,1.0,1.0,1.0 },"ob",Pine::RendererComponent::NONE);

	m_RendComp.lock()->DrawQuad({ 50, 20 }, { 200 ,320.0f }, "TriangleTop", { 1.0,1.0,1.0,1.0 }, "ob", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ 600, 20 }, { 200 ,200.0f }, "TriangleTop", { 1.0,1.0,1.0,1.0 }, "ob", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ 400, 20 }, { 200 ,300.0f }, "TriangleTop", { 1.0,1.0,1.0,1.0 }, "ob", Pine::RendererComponent::NONE);

	m_RendComp.lock()->DrawQuad({ Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName) / 2 - 150,20 }, { 30 ,30 }, "test", { 1.0,1.0,1.0,1.0 }, "Player", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ 300,20 }, { 30 ,30 }, "PineLogo", { 1.0,1.0,1.0,0.5 }, "play", Pine::RendererComponent::NONE);
	m_RendComp.lock()->DrawQuad({ 0,0 }, { Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName),Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) }, "Vinette", { 1.0,1.0,1.0,1.0 }, "Vinette", Pine::RendererComponent::TOP);
	m_RendComp.lock()->DrawQuad({ 0,0 }, { Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName),Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) }, "BG", { 1.0,1.0,1.0,1.0 }, "Background", Pine::RendererComponent::BOTTOM);


	
}

void Player::Update(float p_StepTime) 
{


	if (m_PlayerPos.y < 500 && shoot)//Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName))
	{
		MoveUp(p_StepTime);
	}
	else
	{
		shoot = false;
	}
	PINE_ENGINE_INFO(m_RendComp.lock()->GetTexture("test"));
	


	std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = m_RendComp.lock()->GetAllQuads();
	glm::vec2 _Pos = m_RendComp.lock()->GetQuad("play")->s_Pos;
	glm::vec2 _Size = m_RendComp.lock()->GetQuad("play")->s_Size;
	for (size_t i = 0; i < _Quads.size(); i++)
	{

		if (_Quads[i]->s_Name == "ob")
		{
			glm::vec2 _PillarSize = _Quads[i]->s_Size;
			glm::vec2 _PillarPos = _Quads[i]->s_Pos;

			glm::vec2 _PillarPosL = _PillarPos;

			glm::vec2 _PillarPosR = _PillarPos;
			_PillarPosR.x += _PillarSize.x;
			glm::vec2 _PillarPosT = _PillarPos;
			_PillarPosT.x += _PillarSize.x/2;
			_PillarPosT.y = _PillarSize.y;
			m_RendComp.lock()->GetQuad("thing")->s_Pos = _PillarPosT;
			m_RendComp.lock()->GetQuad("thing1")->s_Pos = _PillarPosL;
			m_RendComp.lock()->GetQuad("thing2")->s_Pos = _PillarPosR;
			m_RendComp.lock()->GetQuad("thing3")->s_Pos = _Pos;
			
			if (m_RendComp.lock()->CheckWithTriangleCollision(_Pos, _Quads[i]->s_Pos, _Size, _Quads[i]->s_Size))
			{
				PINE_ENGINE_WARN("ITS IN");

			}
			else
			{
				//PINE_ENGINE_WARN("ITS OUT");

			}
			if (_Quads[i]->s_Pos.x < -70)
			{
				_Quads[i]->s_Pos.x = Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName) + 70;
			}
			_Quads[i]->s_Pos.x -= 1;
		}
	}
	if (Pine::Input::GetKeyDown(SDL_SCANCODE_SPACE))
	{
		m_RendComp.lock()->GetQuad("play")->s_Pos.y += 0.5 * p_StepTime;
			
	}
	else
	{
		m_RendComp.lock()->GetQuad("play")->s_Pos.y -= 0.7 *p_StepTime;
	}
	m_RendComp.lock()->GetQuad("play")->s_Pos.y = glm::clamp(m_RendComp.lock()->GetQuad("play")->s_Pos.y, 50.0f, 400.0f);


	if (Pine::Input::GetMouseDown(1))
	{
		int size = (rand() % 60) + 15;
		m_RendComp.lock()->DrawQuad({ Pine::Input::GetMousePosition().X,-Pine::Input::GetMousePosition().Y + 540 }, { size ,size }, "PineLogo", { 1.0,1.0,1.0,1.0 }, "LOGO", Pine::RendererComponent::NONE);

	}


	if (shoot)
	{
		glm::vec4 col = { 0.0f ,1.0f, 0.0f ,1.0f };

		Pine::Renderer::DrawQuad({ m_PlayerPos.x,m_PlayerPos.y }, { 100.0f ,100.0f }, col);
	}
	
		
 }



void Player::Render() 
{
	
	
}

void Player::UIRender() 
{
	glm::vec2 _Pos = m_RendComp.lock()->GetQuad("play")->s_Pos;

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

	if (e.GetEventType() == Pine::EventType::MouseButtonDown)
	{
		 e.is_Handled = true;

		if (dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() == Pine::Input::LEFTSINGLECLICK)
		{
			shoot = true;

			m_PlayerPos.y = -dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetY() + 540;

			m_PlayerPos.x = dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetX();

			PINE_INFO("PlayerPos.y {0}", -dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetY());
		}
	}

	if (e.GetEventType() == Pine::EventType::NetworkPacketRecieve)
	{
		std::string _Packet = dynamic_cast<Pine::NetworkPacketEvent&>(e).GetPacket();
		e.is_Handled = true;
	}
}
