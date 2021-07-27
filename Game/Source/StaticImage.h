#pragma once
#include "Pine.h"
#include "Log.h"
#include "window.h"

class StaticImage : public Pine::PineObject
{


public:

	StaticImage(std::string p_Name) : PineObject(p_Name) {}

	void Start()	override;

	void Update(float p_StepTime)	override;

	void Render()	override;

	void UIRender()	override;

	void OnTerminate()	override;

	void Trigger(Pine::PEvent& e);

	//void SetObstacleName(std::string p_Name) { m_ObstacleName = p_Name; }

	//std::string GetObstacleName() { return m_ObstacleName; }

private:

	std::weak_ptr<Pine::RendererComponent> m_RendComp;

	//std::string m_ObstacleName;

};