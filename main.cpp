/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <iostream>
#include <GameCore.h>
#include <exception>

int main(int argc, char* args[]) {

	std::cout << "Game starting..." << std::endl;

	if (!GameCore::Initialize())
		return -1;

	try {

		GameCore::Loop();

	} catch (const std::exception& e) {

		std::cout << "Unexpected error: " << e.what() << std::endl;

	}

	std::cout << "Closing game..." << std::endl;

	GameCore::Close();

	std::cout << "Game Closed!" << std::endl;

	return 0;

}