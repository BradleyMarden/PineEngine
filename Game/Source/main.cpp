#include <iostream>
#include <Pine.h>

#include "MyGame.h"

#define _DEBUG
using namespace Pine;
int main()
{
    std::cout<< "Hello" << std::endl;

   Core* App = new Core();
    myGame* game = new myGame();

    game->app = App;
    App->Pine::Core::PineOpenWindow("Game", 600,600);
    if(!App->Pine::Core::PineInit(game, NULL))
    {
        App->Pine::Core::PineCloseWindow();

    }
    App->Pine::Core::PineStart();
    App->Pine::Core::PineCloseWindow();

    return 0;
}
