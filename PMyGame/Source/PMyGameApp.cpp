#include "PMyGameApp.h"

Pine::Application* Pine::CreateApplication()
{
	PINE_INFO("Game Application Loaded");
	return new PMyGame();
}
void PMyGame::Initialize()
{

	PINE_INFO("INIT GAME");

	if (!MyGame->CreateNetwork())
	{
		auto a = EXIT_FAILURE;
		PINE_INFO("Failed to INIT Net: {0}", a);//provides exit failure error
		
	}
	else
	{
		PINE_INFO("INIT NET");
	}



}
void PMyGame::Update()
{
	for (size_t i = 0; i < 500; i++)
	{

		PINE_INFO("Updating");
	}

}


void PMyGame::Start()
{
	//MyGame->SetGameClose();

}



void PMyGame::Terminate()
{
	PINE_ERROR("TERMING");

}