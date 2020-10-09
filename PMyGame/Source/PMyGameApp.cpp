#include "PMyGameApp.h"

Pine::Application* Pine::CreateApplication()
{
	PINE_INFO("Game Application Loaded");
	return new PMyGame();
}

void PMyGame::Update()
{
	PINE_INFO("Updating");

}


