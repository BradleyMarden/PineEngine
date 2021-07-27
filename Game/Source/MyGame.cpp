#include "MyGame.h"
//enables console logging
#define DEBUG

myGame::myGame(){}
myGame::~myGame(){}

#define SERVER true

#define CLIENT false



void myGame::Initialize()
{

    Pine::Window::CreateNewWindow("Main", 960, 540);

    Renderer::SetCamera(&m_Cam);

    if (SERVER)
    {
        Pine::Networking::PineNetworkingInit();
        Pine::Networking::PineServerCreate(2302, 4);
    }

    if (CLIENT)
        Pine::Networking::PineNetworkingInit();

}
void myGame::Start()
{
    
    
    Pine::EventSystem::RegisterEventCallback(BIND_EVENT(myGame::eventTrigger));

    //create and add scene
    std::shared_ptr<Scene> _Scene = std::make_shared<Scene>("Menu");
    AddScene<Scene>(_Scene);

    //create player
    std::shared_ptr<Player> _Player1 = std::make_shared<Player>("Player1");
    _Player1->SetPlayerName("Brad");

    //create other
    std::shared_ptr<Obstacles> _Obstacles = std::make_shared<Obstacles>("Obstacles");
   // _Obstacles->SetObstacleName("Obs");


    std::shared_ptr<StaticImage> _Vinette = std::make_shared<StaticImage>("Vinette");

    std::shared_ptr<StaticImage> _Background = std::make_shared<StaticImage>("Background");

    //add player to scene



    _Scene->AddPineObject<Obstacles>(_Obstacles);
    _Scene->AddPineObject<Player>(_Player1);
    _Scene->AddPineObject<StaticImage>(_Vinette);
    _Scene->AddPineObject<StaticImage>(_Background);

   // _Scene->AddPineObject<PineObject>(_Vinette);

    //add component to player and Obstacles
    std::shared_ptr<RendererComponent> _PlayerRendererComponent = std::make_shared<RendererComponent>("RendererComponent");
    std::shared_ptr<RendererComponent> _ObstaclesRendererComponent = std::make_shared<RendererComponent>("RendererComponent");
    std::shared_ptr<RendererComponent> _VinetteRendererComponent = std::make_shared<RendererComponent>("RendererComponent");
    std::shared_ptr<RendererComponent> _BackgroundRendererComponent = std::make_shared<RendererComponent>("RendererComponent");
   // std::shared_ptr<RendererComponent> _VinetteRendererComponent = std::make_shared<RendererComponent>("RendererComponent");

    _Player1->AddComponentToPineObject<RendererComponent>(_PlayerRendererComponent);
    _Obstacles->AddComponentToPineObject<RendererComponent>(_ObstaclesRendererComponent);
    _Vinette->AddComponentToPineObject<RendererComponent>(_VinetteRendererComponent);
    _Background->AddComponentToPineObject<RendererComponent>(_BackgroundRendererComponent);

 
    _Vinette->GetComponent<RendererComponent>("RendererComponent").lock()->LoadTexture("VinetteImage", "Assets/Vinette.png");
    _Background->GetComponent<RendererComponent>("RendererComponent").lock()->LoadTexture("BackgroundImage", "Assets/Background.png");

    _Vinette->GetComponent<RendererComponent>("RendererComponent").lock()->DrawQuad({ 0,0 }, { Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName),Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) }, "VinetteImage", { 1.0,1.0,1.0,1.0 }, "Vinette", Pine::RendererComponent::TOP);
    _Background->GetComponent<RendererComponent>("RendererComponent").lock()->DrawQuad({ 0,0 }, { Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName),Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) }, "BackgroundImage", { 1.0,1.0,1.0,1.0 }, "Background", Pine::RendererComponent::BOTTOM);

    //load scene
    LoadScene<Scene>("Menu");

    if (CLIENT)
    {
        //SERVER CONNNECTION
        while (Pine::Networking::PineServerConnect("80.3.158.122", 2302) == EXIT_FAILURE)
        {
            PINE_ENGINE_WARN("Retrying Connection...");
        }
    }
}

void myGame::Restart() 
{
    std::shared_ptr<Pine::RendererComponent::Quad>  _PlayerQuad = GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->GetComponent<RendererComponent>("RendererComponent").lock()->GetQuad("Player");
    _PlayerQuad->s_Pos = GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->GetPlayerStartPos();
    GetScene<Scene>("Menu").lock()->GetPineObject<Obstacles>("Obstacles").lock()->Reset();

}

