#pragma once
#include <Pine.h>
#include <iostream>
using namespace Pine;
class myGame : public Pine::Game
{
public:
    myGame();
    ~myGame();

    Pine::Core *app;
    virtual void Start()override;
virtual void Initialize() override;
virtual void Update() override;
virtual void Terminate() override;
virtual void OnMouseClick() override;
Pine::SourceShader shaders;
Pine::EventSystem* es;

void eventTrigger();

};

Pine::Game* Pine::CreateGame()
{
    Game* game = new myGame();
    game->SetWindowParameters(500, 500, "Brood Test Window");
    return game;
    
}
