#pragma once

#ifdef PINE_PLATFORM_WINDOWS

extern Pine::Application* Pine::CreateApplication();


int main(int argc, char** argv)
{
	printf("Welcome to Pine Engine\n");
	auto app = Pine::CreateApplication();
	app->Run();
	delete app;
}

#endif