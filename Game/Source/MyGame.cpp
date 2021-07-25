#include "MyGame.h"
//enables console logging
#define DEBUG

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{

  
    Pine::EventSystem::RegisterEventCallback(BIND_EVENT(myGame::eventTrigger));

    //create and add scene
    std::shared_ptr<Scene> _Scene = std::make_shared<Scene>("Menu");
    AddScene<Scene>(_Scene);

    std::shared_ptr<Player> _Player1 = std::make_shared<Player>("Player1");
    _Player1->SetPlayerName("Brad");
    _Scene->AddPineObject<Player>(_Player1);
    std::shared_ptr<RendererComponent> _RendererComponent = std::make_shared<RendererComponent>("RendererComponent");
    //_RendererComponent->DrawQuad({ 400,400 }, { 30.0f,30.0f }, 2);
    _Player1->AddComponentToPineObject<RendererComponent>(_RendererComponent);

    LoadScene<Scene>("Menu");

  //  GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->Start();

}

void myGame::Initialize()
{

    Pine::Window::CreateNewWindow("Main", 960,540);
    Renderer::SetCamera(&m_Cam);

   
}
int x, y = 0;
void myGame::Update(int m_StepTime)
{
   // GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->Update(m_StepTime);

    if (Renderer::HasInit() ==true)
    {
        

    }
}

void myGame::Draw() 
{
    //GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->Render();


    glm::vec4 col = { 0.0f ,1.0f, 1.0f ,1.0f };
    PVector2f mousePos = Input::GetMousePosition();

    Pine::Renderer::DrawQuad({ 0,0 }, { Window::GetMainWindow()->s_WindowSize.x,Window::GetMainWindow()->s_WindowSize.y }, 3);

    for (float y = 0; y < Window::GetMainWindow()->s_WindowSize.y / 4; y += 30.0f)
    {
        for (float x = 0; x < Window::GetMainWindow()->s_WindowSize.x; x += 30.0f)
        {
            glm::vec4 col = { (x + 0.25) / 20.0f, 0.2f, (y + 1) / 20.0f, 1.0f };
            Pine::Renderer::DrawQuad({ x,y }, { 30.0f,30.0f }, 2);
        }
    }
    Pine::Renderer::DrawQuad({ p.x,p.y }, { 30.0f,30.0f }, 1);

    //cam.OnUpdate(m_StepTime);
    if (Input::GetKeyDown(SDL_SCANCODE_W))
    {
        // std::cout << "PRESSED" << std::endl;
        p.y++;
    }
    if (Input::GetKeyDown(SDL_SCANCODE_S))
    {
        // std::cout << "PRESSED" << std::endl;
        p.y--;

    }

    if (Input::GetKeyDown(SDL_SCANCODE_A))
    {
        // std::cout << "PRESSED" << std::endl;
        p.x--;
    }
    if (Input::GetKeyDown(SDL_SCANCODE_D))
    {
        // std::cout << "PRESSED" << std::endl;
        p.x++;

    }
    m_Cam.SetPosition({ 10,p.y, 0 });

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
       // e.is_Handled = true;

            if (dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
            {
               
                PINE_INFO("Left Down");
            }
    }
     if (e.GetEventType() == Pine::EventType::MouseButtonUp)
    {
        e.is_Handled = true;
        if (dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
        {
            PINE_INFO("Left Up");

        }
    }
     if (e.GetEventType() == Pine::EventType::KeyDown)
     {
         e.is_Handled = true;
         std::cout << dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() << std::endl;

         PINE_INFO("Key Down: {0}", dynamic_cast<Pine::KeyDownEvent&>(e).GetKey());

         if (dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() == 26)//w
         {
             y++;
         }
         if (dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() == 22)//s
         {
             y--;
         }

         if (dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() == 4)//a
         {
             x--;
         }
         if (dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() == 7)//d
         {
             x++;
         }
     }
     if (e.GetEventType() == Pine::EventType::MiddleMouseScroll)
     {
         //std::cout << "------------------------------------- " << std::endl;

         float offset = dynamic_cast<Pine::MouseScrollEvent&>(e).GetOffset();
         //e.is_Handled = true;

     }
     if (e.GetEventType() == Pine::EventType::KeyUp)
     {
         e.is_Handled = true;
         std::cout << dynamic_cast<Pine::KeyUpEvent&>(e).GetKey() << std::endl;
     }
}

