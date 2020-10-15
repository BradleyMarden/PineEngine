#pragma once
#include <Pine.h>

#include "Pine.h"

class PMyGame : public Pine::Application
{

public:
	PMyGame()
	{

	}

	~PMyGame()
	{


	}
	Application* MyGame = this;  //Pine::Application::GetPGame();

	virtual void Update();
	virtual void Start();
	virtual void Initialize();
	virtual void Terminate();
	

};