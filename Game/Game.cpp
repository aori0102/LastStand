#include <Game.h>
#include <GameComponent.h>
#include <Player.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <Zombie.h>
#include <iostream>
#include <GameManager.h>
#include <Texture.h>
#include <UIEvent.h>
#include <Physics.h>
#include <RenderManager.h>

// Initialize static component
bool Game::gQuit = false;
bool Game::selectedUI = false;
float Game::time = 0.0f;
float Game::deltaTime = 0.0f;
SDL_Window* Game::gWindow = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event* Game::gEvent = new SDL_Event;
std::unordered_map<SDL_Keycode, Game::ActionState> Game::keyStateDictionary = {};
std::unordered_map<MouseButton, Game::ActionState> Game::mouseButtonStateDictionary = {};
std::unordered_set<GameObject*> Game::gameObjectSet = {};
Vector2 Game::windowResolution = Vector2(1280.0f, 720.0f);
Vector2 Game::cameraPosition = Vector2::zero;
std::string Game::gameName = "Last Stand";
GameObject* Game::cameraFocusObject = nullptr;
GameManager* Game::gameManager = nullptr;

// Getter
float Game::Time() { return time; }

float Game::DeltaTime() { return deltaTime; }

Vector2 Game::WindowResolution() { return windowResolution; }

// Method
bool Game::Initialize() {

	// Initialize SDL2
	std::cout << "Initializing SDL2..." << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		std::cout << "Failed to initialize SDL2. SDL Error: " << SDL_GetError() << std::endl;
		return false;

	} else
		std::cout << "SDL2 initialized." << std::endl;

	// Create window
	gWindow = SDL_CreateWindow(
		gameName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowResolution.x,
		windowResolution.y,
		SDL_WINDOW_SHOWN);

	if (!gWindow) {

		std::cout << "Failed to create window. SDL Error: " << SDL_GetError() << std::endl;
		return false;

	} else
		std::cout << "Window created." << std::endl;

	// Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!gRenderer) {

		std::cout << "Failed to create renderer. SDL Error: " << SDL_GetError() << std::endl;
		return false;

	} else
		std::cout << "Renderer created." << std::endl;
	// Renderer settings
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	// Initialize IMG
	int imgFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlag) & imgFlag)) {

		std::cout << "Failed to initialize SDL2 Image. IMG Error: " << IMG_GetError() << std::endl;
		return false;

	} else
		std::cout << "SDL2 Image initialized" << std::endl;

	// Initialize TTF
	if (TTF_Init() == -1) {

		std::cout << "Failed to initialize SDL2 TTF. TTF Error: " << TTF_GetError() << std::endl;
		return false;

	} else
		std::cout << "SDL2 TTF initialized" << std::endl;

	// Success, terminate
	std::cout << "Done!" << std::endl;
	return true;

}

void Game::Loop() {

	while (!gQuit) {

		// Flush the game object beforehand
		GameObject::CleanUpCache();

		// Update time
		float currentTime = static_cast<float>(SDL_GetTicks64()) / 1000.0f;
		deltaTime = currentTime - time;
		time = currentTime;

		// Poll event
		UpdateEvent();
		while (SDL_PollEvent(gEvent) != 0)
			HandleEvent();

		selectedUI = UIEvent::Update();

		// Clear renderer data
		SetRenderDrawColor(Color::TRANSPARENT);
		SDL_RenderClear(gRenderer);

		// Camera and background
		UpdateCamera();

		Physics::Update();

		// Handle game object
		auto it = gameObjectSet.begin();

		while (it != gameObjectSet.end()) {

			(*it)->Update();

			it++;

		}

		Physics::LateCollisionCall();

		GameManager::Instance()->Update();

		RenderManager::RenderAll();

		// Update renderer data
		SDL_RenderPresent(gRenderer);

	}

}

