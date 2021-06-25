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

    /*if(Input::GetKeyDown(SDLK_w))
    {

      shaders =  Pine::Shader::LoadShader("Assets/Shaders/default.PineShader");
      //I dont like currently how the event id created. Its hard to know who has controll of the memory. in future need to abstract this into a macro or static func.
     Pine::WindowResizeEvent*  e = new Pine::WindowResizeEvent(100,100);

    }*/
    if (Input::GetKeyDown(SDLK_a))
    {

    }
    if (Input::GetKeyDown(SDLK_d) && Input::GetKeyDown(SDLK_w))
    {
        Pine::MouseButtonDownEvent* e = new Pine::MouseButtonDownEvent(100,100,Pine::Input::LEFTDOWN, false);
        
    }
}
void myGame::OnMouseClick(){}
void myGame::Terminate(){}

void myGame::eventTrigger(Pine::PEvent& e) 
{
    /*
        this fucntion needs to bind events to a function, that way we give the developer more
        controll over where the event gets finally handeld.

    */
    

    std::cout << "triggered" << std::endl;

    if (&e == nullptr) { return; }
    if (e.GetEventType() == Pine::EventType::WindowResize)
    {
        std::cout << "Winodw Resize" << std::endl;
        e.is_Handled = true;

    }
     if (e.GetEventType() == Pine::EventType::MouseButtonDown) 
    {
        std::cout << "In Game" << std::endl;
        e.is_Handled = true;

            std::cout << dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetX() << std::endl;
            std::cout << dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() << std::endl;

    }
     if (e.GetEventType() == Pine::EventType::MouseButtonUp)
    {
        std::cout << "In Game" << std::endl;
        e.is_Handled = true;

        std::cout << dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetButtonDown() << std::endl;
        if (dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
        {
            std::cout << "EYYYYYYY" << std::endl;

        }

    }

     if (e.GetEventType() == Pine::EventType::KeyDown)
     {
         std::cout << "In Game" << std::endl;
         e.is_Handled = true;

         std::cout << dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() << std::endl;

     }
     if (e.GetEventType() == Pine::EventType::KeyUp)
     {
         std::cout << "In Game" << std::endl;
         e.is_Handled = true;

         std::cout << dynamic_cast<Pine::KeyUpEvent&>(e).GetKey() << std::endl;

     }
}

