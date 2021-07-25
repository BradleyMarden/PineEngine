#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Pine {

	class OrthographicCamera 
	{
	public:
		OrthographicCamera(float p_Left, float p_Right, float p_bottom, float p_Top);
		


		glm::vec3 GetPosition() const { return m_Pos; }
		void SetPosition(const glm::vec3& p_Pos) { m_Pos = p_Pos; UpdateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }

		void SetRotation(float p_Rot) { m_Rotation = p_Rot; UpdateViewMatrix(); }

		void SetProjection(float left, float right, float bottom, float top);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMat; }

		const glm::mat4& GetViewMatrix() const { return m_ViewMat; }

		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMat; }
	private:
		void UpdateViewMatrix();

		glm::mat4 m_ProjectionMat;
		glm::mat4 m_ViewMat;
		glm::mat4 m_ViewProjectionMat;

		glm::vec3 m_Pos;
		float m_Rotation = 0;
	
	};
	//glm::mat4 projection = glm::ortho(0.0f, Window::GetMainWindow()->s_WindowSize.x, 0.0f, Window::GetMainWindow()->s_WindowSize.y, -1.0f, 1.0f);//converts screen space to values between -1:1
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//can be used to imitate move camera(works by shifting all onjects in scene)
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//controls positon of object on screen
	//glm::mat4 mvp = projection * view * model;
	

	
}