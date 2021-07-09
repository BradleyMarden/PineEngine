#include "MyGame.h"

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{
    Pine::EventSystem::RegisterEventCallback(BIND_EVENT(myGame::eventTrigger));

 
}

void myGame::Initialize()
{

   // Pine::Window::CreateNewWindow("Main");
    //SecondWindow = Pine::Window::CreateNewWindow("Second");

    std::cout << "Num of Windows" << Pine::Window::GetOpenWindowCount() << std::endl;
    std::cout << "Main Window Size" << Pine::Window::GetWindowWidth("Main") << std::endl;
    //std::cout << "Second Window Size" << SecondWindow->GetWidth() << std::endl;
//    std::cout << SDL_GetWindowTitle(Pine::Window::GetWindowGLData("Second")->s_Window) << std::endl;
}
void myGame::Update()
{
    if (!Window::CheckWindowAlive("Second"))
    {
        static bool runOnce = false;
        if (!runOnce)
        {
            std::cout << "DEAD" << std::endl;
            runOnce = !runOnce;
        }
    }
  
}
void myGame::OnMouseClick()
{

}
void myGame::Terminate()
{

}

void myGame::eventTrigger(Pine::PEvent& e) 
{
    /*
        this fucntion needs to bind events to a function, that way we give the developer more
        controll over where the event gets finally handeld.

    */

    if (&e == nullptr) { return; }
    if (e.GetEventType() == Pine::EventType::WindowResize)
    {
        e.is_Handled = true;

    }
     if (e.GetEventType() == Pine::EventType::MouseButtonDown) 
    {
        e.is_Handled = true;

            std::cout << "Mouse X pos: "<< dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetX() << std::endl;
            std::cout << "Mouse y pos: "<< dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetY() << std::endl;
            std::cout << "Key Code: " << dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() << std::endl;
            if (dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
            {
                std::cout << "Left Down" << std::endl;
            }
    }
     if (e.GetEventType() == Pine::EventType::MouseButtonUp)
    {
        e.is_Handled = true;
        std::cout << "Mouse X pos: " << dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetX() << std::endl;
        std::cout << "Mouse Y pos: " << dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetY() << std::endl;
        std::cout << "Key Code: " << dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetButtonDown() << std::endl;
        if (dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
        {
            std::cout << "Left Up" << std::endl;
        }
    }
     if (e.GetEventType() == Pine::EventType::KeyDown)
     {
         e.is_Handled = true;
         std::cout << dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() << std::endl;
     }
     if (e.GetEventType() == Pine::EventType::KeyUp)
     {
         e.is_Handled = true;
         std::cout << dynamic_cast<Pine::KeyUpEvent&>(e).GetKey() << std::endl;
     }
}