int x, y = 0;
void myGame::Update(int m_StepTime)
{
    if (SERVER)
        Pine::Networking::PineServerNetworkLoop(0);

    if (CLIENT)
    {
        if (Pine::Networking::PineClientNetworkLoop(0) == EXIT_FAILURE)
        {
            while (Pine::Networking::PineServerConnect("80.3.158.122", 2302) == EXIT_FAILURE)
                PINE_WARN("Retrying Connection...");
        }
    }
    //PINE_ENGINE_WARN("ITS OUT");

    std::vector<std::shared_ptr<Pine::RendererComponent::Quad>> _Quads = GetScene<Scene>("Menu").lock()->GetPineObject<Obstacles>("Obstacles").lock()->GetComponent<RendererComponent>("RendererComponent").lock()->GetAllQuads();
   std::shared_ptr<Pine::RendererComponent::Quad>  _PlayerQuad = GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->GetComponent<RendererComponent>("RendererComponent").lock()->GetQuad("Player");
   std::weak_ptr<Pine::RendererComponent> _PlayerRenderComp = GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->GetComponent<RendererComponent>("RendererComponent");
    for (size_t i = 0; i < _Quads.size(); i++)
    {
        if (_Quads[i]->s_Name == "ObstacleB")
        {


            if (_PlayerRenderComp.lock()->CheckWithTriangleCollision(_PlayerQuad->s_Pos, _Quads[i]->s_Pos, _PlayerQuad->s_Size, _Quads[i]->s_Size, true))
            {
                PINE_ENGINE_WARN("ITS IN");
                m_HitCount++;
                Restart();
            }
        }
        if (_Quads[i]->s_Name == "ObstacleT")
        {
            if (_PlayerRenderComp.lock()->CheckWithTriangleCollision(_PlayerQuad->s_Pos, _Quads[i]->s_Pos, _PlayerQuad->s_Size, _Quads[i]->s_Size, false))
            {
                PINE_ENGINE_WARN("ITS IN");
                m_HitCount++;
                Restart();
            }
        }
    }


}

void myGame::Draw() 
{


    m_Cam.SetPosition({ 10,p.y, 0 });

}

void myGame::RenderUI()
{
    /*// Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(Pine::Window::GetWindowGLData(Pine::Window::GetMainWindow()->s_WindowName)->s_Window);
    //IMGUI CREATE FRAME
    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(0, Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) / 2), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_Always);

    static float f = 0.0f;
    //IMGUI START
    ImGui::Begin("PLAYER");
    ImGui::Text("Hit Ctunt: %i",m_HitCount );
    ImGui::End();
    //IMGUI END

    //IMGUI RENDER
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    */
}
void myGame::OnMouseClick()
{

}
void myGame::Terminate()
{
    if (SERVER)
        Pine::Networking::PineServerClose();

    if (CLIENT)
        Pine::Networking::PineServerDisconnect();
}

void myGame::eventTrigger(Pine::PEvent& e) 
{
    /*
        this fucntion needs to bind events to a function, that way we give the developer more
        controll over where the event gets finally handeld.

    */

    if (&e == nullptr) 
        return; 

    if (e.GetEventType() == Pine::EventType::WindowResize)
        e.is_Handled = true;

     if (e.GetEventType() == Pine::EventType::MouseButtonDown) 
    {
       //e.is_Handled = true;

        if (dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
            PINE_INFO("Left Down");
    }
     if (e.GetEventType() == Pine::EventType::MouseButtonUp)
    {
        e.is_Handled = true;

        if (dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
            PINE_INFO("Left Up");

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
             y--;

         if (dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() == 4)//a
             x--;

         if (dynamic_cast<Pine::KeyDownEvent&>(e).GetKey() == 7)//d
             x++;
     }
     if (e.GetEventType() == Pine::EventType::MiddleMouseScroll)
     {
         float offset = dynamic_cast<Pine::MouseScrollEvent&>(e).GetOffset();

         //e.is_Handled = true;
     }
     if (e.GetEventType() == Pine::EventType::KeyUp)
     {
         e.is_Handled = true;

         std::cout << dynamic_cast<Pine::KeyUpEvent&>(e).GetKey() << std::endl;
     }

    
}

