#pragma once
#include "OrthographicCamera.h"
namespace Pine
{
	OrthographicCamera::OrthographicCamera(float p_Left, float p_Right, float p_Bottom, float p_Top) : m_ProjectionMat(glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f)),m_ViewMat(1.0f)
	{
		m_ViewProjectionMat = m_ProjectionMat * m_ViewMat;
	
	}
	void OrthographicCamera::UpdateViewMatrix() 
	{
		glm::mat4 l_Trans = glm::translate(glm::mat4(1.0f), m_Pos) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMat = glm::inverse(l_Trans);
		m_ViewProjectionMat = m_ProjectionMat * m_ViewMat;
	
	}

	void OrthographicCamera::SetProjection(float p_Left, float p_Right, float p_Bottom, float p_Top)
	{
		m_ProjectionMat = glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f);//converts screen space to values between -1:1
		m_ViewProjectionMat = m_ProjectionMat * m_ViewMat;
	
	}
}	//glm::mat4 projection = glm::ortho(0.0f, Window::GetMainWindow()->s_WindowSize.x, 0.0f, Window::GetMainWindow()->s_WindowSize.y, -1.0f, 1.0f);//converts screen space to values between -1:1
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//can be used to imitate move camera(works by shifting all onjects in scene)
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//controls positon of object on screen
	//glm::mat4 mvp = projection * view * model;