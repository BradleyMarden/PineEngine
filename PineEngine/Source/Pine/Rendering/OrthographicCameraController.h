#pragma once
#include "Log.h"
#include "EventSystem.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Input.h"
#include "Core.h"
#include "OrthographicCamera.h"

namespace Pine {

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