#include <iostream>
#include <Game.h>

using namespace std;

int main(int argc, char* args[]) {

	cout << "Game starting..." << endl;

	if (!Game::Initialize())
		return -1;

	try {

		Game::InitializeGameObject();
		Game::Loop();

	} catch (exception* e) {

		cout << "Unexpected error: " << e->what() << endl;

	}

	return 0;

}