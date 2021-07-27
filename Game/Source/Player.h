#pragma once
#include "Pine.h"
#include "Log.h"
#include "window.h"

class Player : public Pine::PineObject
{
	

public:

	Player(std::string p_Name) : PineObject(p_Name) {}

	void Start()	override;

	void Update(float p_StepTime)	override;

	void Render()	override;

	void UIRender()	override;

	void OnTerminate()	override;

	void SetPlayerName(std::string p_Name) { m_PlayerName = p_Name; }

	void Trigger(Pine::PEvent& e);

	//void SetPosition(glm::vec3 p_Pos) { m_PlayerPos = p_Pos; }
	glm::vec3 GetPlayerStartPos() const { return m_PlayerStartPos; }
	std::string GetPlayerName() { return m_PlayerName; }
private:

	void MoveUp(float p_StepTime);
	std::weak_ptr<Pine::RendererComponent> m_RendComp;
	glm::vec3 m_PlayerStartPos = { Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName) / 2 - 150,20,0};
	glm::vec3 m_PlayerPos = { 0.0f,0.0f ,0.0f };
	glm::vec2 pos;
	std::string m_PlayerName;
	bool shoot = false;
};