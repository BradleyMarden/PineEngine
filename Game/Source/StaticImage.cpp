#pragma once
#include "StaticImage.h"


void StaticImage::Start()
{
	Pine::EventSystem::RegisterEventCallback(BIND_EVENT(StaticImage::Trigger));

	//cache render component
	m_RendComp = GetComponent<Pine::RendererComponent>("RendererComponent");

	//m_RendComp.lock()->LoadTexture("BG", "Assets/Background.png");


	//m_RendComp.lock()->DrawQuad({ 0,0 }, { Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName),Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) }, "BG", { 1.0,1.0,1.0,1.0 }, "Background", Pine::RendererComponent::BOTTOM);

	//m_RendComp.lock()->LoadTexture("BG", "Assets/Background.png");
	//m_RendComp.lock()->LoadTexture("Vinette", "Assets/Vinette.png");

	//m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 0.0,1.0,0.0,1.0 }, "thing", Pine::RendererComponent::TOP);
	//m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 1.0,0.0,0.0,1.0 }, "thing1", Pine::RendererComponent::TOP);
	//m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 0.0,0.0,1.0,1.0 }, "thing2", Pine::RendererComponent::TOP);
	//m_RendComp.lock()->DrawQuad({ 3,3 }, { 30 ,30 }, { 0.0,1.0,1.0,1.0 }, "thing3", Pine::RendererComponent::TOP);

	//m_RendComp.lock()->DrawQuad({ 40, 20 }, { 200 ,320.0f }, "Triangle", { 1.0,1.0,1.0,1.0 }, "Obstacle", Pine::RendererComponent::NONE);
	//m_RendComp.lock()->DrawQuad({ 300, 20 }, { 200 ,200.0f }, "Triangle", { 1.0,1.0,1.0,1.0 }, "Obstacle", Pine::RendererComponent::NONE);
	//m_RendComp.lock()->DrawQuad({ 800, 20 }, { 200 ,300.0f }, "Triangle", { 1.0,1.0,1.0,1.0 }, "Obstacle", Pine::RendererComponent::NONE);

	//m_RendComp.lock()->DrawQuad({ 50, 20 }, { 200 ,320.0f }, "TriangleTop", { 1.0,1.0,1.0,1.0 }, "ob", Pine::RendererComponent::NONE);
	//m_RendComp.lock()->DrawQuad({ 600, 20 }, { 200 ,200.0f }, "TriangleTop", { 1.0,1.0,1.0,1.0 }, "ob", Pine::RendererComponent::NONE);
	//m_RendComp.lock()->DrawQuad({ 400, 20 }, { 200 ,300.0f }, "TriangleTop", { 1.0,1.0,1.0,1.0 }, "ob", Pine::RendererComponent::NONE);

	//m_RendComp.lock()->DrawQuad({ Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName) / 2 - 150,20 }, { 30 ,30 }, "test", { 1.0,1.0,1.0,1.0 }, "Player", Pine::RendererComponent::NONE);
	//m_RendComp.lock()->DrawQuad({ 300,20 }, { 30 ,30 }, "PineLogo", { 1.0,1.0,1.0,0.5 }, "play", Pine::RendererComponent::NONE);
	//m_RendComp.lock()->DrawQuad({ 0,0 }, { Pine::Window::GetWindowWidth(Pine::Window::GetMainWindow()->s_WindowName),Pine::Window::GetWindowHeight(Pine::Window::GetMainWindow()->s_WindowName) }, "Vinette", { 1.0,1.0,1.0,1.0 }, "Vinette", Pine::RendererComponent::TOP);



}

void StaticImage::Update(float p_StepTime)
{


}



void StaticImage::Render()
{


}

void StaticImage::UIRender()
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
	ImGui::End();
	//IMGUI END

	//IMGUI RENDER
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	*/
}

void StaticImage::OnTerminate()
{

}

void StaticImage::Trigger(Pine::PEvent& e)
{

	if (&e == nullptr) { return; }

}
