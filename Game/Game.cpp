#include <Game.h>
#include <GameComponent.h>
#include <Player.h>
#include <SDL_image.h>
#include <SDL.h>
#include <Enemy.h>

// Constants
const string GAME_NAME = "what the fuck";
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// Initialize static component
SDL_Window* Game::gWindow = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event* Game::gEvent = new SDL_Event;
bool Game::gQuit = false;
unordered_map<SDL_Keycode, Game::ActionState> Game::keyStateDictionary = {};
unordered_set<GameObject*> Game::gameObjectSet = {};
float Game::time = 0.0f;
float Game::deltaTime = 0.0f;
vector<Game::ActionState> Game::mouseButtonState = vector<Game::ActionState>(static_cast<int>(MouseButton::Total));

bool Game::Initialize() {

	// Initialize SDL2
	cout << "Initializing SDL2..." << endl;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		cout << "Failed to initialize SDL2. SDL Error: " << SDL_GetError() << endl;
		return false;

	} else
		cout << "SDL2 initialized." << endl;

	// Create window
	gWindow = SDL_CreateWindow(
		GAME_NAME.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!gWindow) {

		cout << "Failed to create window. SDL Error: " << SDL_GetError() << endl;
		return false;

	} else
		cout << "Window created." << endl;

	// Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!gRenderer) {

		cout << "Failed to create renderer. SDL Error: " << SDL_GetError() << endl;
		return false;

	} else
		cout << "Renderer created." << endl;

	// Initialize IMG
	int imgFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlag) & imgFlag)) {

		cout << "Failed to initialize SDL2 Image. IMG Error: " << IMG_GetError() << endl;
		return false;

	} else
		cout << "SDL2 Image initialized" << endl;

	// Success, terminate
	cout << "Done!" << endl;
	return true;

}

void Game::Loop() {

	while (!gQuit) {

		// Flush the game object before-hand
		GameObject::ObjectUpdate();

		// Update time
		float currentTime = static_cast<float>(SDL_GetTicks64()) / 1000.0f;
		deltaTime = currentTime - time;
		time = currentTime;

		// Poll event
		while (SDL_PollEvent(gEvent) != 0) {

			HandleEvent();

		}

		// Clear renderer data
		Game::SetRenderDrawColor(Color::TRANSPARENT);
		SDL_RenderClear(gRenderer);

		// Handle game object
		auto it = gameObjectSet.begin();

		while (it != gameObjectSet.end()) {

			(*it)->Update();

			it++;

		}

		// Update renderer data
		SDL_RenderPresent(gRenderer);

	}

}

void Game::HandleEvent() {

	switch (gEvent->type) {

	case SDL_QUIT:
		gQuit = true;
		break;

	case SDL_KEYDOWN: {
		SDL_Keycode keycode = gEvent->key.keysym.sym;

		ActionState* keyState = FindKeyState(keycode);

		if (keyState) {

			keyState->canceled = false;
			keyState->started = true;

		}
		break;

	}

	case SDL_KEYUP: {
		SDL_Keycode keycode = gEvent->key.keysym.sym;

		ActionState* keyState = FindKeyState(keycode);

		if (keyState) {

			keyState->canceled = true;
			keyState->started = false;

		}
		break;

	}

	case SDL_MOUSEBUTTONDOWN: {

		// Mouse index
		int mouseIndex = -1;

		// Get index
		switch (gEvent->button.button) {

		case SDL_BUTTON_LEFT:
			mouseIndex = static_cast<int>(MouseButton::Left);
			break;

		case SDL_BUTTON_RIGHT:
			mouseIndex = static_cast<int>(MouseButton::Right);
			break;

		case SDL_BUTTON_MIDDLE:
			mouseIndex = static_cast<int>(MouseButton::Middle);
			break;

		}

		// The button isn't recognised
		if (mouseIndex == -1)
			break;

		// Set button state
		mouseButtonState[mouseIndex].started = true;
		mouseButtonState[mouseIndex].canceled = false;
		break;

	}

	case SDL_MOUSEBUTTONUP: {

		// Mouse index
		int mouseIndex = -1;

		// Get index
		switch (gEvent->button.button) {

		case SDL_BUTTON_LEFT:
			mouseIndex = static_cast<int>(MouseButton::Left);
			break;

		case SDL_BUTTON_RIGHT:
			mouseIndex = static_cast<int>(MouseButton::Right);
			break;

		case SDL_BUTTON_MIDDLE:
			mouseIndex = static_cast<int>(MouseButton::Middle);
			break;

		}

		// The button isn't recognised
		if (mouseIndex == -1)
			break;

		// Set button state
		mouseButtonState[mouseIndex].canceled = true;
		mouseButtonState[mouseIndex].started = false;
		break;

	}

	}

}

Game::ActionState* Game::FindKeyState(SDL_Keycode keycode) {

	auto it = keyStateDictionary.find(keycode);

	if (it == keyStateDictionary.end())
		return nullptr;

	return &keyStateDictionary[keycode];

}

Game::ActionState Game::GetKeyState(SDL_Keycode keycode) {

	// Find the key
	ActionState* keyState = FindKeyState(keycode);

	// Create a key state if not already
	if (!keyState) {

		keyState = new ActionState;
		keyStateDictionary[keycode] = *keyState;
		delete keyState;

	}

	return keyStateDictionary[keycode];

}

void Game::InitializeGameObject() {

	// Player
	Player* player = new Player;
	player->name = "Player";
	
	Enemy* enemy = new Enemy;

}

Vector2 Game::GetMouseInput() {

	int x, y;

	SDL_GetMouseState(&x, &y);

	return Vector2(x, y);

}

void Game::SetRenderDrawColor(SDL_Color color) {

	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);

}

void Game::RegisterGameObject(GameObject* gameObject) {

	gameObjectSet.insert(gameObject);

}

void Game::UnregisterGameObject(GameObject* gameObject) {

	gameObjectSet.erase(gameObject);

}

Game::ActionState Game::GetMouseState(MouseButton mouseButton) {

	return mouseButtonState[static_cast<int>(mouseButton)];

}

void Game::DrawLine(Vector2 start, Vector2 end, SDL_Color color) {

	SetRenderDrawColor(color);

	SDL_RenderDrawLineF(gRenderer, start.x, start.y, end.x, end.y);

}