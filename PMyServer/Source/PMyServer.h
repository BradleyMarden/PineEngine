#pragma once
#include "PineServer.h"
class PMyServer : public Pine::Game
{
public: 
	 PMyServer();
	 ~PMyServer();

	virtual void Update();
	virtual void Start();
	virtual void Initialize();
	virtual void Terminate();

};

