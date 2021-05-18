#pragma once
#include <iostream>
#include <Pine.h>
//#ifdef PINE_PLATFORM_WINDOWS

extern Pine::Game* Pine::CreateGame();


int main(int argc, const char* argv[])
{
    Pine::Core* App = new Pine::Core();
	auto game = Pine::CreateGame();

    // Pine::Core::PineOpenWindow("Game", 600, 600);
     Pine::Core::PineOpenWindow();
    
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