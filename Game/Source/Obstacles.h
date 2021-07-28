#pragma once
#include "Pine.h"
#include "Log.h"
#include "window.h"

class Obstacles : public Pine::PineObject
{


public:

	Obstacles(std::string p_Name) : PineObject(p_Name) {}

	void Start()	override;

	void Update(float p_StepTime)	override;

	void Render()	override;

	void UIRender()	override;

	void OnTerminate()	override;

	void Trigger(Pine::PEvent& e);

	void Reset();

	//void SetObstacleName(std::string p_Name) { m_ObstacleName = p_Name; }

	//std::string GetObstacleName() { return m_ObstacleName; }

private:

	std::weak_ptr<Pine::RendererComponent> m_RendComp;
	float m_LastPos;
	int m_PassedScreenCounter = 0;
	int m_ScrollSpeed = 1;
	glm::vec4 m_TopTriColor = { 1.0 ,1.0 ,1.0 ,1.0 };
	glm::vec4 m_BottomTriColor = { 1.0 ,1.0 ,1.0 ,1.0 };
	int m_SpeedIncreaseRequirement = 10;
	//std::string m_ObstacleName;
	Mix_Chunk* m_Crash = nullptr;

};