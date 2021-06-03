#pragma once
#include <iostream>
#include <Pine.h>
//#ifdef PINE_PLATFORM_WINDOWS

//UNDEFINE FOR RELSEASE
#define DEBUG

//External function, which allows the main functions to get the developers game class. NOTE: this function MUST be implemented in a child of the Game class, see documentation.
extern Pine::Game* Pine::CreateGame();

//I have abstracted the main loop away from the developer as I want PineEngine to have controll of the flow of the application
int main(int argc, const char* argv[])
{
    //Create game, this is where all the logic for the game lives
    Pine::Game* game = Pine::CreateGame();
    if (!game->g_ParametersSet)
        game->SetWindowParameters(600, 600, "Pine Engine Application");
    //Create core, this is where the logic for the engine lives
    Pine::Core* App = new Pine::Core();

    //Open the window, currently can only be used to open one window. TBA: open multiple windows
    Pine::Core::PineOpenWindow();
    
    //Initilialise application
    PINE_ASSERT("PineEngine could not be initialised. Please check that you are passing a Pine::Game child object", App->Pine::Core::PineInit(game, NULL));

    //Main game loop contained inside.
    App->Pine::Core::PineStart();
    App->Pine::Core::PineCloseWindow();


	delete game;
    delete App;

}
//#endif