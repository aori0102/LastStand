﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameCore.h>

#include <iostream>
#include <sstream>

#include <AnimationManager.h>
#include <AudioManager.h>
#include <DataManager.h>
#include <GameComponent.h>
#include <GameManager.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <PhysicsManager.h>
#include <RenderManager.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SettingsUI.h>
#include <Texture.h>
#include <Tutorial.h>
#include <UIEventManager.h>
#include <Version.h>
#include <WaveManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float GameCore::CAMERA_ZOOM_SPEED = 14.0f;
const float GameCore::CAMERA_FOLLOW_SPEED = 9.0f;
const float GameCore::MAX_CAMERA_DISTANCE = 120.0f;

const Vector2 GameCore::MAP_ZONE = Vector2(3840.0f, 3840.0f);

const std::unordered_map<ActionIndex, SDL_Keycode> GameCore::DEFAULT_KEY_BINDING_MAP = {
	{ ActionIndex::MoveUp, SDLK_w },
	{ ActionIndex::MoveDown, SDLK_s },
	{ ActionIndex::MoveLeft, SDLK_a },
	{ ActionIndex::MoveRight, SDLK_d },
	{ ActionIndex::Reload, SDLK_r },
	{ ActionIndex::Sprint, SDLK_LSHIFT },
	{ ActionIndex::ToggleInventory, SDLK_i },
	{ ActionIndex::ToggleShop, SDLK_TAB },
};

bool GameCore::quit = false;
bool GameCore::selectedUI = false;
bool GameCore::isAnyKeyPressed = false;

float GameCore::time = 0.0f;
float GameCore::deltaTime = 0.0f;
float GameCore::currentCameraZoom = 1.0f;
float GameCore::targetCameraZoom = 1.0f;
float GameCore::sfxVolume = 1.0f;
float GameCore::masterVolume = 1.0f;
float GameCore::musicVolume = 1.0f;

std::string GameCore::gameName = "Last Stand";

std::unordered_map<SDL_Keycode, ActionState> GameCore::keyStateDictionary = {};
std::unordered_map<MouseButton, ActionState> GameCore::mouseButtonStateDictionary = {};
std::unordered_map<ActionIndex, SDL_Keycode> GameCore::keyMappingDictionary = {};

Vector2 GameCore::cameraPosition = Vector2::zero;
Vector2 GameCore::windowResolution = Vector2(1280.0f, 720.0f);

SDL_Keycode GameCore::lastKeyPressed = SDLK_0;

SDL_Event* GameCore::gameEvent = nullptr;
SDL_Renderer* GameCore::renderer = nullptr;
SDL_Window* GameCore::window = nullptr;

GameManager* GameCore::gameManager = nullptr;

GameObject* GameCore::cameraFocusObject = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void GameCore::UpdateEvent() {

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

	isAnyKeyPressed = false;

}

