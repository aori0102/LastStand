#include <iostream>
#include <Game.h>
#include <exception>

int main(int argc, char* args[]) {

	std::cout << "Game starting..." << std::endl;

	if (!Game::Initialize())
		return -1;

	try {

		Game::InitializeGameObject();
		Game::Loop();

	} catch (std::exception* e) {

		std::cout << "Unexpected error: " << e->what() << std::endl;

	}

	return 0;

}