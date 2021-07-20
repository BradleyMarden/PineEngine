#include "MyGame.h"

myGame::myGame(){}
myGame::~myGame(){}

void myGame::Start()
{
    Pine::EventSystem::RegisterEventCallback(BIND_EVENT(myGame::eventTrigger));

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

    Pine::Window::CreateNewWindow("Main");
   // Pine::Renderer::SetWindowIcon("Assets/PineEngineText.png");
    Pine::Window::CreateNewWindow("Second");

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
    if (Renderer::HasInit() ==true)
    {

        //glm::vec4 col = { 1.0f ,1.0f, 1.0f ,1.0f };

       // Pine::Renderer::ResetStats();
        //glUseProgram(shader);
        //glClear(GL_COLOR_BUFFER_BIT);
       // Pine::Renderer::BeginBatch();
/*
        for (float y = -10.f; y  < 10.0f; y+= 0.25f)
        {
            for (float x = -10.f; y < 10.0f; y += 0.25f)
            {
                glm::vec4 col = { (x + 10) / 20.0f, 0.2f, (y + 10) / 20.0f, 1.0f };
                Pine::Renderer::DrawQuad({ x,y }, { 0.25f,0.25f }, col);
            }
        }*/
        for (size_t i = 0; i < 200; i++)
        {
            //Pine::Renderer::DrawQuad({ 100.0f,100.0f }, { 0.25f,0.25f }, col);

        }

      //  Renderer::EndBatch();
        //int location = glGetUniformLocation(shader, "u_ViewProj");

        //glUniformMatrix4fv(location, 1, GL_FALSE, &vp[0][0]);

       // int location2 = glGetUniformLocation(shader, "u_ViewProj");
       // glm::mat4 p = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0));
       // glUniformMatrix4fv(location2, 1, GL_FALSE, &p[0][0]);
        //Renderer::Flush();

    }
    //for (float y = -10.f; y  < 10.0f; y+= 0.25f)
    //{
       // for (float x = -10.f; y < 10.0f; y += 0.25f)
      //  {
   // glm::vec4 col = { (x + 10) / 20.0f, 0.2f, (y + 10) / 20.0f, 1.0f };
       // }
    //}
  
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

