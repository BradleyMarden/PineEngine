#pragma once
#include <iostream>
#include <Pine.h>

//External function, which allows the main functions to get the developers game class. NOTE: this function MUST be implemented in a child of the Game class, see documentation.
extern Pine::Game* Pine::CreateGame();

//I have abstracted the main loop away from the developer as I want PineEngine to have controll of the flow of the application
int main(int argc, const char* argv[])
{

    //Create game, this is where all the logic for the game lives
    Pine::Game* game = Pine::CreateGame();

    //Create core, this is where the logic for the engine lives
    Pine::Core* App = new Pine::Core();

   // App->Pine::Core::PineCreateWindow(600, 600);

    //Initilialise application
    App->Pine::Core::PineInit(game, NULL);

    //Main game loop contained inside.
    App->Pine::Core::PineStart();

    //close game
    App->Pine::Core::PineCloseEngine();


	delete game;
    delete App;
    return 0;
}
