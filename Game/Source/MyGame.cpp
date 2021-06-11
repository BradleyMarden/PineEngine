#include "MyGame.h"

myGame::myGame(){}
myGame::~myGame(){}


void myGame::Start()
{
   // std::cout << "Started" << std::endl;
    Pine::EventSystem::RegisterEventCallback(BIND_EVENT(myGame::eventTrigger));

   // es = new Pine::EventSystem();

   // Pine::PineEvent* event = new Pine::PineEvent("Launch");

   // int id = es->Register(event);
    //es->Subscribe(this, &Pine::Game::Start);
    //es->Subscribe("Launch",&myGame::eventTrigger);
    //es->Publish("Launch");
}

void myGame::Initialize(){}
void myGame::Update(){


    if(Input::GetKeyDown(SDLK_w))
    {

      shaders =  Pine::Shader::LoadShader("Assets/Shaders/default.PineShader");
      //I dont like currently how the event id created. Its hard to know who has controll of the memory. in future need to abstract this into a macro or static func.
     Pine::WindowResizeEvent*  e = new Pine::WindowResizeEvent(100,100);

    }
    if (Input::GetKeyDown(SDLK_a))
    {

    }
    if (Input::GetKeyDown(SDLK_d))
    {



    }
}
void myGame::OnMouseClick(){}
void myGame::Terminate(){}

void myGame::eventTrigger(Pine::PEvent& e) 
{
    /*
        this fucntion needs to bind events to a function, that way we give the developer more
        controll over where the event gets finally handeld.

        EventSystem::BindTypeToFucntion(TYPE, FUNC);
    */
    

    std::cout << "triggered" << std::endl;

    if (&e == nullptr) { return; }
    if (e.GetEventType() == Pine::EventType::WindowResize)
    {
        std::cout << "Winodw Resize" << std::endl;
        e.is_Handled = true;

    }
    else if (e.GetEventType() == Pine::EventType::MouseButtonDown) 
    {
        //cannot get event specific data as any child object of event will not be passed down., need to link each type to a function
        e.is_Handled = true;
        std::cout << dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetX() << std::endl;


    }
}

