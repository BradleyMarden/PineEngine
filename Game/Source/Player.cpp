#pragma once
#include "Player.h"


void Player::Start() 
{
	Pine::EventSystem::RegisterEventCallback(BIND_EVENT(Player::Trigger));
	
	//cache render component
	m_RendComp = GetComponent<Pine::RendererComponent>("RendererComponent");
	m_RendComp.lock()->DrawQuad({ Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName)/2-150,Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName)/2-150 }, { 30 ,30}, 1, "Player");

	m_RendComp.lock()->DrawQuad({ 40, 0 },	{ 70.0f ,320.0f }, 1, "ob");
	m_RendComp.lock()->DrawQuad({ 300, 0 }, { 70.0f ,200.0f }, 1, "ob");
	m_RendComp.lock()->DrawQuad({ 800, 0 }, { 70.0f ,300.0f }, 1, "ob");     
	
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


	if (Pine::Input::GetKeyDown(SDL_SCANCODE_K))
	{
		//shoot = true;
		std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = m_RendComp.lock()->GetAllQuads();
		for (size_t i = 0; i < _Quads.size(); i++)
		{
			if (_Quads[i]->s_ID == 1) 
			{
				m_RendComp.lock()->DeleteQuad(_Quads[i]);
			}
		}
	}

	if (Pine::Input::GetKeyDown(SDL_SCANCODE_O))
	{
		//shoot = true;
		std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = m_RendComp.lock()->GetAllQuads();
		for (size_t i = 0; i < _Quads.size(); i++)
		{
			if (_Quads[i]->s_Name == "LOGO")
			{
				m_RendComp.lock()->DeleteQuad(_Quads[i]);
			}
		}
	}




	std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = m_RendComp.lock()->GetAllQuads();
	glm::vec2 _Pos = m_RendComp.lock()->GetQuad("Player")->s_Pos;
	glm::vec2 _Size = m_RendComp.lock()->GetQuad("Player")->s_Size;
		for (size_t i = 0; i < _Quads.size(); i++)
		{
			if (_Quads[i]->s_Name == "LOGO")
			{
				//m_RendComp.lock()->DeleteQuad(_Quads[i]);
				_Quads[i]->s_Pos.y += 1;
				if (m_RendComp.lock()->CheckCollision(_Pos, _Quads[i]->s_Pos, _Size, _Quads[i]->s_Size))
				{
					m_RendComp.lock()->DeleteQuad(_Quads[i]);
				}
			}
			if (_Quads[i]->s_Name == "ob")
			{
				_Quads[i]->s_Pos.x -= 1;

				if (_Quads[i]->s_Pos.x < -_Quads[i]->s_Size.x)
				{
					_Quads[i]->s_Pos.x = 915;
				}

			}
			if (_Quads[i]->s_Pos.y == 540 )
			{
				m_RendComp.lock()->DeleteQuad(_Quads[i]);
			}

			
			//if (_Quads[i]->s_Pos.y <= _Pos.y + 30)
			//{
				//m_RendComp.lock()->DeleteQuad(_Quads[i]);

			///}
		}
		if (Pine::Input::GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_RendComp.lock()->GetQuad("Player")->s_Pos.y += 0.5 * p_StepTime;

		}
		else
		{
			m_RendComp.lock()->GetQuad("Player")->s_Pos.y -= 0.7 *p_StepTime;
		}
		m_RendComp.lock()->GetQuad("Player")->s_Pos.y = glm::clamp(m_RendComp.lock()->GetQuad("Player")->s_Pos.y, 50.0f, 400.0f);


		

 }

void Player::OnTerminate() 
{
}

static glm::vec2 pos = {400,400};
void Player::Render() 
{


	

	if (Pine::Input::GetKeyDown(SDL_SCANCODE_F))
	{
		for (size_t i = 0; i < 100; i++)
		{
			int x = (rand() % 750) + 50; //picks a random number out of 48

			int y = (rand() % 500) - 300;//picks a random number out of 10

			int size = (rand() % 60) + 15;

			glm::vec4 col = { 0.0f ,1.0f, 0.0f ,1.0f };

			m_RendComp.lock()->DrawQuad({ x,y }, { size ,size }, 2, 1);
			
		}
		std::string _Pos = std::to_string((double)Pine::Input::GetMousePosition().X) + "," + std::to_string((double)Pine::Input::GetMousePosition().Y);

		Pine::Networking::PineSendGlobalPacket("aaaaa");
		//Pine::Networking::PineSendGlobalDataPacket(Pine::Input::GetMousePosition().X, Pine::Input::GetMousePosition().Y);
	}

	if (Pine::Input::GetMouseDown(1))
	{
		int size = (rand() % 60) + 15;
		m_RendComp.lock()->DrawQuad({ Pine::Input::GetMousePosition().X,-Pine::Input::GetMousePosition().Y + 540 }, { size ,size }, 1, "LOGO");

	}

	if (Pine::Input::GetKeyDown(SDL_SCANCODE_G))
	{
		float d = (rand() % 1); //picks a random number out of 48

		PINE_WARN("Delay {0}", d);

		for (size_t i = 0; i < 100; i++)
		{
			int x = (rand() % 750) + 50; //picks a random number out of 48

			int y = (rand() % 500) - 300;//picks a random number out of 10

			int size = (rand() % 60) + 15;

			glm::vec4 col = { 0.0f ,1.0f, 0.0f ,1.0f };

			m_RendComp.lock()->DrawQuad({ Pine::Input::GetMousePosition().X,-Pine::Input::GetMousePosition().Y +540 }, { size ,size }, 1, "LOGO");
		}

	}

	if (shoot)
	{
		glm::vec4 col = { 0.0f ,1.0f, 0.0f ,1.0f };

		Pine::Renderer::DrawQuad({ m_PlayerPos.x,m_PlayerPos.y }, { 100.0f ,100.0f }, col);
	}
	
}

void Player::UIRender() 
{

}

void Player::MoveUp(float p_StepTime)
{
	m_PlayerPos.y += 0.5 * p_StepTime;

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

		/*
		std::vector<int> _results;

		std::stringstream _ss(_Packet);

		while (_ss.good())
		{
			std::string _subString;
			std::getline(_ss, _subString, ',');
			_results.push_back(std::stoi(_subString));
		}
		*/
		e.is_Handled = true;
	}
}
