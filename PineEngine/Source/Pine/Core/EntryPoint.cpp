#pragma once
#include <iostream>
#include <Pine.h>
//#ifdef PINE_PLATFORM_WINDOWS

extern Pine::Game* Pine::CreateGame();


int main(int argc, const char* argv[])
{

	auto game = Pine::CreateGame();
	Pine::Core* App = new Pine::Core();

    App->Pine::Core::PineOpenWindow("Game", 600, 600);
    if (!App->Pine::Core::PineInit(game, NULL))
    {
        App->Pine::Core::PineCloseWindow();

    }
    App->Pine::Core::PineStart();
    App->Pine::Core::PineCloseWindow();


	delete game;
    delete App;

}
//#endif