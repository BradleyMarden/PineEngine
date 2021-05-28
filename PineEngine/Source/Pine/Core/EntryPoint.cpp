#pragma once
#include <iostream>
#include <Pine.h>
//#ifdef PINE_PLATFORM_WINDOWS

extern Pine::Game* Pine::CreateGame();


int main(int argc, const char* argv[])
{
    Pine::Core* App = new Pine::Core();
	auto game = Pine::CreateGame();
    if (glewInit() != GLEW_OK)
    {
        std::cout << "OPENGL NOt" << std::endl;
    }
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