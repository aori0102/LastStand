#include <Game.h>
#include <GameComponent.h>
#include <Player.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <Enemy.h>
#include <iostream>

// Background path
const string BACKGROUND_PATH = "./Asset/Background.png";

// Colors
const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
const Color Color::RED = Color(255, 0, 0, 255);
const Color Color::GREEN = Color(0, 255, 0, 255);
const Color Color::BLUE = Color(0, 0, 255, 255);
const Color Color::WHITE = Color(255, 255, 255, 255);
const Color Color::YELLOW = Color(255, 255, 0, 255);
const Color Color::BLACK = Color(0, 0, 0, 255);

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
Vector2 Game::windowResolution = Vector2(1280.0f, 720.0f);
string Game::gameName = "Last Stand";
Vector2 Game::cameraPosition = Vector2::zero;
GameObject* Game::cameraFocusObject = nullptr;
GameObject* Game::background = nullptr;

Color::Color(Uint8 initR, Uint8 initG, Uint8 initB, Uint8 initA) {

	r = initR;
	g = initG;
	b = initB;
	a = initA;

}

SDL_Color Color::ToSDLColor() {

	return { r, g, b, a };

}

float Game::GetTime() { return time; }

float Game::GetDeltaTime() { return deltaTime; }

Vector2 Game::GetResolution() { return windowResolution; }

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
		gameName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowResolution.x,
		windowResolution.y,
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

	// Initialize TTF
	if (TTF_Init() == -1) {

		cout << "Failed to initialize SDL2 TTF. TTF Error: " << TTF_GetError() << endl;
		return false;

	} else
		cout << "SDL2 TTF initialized" << endl;

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

		UpdateCameraAndBackground();

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
	LetCameraFocus(player);

	// Enemy
	Enemy* enemy = new Enemy;

	// Background
	background = new GameObject;
	Image* backgroundImage = background->AddComponent<Image>();
	backgroundImage->LoadImage(BACKGROUND_PATH);

}

Vector2 Game::GetMouseInput() {

	int x, y;

	SDL_GetMouseState(&x, &y);

	return Vector2(x, y) + cameraPosition - windowResolution / 2.0f;

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

	return mouseButtonState[static_cast<int>(mouseButton)];

}

void Game::DrawLine(Vector2 position, Vector2 direction, float maxDistance, Color color) {

	SetRenderDrawColor(color);

	Vector2 renderPosition = position - cameraPosition + windowResolution / 2.0f;
	Vector2 renderEnd = renderPosition + direction.Normalize() * maxDistance;

	SDL_RenderDrawLineF(gRenderer, renderPosition.x, renderPosition.y, renderEnd.x, renderEnd.y);

}

void Game::DrawRectangle(SDL_FRect* quad, bool onScreen, bool fill) {

	Vector2 renderTopLeft =
		!onScreen ? (Vector2(quad->x, quad->y) - cameraPosition + windowResolution / 2.0f)
		: Vector2(quad->x, quad->y);

	quad->x = renderTopLeft.x;
	quad->y = renderTopLeft.y;

	if (fill)
		SDL_RenderFillRectF(gRenderer, quad);
	else
		SDL_RenderDrawRectF(gRenderer, quad);

}

void Game::DrawRectangle(Vector2 center, Vector2 extents, bool onScreen, bool fill) {

	Vector2 renderCenter =
		!onScreen ? (center - cameraPosition + windowResolution / 2.0f)
		: center;

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

void Game::RenderCopy(Texture* texture, Vector2 position, Vector2 scale, bool onScreen, Vector2 clip, float angle, Vector2 pivot, SDL_RendererFlip flip) {

	// Calculate camera's area

	// Render quad
	Vector2 renderPosition =
		!onScreen ? (position - cameraPosition + windowResolution / 2.0f)
		: position;
	SDL_FRect quad = {
		renderPosition.x - pivot.x * scale.x,
		renderPosition.y - pivot.y * scale.y,
		scale.x * clip.x,
		scale.y * clip.y
	};

	// Broad check if texture is out of camera view, if so, skip rendering
	if (quad.x > windowResolution.x ||
		quad.y > windowResolution.y ||
		quad.x + quad.w < 0.0f ||
		quad.y + quad.h < 0.0f
		)
		return;

	Vector2 textureDimension = texture->GetTextureDimension();

	pivot.x = Math::Clamp(pivot.x, 0.0f, 1.0f);
	pivot.y = Math::Clamp(pivot.y, 0.0f, 1.0f);
	SDL_FPoint center = { scale.x * pivot.x, scale.y * pivot.y };

	clip.x = Math::Clamp(clip.x, 0.0f, 1.0f);
	clip.y = Math::Clamp(clip.y, 0.0f, 1.0f);
	SDL_Rect clipRect = { 0, 0, textureDimension.x * clip.x, textureDimension.y * clip.y };

	SDL_RenderCopyExF(
		gRenderer,
		texture->GetTexture(),
		&clipRect,
		&quad,
		angle,
		&center,
		flip
	);

}

SDL_Texture* Game::CreateTexture(SDL_Surface* loadedSurface) {

	return SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

}

void Game::UpdateCameraAndBackground() {

	if (!cameraFocusObject)
		return;

	// Get focus object component and update camera
	Transform* focusTransform = cameraFocusObject->GetComponent<Transform>();
	cameraPosition = focusTransform->position;

	// Render background
	background->GetComponent<Transform>()->position = cameraPosition.Inverse();
	background->GetComponent<Image>()->Render();

	cout << background->GetComponent<Transform>()->position.x;
	cout << " " << background->GetComponent<Transform>()->position.y << endl;

}

void Game::LetCameraFocus(GameObject* gameObject) {

	cameraFocusObject = gameObject;

}