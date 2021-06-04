#include "MyGame.h"

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{
   // std::cout << "Started" << std::endl;

    es = new Pine::EventSystem();

    Pine::PineEvent* event = new Pine::PineEvent("Launch");

    int id = es->Register(event);
    //es->Subscribe(this, &Pine::Game::Start);
    es->Subscribe("Launch",&myGame::eventTrigger);
    es->Publish("Launch");
}

void myGame::Initialize(){}
void myGame::Update(){


    if(Input::GetKeyDown(SDLK_w))
    {

      shaders =  Pine::Shader::LoadShader("Assets/Shaders/default.PineShader");
  
    }
    if (Input::GetKeyDown(SDLK_a))
    {

        std::cout << shaders.VertexSource << std::endl;

    }
    if (Input::GetKeyDown(SDLK_d))
    {

        std::cout << shaders.FragmentSource << std::endl;
    }
}
void myGame::OnMouseClick(){}
void myGame::Terminate(){}

void myGame::eventTrigger() 
{
    std::cout << "triggered" << std::endl;
}