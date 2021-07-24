#pragma once
#include "Pine.h"
#include "Log.h"

class Player : public Pine::PineObject
{

public:

	Player(std::string p_Name) : PineObject(p_Name) {}

	void OnInit();

	void Start();

	void Update(float p_StepTime);

	void OnTerminate();

	void SetPlayerName(std::string p_Name) { m_PlayerName = p_Name; }

	std::string GetPlayerName() { return m_PlayerName; }
private:
	std::string m_PlayerName;
};