void Game::Close() {

	// Flush game objects and components

	// Close window and renderer
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	// Close SDL libraries
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

void Game::UpdateEvent() {

	// Update the previous input event
	auto it_key = keyStateDictionary.begin();
	while (it_key != keyStateDictionary.end()) {

		if (it_key->second.started) {

			it_key->second.started = false;
			it_key->second.performed = true;

		}

		it_key++;

	}

	auto it_mouse = mouseButtonStateDictionary.begin();
	while (it_mouse != mouseButtonStateDictionary.end()) {

		if (it_mouse->second.started) {

			it_mouse->second.started = false;
			it_mouse->second.performed = true;

		}

		it_mouse++;

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

		if (keyState && keyState->canceled) {

			keyState->canceled = false;
			keyState->performed = false;
			keyState->started = true;

		}
		break;

	}

	case SDL_KEYUP: {
		SDL_Keycode keycode = gEvent->key.keysym.sym;

		ActionState* keyState = FindKeyState(keycode);
		 
		if (keyState) {

			keyState->canceled = true;
			keyState->performed = false;
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
		mouseButtonStateDictionary[static_cast<MouseButton>(mouseIndex)].started = true;
		mouseButtonStateDictionary[static_cast<MouseButton>(mouseIndex)].canceled = false;
		mouseButtonStateDictionary[static_cast<MouseButton>(mouseIndex)].performed = false;
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
		mouseButtonStateDictionary[static_cast<MouseButton>(mouseIndex)].canceled = true;
		mouseButtonStateDictionary[static_cast<MouseButton>(mouseIndex)].started = false;
		mouseButtonStateDictionary[static_cast<MouseButton>(mouseIndex)].performed = false;
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

Game::ActionState* Game::FindMouseButtonState(MouseButton mouseButton) {

	auto it = mouseButtonStateDictionary.find(mouseButton);

	if (it == mouseButtonStateDictionary.end())
		return nullptr;

	return &mouseButtonStateDictionary[mouseButton];

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

	gameManager = new GameManager;

	Random::Init();

}

Vector2 Game::ScreenToWorldPosition(Vector2 screenPosition) {

	return Vector2(
		screenPosition.x - windowResolution.x / 2.0f,
		windowResolution.y / 2.0f - screenPosition.y
	) + cameraPosition;

}

Vector2 Game::GetMouseInput() {

	int x, y;

	SDL_GetMouseState(&x, &y);

	return Vector2(x, y);

}

void Game::SetRenderDrawColor(Color color) {

	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);

}

void Game::RegisterGameObject(GameObject* gameObject) {

	gameObjectSet.insert(gameObject);

}

void Game::UnregisterGameObject(GameObject* gameObject) {

	gameObjectSet.erase(gameObject);

}

Game::ActionState Game::GetMouseState(MouseButton mouseButton) {

	// Find the key
	ActionState* mouseButtonState = FindMouseButtonState(mouseButton);

	// Create a key state if not already
	if (!mouseButtonState) {

		mouseButtonState = new ActionState;
		mouseButtonStateDictionary[mouseButton] = *mouseButtonState;
		delete mouseButtonState;

	}

	return mouseButtonStateDictionary[mouseButton];

}

void Game::DrawLine(Vector2 position, Vector2 direction, float maxDistance, Color color) {

	SetRenderDrawColor(color);

	Vector2 renderPosition = position - cameraPosition + windowResolution / 2.0f;
	Vector2 renderEnd = renderPosition + direction.Normalize() * maxDistance;

	SDL_RenderDrawLineF(gRenderer, renderPosition.x, renderPosition.y, renderEnd.x, renderEnd.y);

}

void Game::DrawRectangle(Vector2 center, Vector2 extents, bool onScreen, bool fill, Color color) {

	SetRenderDrawColor(color);

	Vector2 renderCenter = (!onScreen ? (center - cameraPosition) : center) + windowResolution / 2.0f;

	SDL_FRect quad = {
		renderCenter.x - extents.x,
		renderCenter.y - extents.y,
		extents.x * 2.0f,
		extents.y * 2.0f
	};

	if (fill)
		SDL_RenderFillRectF(gRenderer, &quad);
	else
		SDL_RenderDrawRectF(gRenderer, &quad);

}

void Game::RenderCopy(Texture* texture, Vector2 position, Vector2 scale, bool onScreen, SDL_Rect* clip, float angle, SDL_RendererFlip flip) {

	// Calculate camera's area
	// This game use a different axis positioning comparing to SDL2.
	// (0, 0) in the center of the window instead of top left
	// Call it C00 (for center(0, 0))
	// Render position relative to screen in C00
	Vector2 renderPosition = Math::C00ToSDL(!onScreen ? position - cameraPosition : position, scale);

	// Rendering format in SDL2
	SDL_FRect quad = {
		renderPosition.x,
		renderPosition.y,
		scale.x,
		scale.y
	};

	// Broad check if texture is out of camera view, if so, skip rendering
	if (quad.x > windowResolution.x ||
		quad.y > windowResolution.y ||
		quad.x + quad.w < 0.0f ||
		quad.y + quad.h < 0.0f
		)
		return;

	// Clipping texture

	SDL_RenderCopyExF(
		gRenderer,
		texture->GetTexture(),
		clip,
		&quad,
		angle,
		nullptr,	// Rotate by center of texture
		flip
	);

}

SDL_Texture* Game::CreateTexture(SDL_Surface* loadedSurface) {

	return SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

}

SDL_Texture* Game::CreateTexture(Vector2 size) {

	SDL_Texture* texture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.x, size.y);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	return texture;

}

void Game::ClearTexture(SDL_Texture* texture) {

	SDL_DestroyTexture(texture);
	texture = nullptr;

}

void Game::UpdateCamera() {

	if (!cameraFocusObject)
		return;

	// Get focus object component and update camera
	cameraPosition = cameraFocusObject->GetComponent<Transform>()->position;

}

void Game::LetCameraFocus(GameObject* gameObject) {

	cameraFocusObject = gameObject;

}

bool Game::SelectedUI() { return selectedUI; }