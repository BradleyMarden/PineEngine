#include "MyGame.h"
//enables console logging
#define DEBUG

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{
    Pine::EventSystem::RegisterEventCallback(BIND_EVENT(myGame::eventTrigger));

    Pine::MaterialComponent comp();

    Pine::NetworkComponent net();

    //create and add scene
    std::shared_ptr<Scene> _Scene = std::make_shared<Scene>("Menu");
    AddScene<Scene>(_Scene);

    std::shared_ptr<Player> _Player1 = std::make_shared<Player>("Player1");
    _Player1->SetPlayerName("Brad");
    _Scene->AddPineObject<Player>(_Player1);

    std::weak_ptr<Player> _Player2 = _Scene->AddPineObject<Player>("Player2");
    _Player2.lock()->SetPlayerName("Tayla");

    std::weak_ptr<Scene> _WeakScene = GetScene<Scene>("Menu");
    PINE_ENGINE_WARN(_WeakScene.lock()->GetName());


    PINE_ENGINE_WARN(_Scene->GetPineObject<Player>("Player1").lock()->GetName());

    _Scene->AddPineObject<Player>("Player3");
    _Scene->GetPineObject<Player>("Player3").lock()->SetPlayerName("Nathan");
    _Player1->AddComponentToPineObject<MaterialComponent>("TestComponent");
    _Player1->GetComponent<MaterialComponent>("TestComponent").lock()->SetMatName("Material");
    PINE_ENGINE_WARN(_Player1->GetComponent<MaterialComponent>("TestComponent").lock()->GetMatName());


    PINE_ENGINE_WARN(_Scene->GetPineObject<Player>("Player1").lock()->GetPlayerName());
    PINE_ENGINE_WARN(_Scene->GetPineObject<Player>("Player2").lock()->GetPlayerName());
    PINE_ENGINE_WARN(_Scene->GetPineObject<Player>("Player3").lock()->GetPlayerName());

    


    PINE_ENGINE_WARN(GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->GetPlayerName());
    PINE_ENGINE_WARN(GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player2").lock()->GetPlayerName());
    PINE_ENGINE_WARN(GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player3").lock()->GetPlayerName());
                                                                                            
    PINE_ENGINE_WARN(GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player1").lock()->GetPlayerName());
    PINE_ENGINE_WARN(GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player2").lock()->GetPlayerName());
    PINE_ENGINE_WARN(GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Player3").lock()->GetPlayerName());


    LoadScene<Scene>("Menu");

    
   /* std::shared_ptr<Scene> sc =  std::make_shared<Scene>("Menu");
    AddScene(sc);
    std::weak_ptr<Scene> sc2 = GetScene<Scene>("Menu").lock();
    std::weak_ptr<Player> p1 = GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Bradley");

    std::shared_ptr<Player> player = std::make_shared<Player>("Brood");
    GetScene<Scene>("Menu").lock()->AddPineObject<Player>(player);

    GetScene<Scene>("Menu").lock()->AddPineObject<Player>("Bradley");

    GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Bradley").lock()->SetName("Bradley Marden");
    GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Brood").lock()->SetName("Bradley James Charles Hanson-Marden");

    PINE_ENGINE_WARN("Name in scene: {0}", GetScene<Scene>("Menu").lock()->GetPineObject<Player>("Bradley").lock()->GetName());
    std::string n = LoadScene<Scene>("Menu").lock()->GetSceneName();
    PINE_ERROR("Scene Name: {0}", n);
   // Pine::ComponentSystem::AddComponent<NetworkComponent>(1);
    //Pine::ComponentSystem::AddComponent<NetworkComponent>(1);

    m_Scene = new Scene("Menu");
    m_Scene->AddPineObject<PineObject>("Test");
    m_Scene->AddPineObject<Player>("Player");
    m_Scene->AddPineObject<Player>("Player2");
    m_Scene->AddPineObject<PineObject>("Test");

    //PineObject* _PO = m_Scene->GetPineObject<PineObject>("Test");
    m_Scene->GetPineObject<Player>("Player").lock()->SetName("Broodley");
    m_Scene->GetPineObject<Player>("Player2").lock()->SetName("Tayla");

    std::weak_ptr<Player> _PO1 = m_Scene->GetPineObject<Player>("Player");
    PINE_ERROR(_PO1.lock()->GetName());
    PINE_ERROR(m_Scene->GetPineObject<Player>("Player2").lock()->GetName());
    PINE_ERROR(m_Scene->GetPineObject<Player>("Player").lock()->GetInstanceID());
    PINE_ERROR(m_Scene->GetPineObject<Player>("Player2").lock()->GetInstanceID());
    PINE_ERROR(m_Scene->GetPineObject<Player>("Test").lock()->GetInstanceID());

    //returns all PineObjects of type
    std::unordered_map <std::string, std::weak_ptr<Player>>& map = m_Scene->GetAllPineObjectsOfType<Player>();
    PINE_ERROR("Size: {0}", map.size());


    for (auto x : map)
    {
        //x.second->SetName("Nath");
    }

    PINE_ERROR(_PO1.lock()->GetName());
    PINE_ERROR(m_Scene->GetPineObject<Player>("Player2").lock()->GetName());
    m_Scene->GetPineObject<Player>("Player2").lock()->AddComponentToPineObject<MaterialComponent>("Render");
    m_Scene->GetPineObject<Player>("Player2").lock()->AddComponentToPineObject<MaterialComponent>("Render");*/
   // m_Scene->AddPineObject<Player>("Player");

    //m_Scene->GetPineObject<Player>("Player")->GetName();

    

   /* //load shader
    SourceShader localShaders = Pine::Shader::LoadShader("Assets/Shaders/default.PineShader");
     shader = Shader::CreateShader(localShaders.VertexSource, localShaders.FragmentSource);
    glUseProgram(shader);

    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(PINE_MAIN_WINDOW_SIZE), 0.0f, static_cast<float>(PINE_MAIN_WINDOW_SIZE), -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;
    vp = proj * view;
    Shader::SetUniformMat4f("u_MVP", mvp);

    int location = glGetUniformLocation(shader, "u_MVP");

    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);



    auto loc = glGetUniformLocation(shader, "u_Textures");
    int samplers[32];
    for (int i = 0; i < 32; i++)
    {
        samplers[i] = i;

    }

    glUniform1iv(loc, 32, samplers);
    glClearColor(0.2f, 0.2f, 0.1f, 1.0f);*/
 
}

void myGame::Initialize()
{

    Pine::Window::CreateNewWindow("Main", 960,540);
   // Pine::Renderer::SetWindowIcon("Assets/PineEngineText.png");
    //Pine::Window::CreateNewWindow("Second");
    Renderer::SetCamera(&cam);
    //std::cout << "Num of Windows" << Pine::Window::GetOpenWindowCount() << std::endl;
    //std::cout << "Main Window Size" << Pine::Window::GetWindowWidth("Main") << std::endl;
    //std::cout << "Second Window Size" << SecondWindow->GetWidth() << std::endl;
//    std::cout << SDL_GetWindowTitle(Pine::Window::GetWindowGLData("Second")->s_Window) << std::endl;

   
}
int x, y = 0;
void myGame::Update(int m_StepTime)
{

    if (Input::GetKeyDown(SDL_SCANCODE_P))
    {
       // std::cout << "PRESSED" << std::endl;
    }
    if (!Window::CheckWindowAlive("Second"))
    {
        static bool runOnce = false;
        if (!runOnce)
        {
           // std::cout << "DEAD" << std::endl;
            runOnce = !runOnce;
        }
    }
    if (Renderer::HasInit() ==true)
    {
        glm::vec4 col = { 0.0f ,1.0f, 1.0f ,1.0f };

        PVector2f mousePos = Input::GetMousePosition();
        Renderer::ResetStats();
        Renderer::BeginBatch();
        Pine::Renderer::DrawQuad({ 0,0 }, { Window::GetMainWindow()->s_WindowSize.x,Window::GetMainWindow()->s_WindowSize.y }, 3);

        for (float y = 0; y < Window::GetMainWindow()->s_WindowSize.y/4; y += 30.0f)
        {
            for (float x = 0; x < Window::GetMainWindow()->s_WindowSize.x; x += 30.0f)
            {
                glm::vec4 col = { (x + 0.25) / 20.0f, 0.2f, (y + 1) / 20.0f, 1.0f };
                Pine::Renderer::DrawQuad({ x,y }, { 30.0f,30.0f }, 2);
            }
        }
        
        Renderer::DrawQuad({ 400,400}, { 100.0f ,100.0f }, col);
        Renderer::EndBatch();
        Renderer::Flush();

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

           // std::cout << "Mouse X pos: "<< dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetX() << std::endl;
           // std::cout << "Mouse y pos: "<< dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetY() << std::endl;
           // std::cout << "Key Code: " << dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() << std::endl;
            if (dynamic_cast<Pine::MouseButtonDownEvent&>(e).GetButtonDown() == Input::LEFTSINGLECLICK)
            {
               
                PINE_INFO("Left Down");
            }
    }
     if (e.GetEventType() == Pine::EventType::MouseButtonUp)
    {
        e.is_Handled = true;
        //std::cout << "Mouse X pos: " << dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetX() << std::endl;
       // std::cout << "Mouse Y pos: " << dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetY() << std::endl;
       // std::cout << "Key Code: " << dynamic_cast<Pine::MouseButtonUpEvent&>(e).GetButtonDown() << std::endl;
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
         e.is_Handled = true;

     }
     if (e.GetEventType() == Pine::EventType::KeyUp)
     {
         e.is_Handled = true;
         std::cout << dynamic_cast<Pine::KeyUpEvent&>(e).GetKey() << std::endl;
     }
}

