#pragma once


#include <iostream>
#include <Pine.h>
#include "Player.h"
#include "Obstacles.h"
#include "StaticImage.h"
#include "Log.h"
using namespace Pine;
class myGame : public Pine::Game
{
public:
    myGame();
    ~myGame();

    Pine::Core *app;
    virtual void Start()override;
    virtual void Initialize() override;
    virtual void Update(int p_StepTime) override;
    virtual void Terminate() override;
    virtual void Draw() override;
    virtual void RenderUI() override;
    virtual void OnMouseClick() override;
    Pine::SourceShader shaders;
    Pine::EventSystem* es;
    void eventTrigger(Pine::PEvent& e);
    unsigned int shader;
    Pine::Window* MainWindow = nullptr;
    const Pine::Window* SecondWindow = nullptr;
    glm::mat4 vp;
    OrthographicCamera m_Cam = { 0, 960, 0, 540};

    glm::vec2 p = { 0.0f,0.0f };
    glm::vec2 m_Pos;
    int m_HitCount = 0;
    bool wait = true;

    void Restart();
};

Pine::Game* Pine::CreateGame()
{
    Game* game = new myGame();
    return game;
}
