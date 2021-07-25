#pragma once
#include "Player.h"


void Player::Start() 
{
	Pine::EventSystem::RegisterEventCallback(BIND_EVENT(Player::Trigger));
	m_RendComp = GetComponent<Pine::RendererComponent>("RendererComponent");

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

		for (size_t i = 0; i < _Quads.size(); i++)
		{
			if (_Quads[i]->s_Name == "LOGO")
			{
				//m_RendComp.lock()->DeleteQuad(_Quads[i]);
				_Quads[i]->s_Pos.y += 1;
			}

			if (_Quads[i]->s_Pos.y == 540 )
			{
				m_RendComp.lock()->DeleteQuad(_Quads[i]);
			}
		}
}

void Player::OnTerminate() 
{
}
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
			//Pine::Renderer::DrawQuad({x,y }, { size ,size }, 2);
			m_RendComp.lock()->DrawQuad({ x,y }, { size ,size }, 2, 1);

		}
	}

	if (Pine::Input::GetMouseDown(1))
	{
		int size = (rand() % 60) + 15;
		m_RendComp.lock()->DrawQuad({ Pine::Input::GetMousePosition().X,-Pine::Input::GetMousePosition().Y + 540 }, { size ,size }, 1, "LOGO");
	}

	if (Pine::Input::GetKeyDown(SDL_SCANCODE_G))
	{
		float d = (rand() % 1); //picks a random number out of 48
		//SDL_Delay(d);
		PINE_WARN("Delay {0}", d);

		for (size_t i = 0; i < 100; i++)
		{
			
			int x = (rand() % 750) + 50; //picks a random number out of 48
			int y = (rand() % 500) - 300;//picks a random number out of 10
			int size = (rand() % 60) + 15;
			glm::vec4 col = { 0.0f ,1.0f, 0.0f ,1.0f };
			//Pine::Renderer::DrawQuad({x,y }, { size ,size }, 2);
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

}
