#include "MyGame.h"

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{
    Pine::EventSystem::RegisterEventCallback(BIND_EVENT(myGame::eventTrigger));

 
}

void myGame::Initialize()
{

    Pine::Window::CreateNewWindow("Main");
    SecondWindow = Pine::Window::CreateNewWindow("Second");
    Pine::Window::CreateNewWindow("Third", 1920,1080);

    //Pine::Window::CreateNewWindow("Four");

    std::cout << "Num of Windows" << Pine::Window::GetOpenWindowCount() << std::endl;
    std::cout << "Main Window Size" << Pine::Window::GetWindowWidth("temp") << std::endl;
    std::cout << "Second Window Size" << SecondWindow->GetWidth() << std::endl;
   // SecondWindow->CloseWindow("Second");
    std::cout << SDL_GetWindowTitle(Pine::Window::GetWindowGLData("Second")->s_Window) << std::endl;
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
    
    std::cout << "triggered" << std::endl;

    if (&e == nullptr) { return; }
    if (e.GetEventType() == Pine::EventType::WindowResize)
    {
        std::cout << "Window Resize" << std::endl;
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

