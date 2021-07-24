#pragma once
#include "Log.h"
#include "EventSystem.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Input.h"
#include "Core.h"
#include "OrthographicCamera.h"

namespace Pine {

	//glm::mat4 projection = glm::ortho(0.0f, Window::GetMainWindow()->s_WindowSize.x, 0.0f, Window::GetMainWindow()->s_WindowSize.y, -1.0f, 1.0f);//converts screen space to values between -1:1
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//can be used to imitate move camera(works by shifting all onjects in scene)
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//controls positon of object on screen
	//glm::mat4 mvp = projection * view * model;
	class OrthographicCameraController {

	public:
		OrthographicCameraController(float p_AspectRatio, bool rotation);
		void OnUpdate(int p_StepTime);
		void trigger(PEvent& e);
		OrthographicCamera& GetCamera()  { return m_Cam; }

	private:
		float m_Zoom = 1.0;
		OrthographicCamera m_Cam;

		glm::vec3 m_Pos = { 0.0f,0.0f,0.0f };
		float m_Rotation = 0;
		float m_AspectRatio;
		float m_CamMoveSpeed = 1;
		float m_CamRotSpeed = 1;
	};

	
}