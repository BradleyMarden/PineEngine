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

	void SetPosition(glm::vec3 p_Pos) { m_PlayerPos = p_Pos; }

	std::string GetPlayerName() { return m_PlayerName; }
private:

	void MoveUp(float p_StepTime);
	std::weak_ptr<Pine::RendererComponent> m_RendComp;
	glm::vec3 m_PlayerPos = {0,0,0};
	std::string m_PlayerName;
	bool shoot = false;
};