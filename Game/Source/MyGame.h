#pragma once


#include <iostream>
#include <Pine.h>
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
    void eventTrigger(Pine::PEvent& e);
    unsigned int shader;
    Pine::Window* MainWindow = nullptr;
    const Pine::Window* SecondWindow = nullptr;
    glm::mat4 vp;
};

Pine::Game* Pine::CreateGame()
{
    Game* game = new myGame();
    return game;
}
