#include "PMyGameApp.h"

Pine::Application* Pine::CreateApplication()
{
	PINE_INFO("Game Application Loaded");
	return new PMyGame();
}

void PMyGame::Update()
{
	for (size_t i = 0; i < 5000; i++)
	{
		PINE_INFO("Update");

	}


}
