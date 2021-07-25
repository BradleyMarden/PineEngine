#pragma once
#include "OrthographicCameraController.h"
namespace Pine
{
	OrthographicCameraController::OrthographicCameraController(float p_AspectRatio, bool p_Rotation): m_Cam(0* m_Zoom, 920 * m_Zoom, 0, 540)
	{
		 m_AspectRatio = p_AspectRatio;
		 m_Rotation = p_Rotation;
	
		Pine::EventSystem::RegisterEventCallback(BIND_EVENT(OrthographicCameraController::trigger));

	}

	void OrthographicCameraController::OnUpdate(int p_StepTime)
	{
	
		if (Input::GetKeyDown(SDL_SCANCODE_W))
		{
			m_Pos.y += m_CamMoveSpeed * p_StepTime;
		}
		else if (Input::GetKeyDown(SDL_SCANCODE_S))
		{
			m_Pos.y -= m_CamMoveSpeed * p_StepTime;

		}

		if (Input::GetKeyDown(SDL_SCANCODE_A))
		{
			m_Pos.x -= m_CamMoveSpeed * p_StepTime;

		}
		else if (Input::GetKeyDown(SDL_SCANCODE_D))
		{
			m_Pos.x += m_CamMoveSpeed * p_StepTime;
		}

		if (m_Rotation)
		{
			if (Input::GetKeyDown(SDL_SCANCODE_Q))
			{
				m_Rotation  += m_CamRotSpeed * p_StepTime;

			}
			if (Input::GetKeyDown(SDL_SCANCODE_E))
			{
				m_Rotation -= m_CamRotSpeed * p_StepTime;
			}

			m_Cam.SetRotation(m_Rotation);
		}
		m_Cam.SetPosition(m_Pos);
	}
	void OrthographicCameraController::trigger(PEvent& e) 
	{
		if (&e == nullptr) { return; }
		if (e.GetEventType() == Pine::EventType::MiddleMouseScroll)//changes zoom level
		{
			std::cout << "------------------------------------- " << std::endl;

			float offset = dynamic_cast<Pine::MouseScrollEvent&>(e).GetOffset();
			std::cout << "OFFSET: " << offset << std::endl;
			m_Zoom -= offset;
			m_Cam.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
			e.is_Handled = true;

		}
		if (e.GetEventType() == Pine::EventType::WindowResize)//changes aspect ratio
		{
			std::cout << "------------------------------------- " << std::endl;

			const char* name = dynamic_cast<Pine::WindowResizeEvent&>(e).GetWindowName();
			std::cout << "Window: " << name << std::endl;
			m_AspectRatio = dynamic_cast<Pine::WindowResizeEvent&>(e).GetWidth() / dynamic_cast<Pine::WindowResizeEvent&>(e).GetHeight();
			m_Cam.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
			e.is_Handled = true;

		}
	
	}
}	//glm::mat4 projection = glm::ortho(0.0f, Window::GetMainWindow()->s_WindowSize.x, 0.0f, Window::GetMainWindow()->s_WindowSize.y, -1.0f, 1.0f);//converts screen space to values between -1:1
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//can be used to imitate move camera(works by shifting all onjects in scene)
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//controls positon of object on screen
	//glm::mat4 mvp = projection * view * model;