void GameCore::HandleEvent() {

	switch (gameEvent->type) {

	case SDL_QUIT:
		quit = true;
		break;

	case SDL_KEYDOWN: {
		SDL_Keycode keycode = gameEvent->key.keysym.sym;

		ActionState* keyState = FindKeyState(keycode);

		if (keyState && keyState->canceled) {

			keyState->canceled = false;
			keyState->performed = false;
			keyState->started = true;

			isAnyKeyPressed = true;
			lastKeyPressed = keycode;

		}
		break;

	}

	case SDL_KEYUP: {
		SDL_Keycode keycode = gameEvent->key.keysym.sym;

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
		switch (gameEvent->button.button) {

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
		switch (gameEvent->button.button) {

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

void GameCore::UpdateCamera() {

	if (!GameManager::Instance()->GameRunning())
		return;

	if (!cameraFocusObject)
		return;

	// Get focus object component and update camera
	float cameraSpeed = CAMERA_FOLLOW_SPEED *
		std::max(1.0f, (cameraPosition - cameraFocusObject->transform->position).Magnitude() / MAX_CAMERA_DISTANCE);

	cameraPosition = Vector2::Lerp(cameraPosition, cameraFocusObject->transform->position, deltaTime * cameraSpeed);
	cameraPosition.x = Math::Clamp(
		cameraPosition.x,
		(windowResolution.x - MAP_ZONE.x) / 2.0f,
		(-windowResolution.x + MAP_ZONE.x) / 2.0f
	);
	cameraPosition.y = Math::Clamp(
		cameraPosition.y,
		(windowResolution.y - MAP_ZONE.y) / 2.0f,
		(-windowResolution.y + MAP_ZONE.y) / 2.0f
	);
	currentCameraZoom = Math::Lerp(currentCameraZoom, targetCameraZoom, deltaTime * CAMERA_ZOOM_SPEED);

}

void GameCore::FlushManager() {

	std::cout << "Flushing Game Managers..." << std::endl;

	delete gameManager;
	gameManager = nullptr;

}

bool GameCore::InitializeProgram() {

	std::cout << "----------------------------------" << std::endl << std::endl;;
	std::cout << "[Core] Launching Last Stand " << GetVersionString() << std::endl << std::endl;
	std::cout << "----------------------------------" << std::endl << std::endl;

	try {

		gameEvent = new SDL_Event;

		std::string errorCode;

		// Initialize SDL2
		std::cout << "Initializing SDL2..." << std::endl;

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {

			errorCode = "Failed to initialize SDL2. SDL Error: ";
			errorCode += SDL_GetError();
			throw std::exception(errorCode.c_str());

		} else
			std::cout << "SDL2 initialized." << std::endl;

		// Create window
		window = SDL_CreateWindow(
			gameName.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			windowResolution.x,
			windowResolution.y,
			SDL_WINDOW_SHOWN);

		if (!window) {

			errorCode = "Failed to create window. SDL Error: ";
			errorCode += SDL_GetError();
			throw std::exception(errorCode.c_str());

		} else
			std::cout << "Window created." << std::endl;

		// Create renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (!renderer) {

			errorCode = "Failed to create renderer. SDL Error: ";
			errorCode += SDL_GetError();
			throw std::exception(errorCode.c_str());

		} else
			std::cout << "Renderer created." << std::endl;
		// Renderer settings
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		// Initialize IMG
		int imgFlag = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlag) & imgFlag)) {

			errorCode = "Failed to initialize SDL2 Image. IMG Error: ";
			errorCode += SDL_GetError();
			throw std::exception(errorCode.c_str());

		} else
			std::cout << "SDL2 Image initialized" << std::endl;

		// Initialize TTF
		if (TTF_Init() == -1) {

			errorCode = "Failed to initialize SDL2 TTF. TTF Error: ";
			errorCode += SDL_GetError();
			throw std::exception(errorCode.c_str());

		} else
			std::cout << "SDL2 TTF initialized" << std::endl;

		// Initialize MIX
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {

			errorCode = "Failed to initialize SDL2 Mixer. MIX Error: ";
			errorCode += Mix_GetError();
			throw std::exception(errorCode.c_str());

		} else
			std::cout << "SDL2 Mixer initialized" << std::endl;

		// Success, terminate
		std::cout << "Done!" << std::endl;
		return true;

	} catch (const std::exception& e) {

		std::cout << "Error initializing Manager: " << e.what() << std::endl;
		return false;

	}

	return true;

}

bool GameCore::InitializeManager() {

	try {

		std::cout << "Initializing GameManager..." << std::endl;
		gameManager = new GameManager;

	} catch (const std::exception& e) {

		std::cout << "Error initializing Manager: " << e.what() << std::endl;
		return false;

	}

	return true;

}

bool GameCore::InitializeSystem() {

	try {

		Random::Init();

	} catch (const std::exception& e) {

		std::cout << "Error initializing Manager: " << e.what() << std::endl;
		return false;

	}

	return true;

}

ActionState* GameCore::FindKeyState(SDL_Keycode keycode) {

	auto it = keyStateDictionary.find(keycode);

	if (it == keyStateDictionary.end())
		keyStateDictionary[keycode] = ActionState();

	return &keyStateDictionary.at(keycode);

}

ActionState* GameCore::FindMouseButtonState(MouseButton mouseButton) {

	auto it = mouseButtonStateDictionary.find(mouseButton);

	if (it == mouseButtonStateDictionary.end())
		return nullptr;

	return &mouseButtonStateDictionary[mouseButton];

}

void GameCore::SetRenderDrawColor(Color color) {

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

}

void GameCore::DrawLine(Vector2 position, Vector2 direction, float maxDistance, Color color) {

	SetRenderDrawColor(color);

	Vector2 renderPosition = position - cameraPosition + windowResolution / 2.0f;
	Vector2 renderEnd = renderPosition + direction.Normalize() * maxDistance;

	SDL_RenderDrawLineF(renderer, renderPosition.x, renderPosition.y, renderEnd.x, renderEnd.y);

}

void GameCore::DrawRectangle(Vector2 center, Vector2 extents, bool onScreen, bool fill, Color color, Layer layer) {

	SetRenderDrawColor(color);

	Vector2 renderCenter = !onScreen ? center - cameraPosition : center;

	if (RenderManager::Instance()->AffectByZoom(layer)) {

		extents *= currentCameraZoom;

		renderCenter *= currentCameraZoom;

	}

	renderCenter = Math::C00ToSDL(renderCenter, extents * 2.0f);

	SDL_FRect quad = {
		renderCenter.x,
		renderCenter.y,
		extents.x * 2.0f,
		extents.y * 2.0f
	};

	if (fill)
		SDL_RenderFillRectF(renderer, &quad);
	else
		SDL_RenderDrawRectF(renderer, &quad);

}

void GameCore::RenderCopy(Texture* texture, Vector2 position, Vector2 scale, bool onScreen, Layer layer, SDL_Rect* clip, float angle, SDL_RendererFlip flip) {

	// Calculate camera's area
	// This game use a different axis positioning comparing to SDL2.
	// (0, 0) in the center of the window instead of top left
	// Call it C00 (for center(0, 0))
	// Render position relative to screen in C00
	Vector2 renderPosition = !onScreen ? position - cameraPosition : position;

	if (RenderManager::Instance()->AffectByZoom(layer)) {

		renderPosition *= currentCameraZoom;

		scale *= currentCameraZoom;

	}

	renderPosition = Math::C00ToSDL(renderPosition, scale);

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

	SDL_RenderCopyExF(
		renderer,
		texture->GetTexture(),
		clip,
		&quad,
		angle,
		nullptr,	// Rotate by center of texture
		flip
	);

}

void GameCore::Loop() {

	while (!quit) {

		// Update time
		float currentTime = static_cast<float>(SDL_GetTicks64()) / 1000.0f;
		deltaTime = currentTime - time;
		time = currentTime;

		// Poll event
		UpdateEvent();
		while (SDL_PollEvent(gameEvent) != 0)
			HandleEvent();

		selectedUI = UIEventManager::Instance()->Update();

		// Clear renderer data
		SetRenderDrawColor(Color::TRANSPARENT);
		SDL_RenderClear(renderer);

		// Camera and background
		UpdateCamera();

		PhysicsManager::Instance()->Update();

		GameManager::Instance()->Update();

		PhysicsManager::Instance()->LateCollisionCall();

		RenderManager::Instance()->RenderAll();

		// Update renderer data
		SDL_RenderPresent(renderer);

	}

}

void GameCore::Close() {

	quit = true;
	delete gameEvent;
	gameEvent = nullptr;

	FlushManager();

	// Flush audio system
	Mix_CloseAudio();

	// Close window and renderer
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	// Close SDL libraries
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

}

void GameCore::LetCameraFocus(GameObject* gameObject) {

	cameraFocusObject = gameObject;

}

void GameCore::SetCameraZoom(float zoom) {

	targetCameraZoom = zoom;

}

void GameCore::ClearTexture(SDL_Texture* texture) {

	SDL_DestroyTexture(texture);
	texture = nullptr;

}

void GameCore::SetMusicVolume(float amount) {

	musicVolume = Math::Clamp(amount, 0.0f, 1.0f);
	Mix_VolumeMusic(MIX_MAX_VOLUME * amount * masterVolume);

}

void GameCore::SetSFXVolume(float amount) {

	sfxVolume = Math::Clamp(amount, 0.0f, 1.0f);
	Mix_Volume(-1, MIX_MAX_VOLUME * amount * masterVolume);

}

void GameCore::SetMasterVolume(float amount) {

	masterVolume = Math::Clamp(amount, 0.0f, 1.0f);
	Mix_VolumeMusic(MIX_MAX_VOLUME * amount * masterVolume);
	Mix_Volume(-1, MIX_MAX_VOLUME * amount * masterVolume);

}

void GameCore::SetActionKeyBind(ActionIndex actionIndex, SDL_Keycode keycode) {

	keyMappingDictionary[actionIndex] = keycode;

	Tutorial::Instance()->UpdateActionBinding(actionIndex);

}

void GameCore::SaveConfig() {

	PlayerConfig* config = DataManager::Instance()->playerConfig;

	config->masterVolume = masterVolume;
	config->sfxVolume = sfxVolume;
	config->musicVolume = musicVolume;
	config->keyBindingMap = keyMappingDictionary;

}

void GameCore::LoadConfig() {

	PlayerConfig* config = DataManager::Instance()->playerConfig;

	masterVolume = config->masterVolume;
	sfxVolume = config->sfxVolume;
	musicVolume = config->musicVolume;
	keyMappingDictionary = config->keyBindingMap;

	SettingsUI::Instance()->UpdateConfig();

}

void GameCore::QuitGame() {

	quit = true;

}

bool GameCore::SelectedUI() { return selectedUI; }

bool GameCore::Initialize() {

	return InitializeProgram() &&
		InitializeManager() &&
		InitializeSystem();

}

bool GameCore::IsAnyKeyPressed() { return isAnyKeyPressed; }

float GameCore::Time() { return time; }

float GameCore::DeltaTime() { return deltaTime; }

float GameCore::GetMasterVolume() { return masterVolume; }

float GameCore::GetSFXVolume() { return sfxVolume; }

float GameCore::GetMusicVolume() { return musicVolume; }

std::string GameCore::GetVersionString() {

	std::stringstream ss;
	ss << "v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;
	return ss.str();

}

std::string GameCore::GetAppDataPath() {

	const char* appData = std::getenv("APPDATA");

	if (appData)
		return std::string(appData);
	else
		throw std::exception("Cannot locate AppData path");

}

std::string GameCore::GetLastKeyInString() {

	return SDL_GetKeyName(lastKeyPressed);

}

ActionState GameCore::GetKeyState(SDL_Keycode keycode) {

	// Find the key
	return *FindKeyState(keycode);

}

ActionState GameCore::GetMouseState(MouseButton mouseButton) {

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

ActionState GameCore::GetActionState(ActionIndex actionIndex) {

	return GetKeyState(keyMappingDictionary.at(actionIndex));

}

Vector2 GameCore::WindowResolution() { return windowResolution; }

Vector2 GameCore::GetMouseInput() {

	int x, y;

	SDL_GetMouseState(&x, &y);

	return Vector2(x, y);

}

Vector2 GameCore::ScreenToWorldPosition(Vector2 screenPosition) {

	return Vector2(
		screenPosition.x - windowResolution.x / 2.0f,
		windowResolution.y / 2.0f - screenPosition.y
	) + cameraPosition;

}

SDL_Keycode GameCore::GetKeyBinded(ActionIndex actionIndex) {

	return keyMappingDictionary.at(actionIndex);

}

SDL_Keycode GameCore::GetLastKey() { return lastKeyPressed; }

SDL_Texture* GameCore::CreateTexture(SDL_Surface* loadedSurface) {

	return SDL_CreateTextureFromSurface(renderer, loadedSurface);

}

SDL_Texture* GameCore::CreateTexture(Vector2 size) {

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.x, size.y);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	return texture;

}