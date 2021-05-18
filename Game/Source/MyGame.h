#pragma once
#include <Pine.h>
#include <iostream>
using namespace Pine;
//#undef main
class myGame : public Pine::Game
{
public:
    myGame();
    ~myGame();

    Pine::Core *app;
    virtual void Start();
virtual void Initialize();
virtual void Update();
virtual void Terminate();
virtual void OnMouseClick();

};

Pine::Game* Pine::CreateGame()
{
    std::cout << "Game Created" << std::endl;
    Game* game = new myGame();
    game->SetWindowParameters(600, 600, "Brood Test Window");
    return game;
    
}
