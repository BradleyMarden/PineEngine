#include "MyGame.h"

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{
    std::cout << "Started" << std::endl;
}

void myGame::Initialize(){}
void myGame::Update(){


    if(Input::GetKeyDown(SDLK_w))
    {

    std::cout<< "Hello" << std::endl;

    }

}
void myGame::OnMouseClick(){}
void myGame::Terminate(){}