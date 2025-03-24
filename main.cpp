#include <iostream>
#include <GameCore/GameCore.h>
#include <exception>

int main(int argc, char* args[]) {

	std::cout << "Game starting..." << std::endl;

	if (!GameCore::Initialize())
		return -1;

	try {

		GameCore::InitializeGame();
		GameCore::Loop();

	} catch (const std::exception& e) {

		std::cout << "Unexpected error: " << e.what() << std::endl;

	}

	return 0;

}