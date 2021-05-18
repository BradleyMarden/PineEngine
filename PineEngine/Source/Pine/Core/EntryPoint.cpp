#pragma once
#include <iostream>
#include <Pine.h>
//#ifdef PINE_PLATFORM_WINDOWS

extern Pine::Game* Pine::CreateGame();


int main(int argc, const char* argv[])
{
	auto game = Pine::CreateGame();
	std::cout << "Started" << std::endl;
	game->Initialize();
	delete game;

}
//#endif