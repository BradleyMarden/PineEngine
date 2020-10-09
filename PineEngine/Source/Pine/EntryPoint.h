#pragma once

#ifdef PINE_PLATFORM_WINDOWS
extern Pine::Application* Pine::CreateApplication();


int main(int argc, char* argv[])
{
	//init logging
	Pine::Log::Init();
	PINE_ENGINE_WARN("Welcome to Pine Engine!");
	PINE_ENGINE_WARN("Created By Bradley Marden : Apache License 2.0");
	PINE_ENGINE_WARN("Initialized");

	//create application
	auto app = Pine::CreateApplication();
	app->Run(app);
	
	//after run has finished delete app
		

	delete app;
	return (0);
}

#endif