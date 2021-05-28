#include "MyGame.h"

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{
   // std::cout << "Started" << std::endl;
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