#pragma once

#include <unordered_map>
#include <unordered_set>
#include <SDL.h>
#include <vector>
#include <iostream>

#include <Type.h>

enum class UILayer {

	Default,
	Tooltip,
	Menu

};

enum class MouseButton {

	Left,
	Right,
	Middle

};

class GameObject;
class GameManager;
class MediaManager;
class Texture;
class Color;

class GameCore {

public:

	struct ActionState {
		bool started = false;
		bool performed = false;
		bool canceled = true;
	};

private:

	// Event control
	static SDL_Event* gEvent;
	static std::unordered_map<SDL_Keycode, ActionState> keyStateDictionary;
	static std::unordered_set<GameObject*> gameObjectSet;
	static std::unordered_map<MouseButton, ActionState> mouseButtonStateDictionary;

	static ActionState* FindKeyState(SDL_Keycode keycode);
	static ActionState* FindMouseButtonState(MouseButton mouseButton);

	// Game info
	static std::string gameName;
	static Vector2 windowResolution;

	// Game component
	static SDL_Window* gWindow;
	static SDL_Renderer* gRenderer;

	// Game control
	static bool gQuit;
	static float time;
	static float deltaTime;

	// --- MANAGERS ---
	static MediaManager* mediaManager;
	static GameManager* gameManager;

	static void HandleEvent();
	static void UpdateEvent();

	// Camera
	static float currentCameraZoom;
	static float targetCameraZoom;
	static const float CAMERA_ZOOM_SPEED;
	static Vector2 cameraPosition;
	static GameObject* cameraFocusObject;

	static void UpdateCamera();

	// UI and interaction control
	static bool selectedUI;

public:

	static ActionState GetKeyState(SDL_Keycode keycode);
	static Vector2 GetMouseInput();
	static Vector2 ScreenToWorldPosition(Vector2 screenPosition);
	static ActionState GetMouseState(MouseButton mouseButton);

	// Rendering
	static void SetRenderDrawColor(Color color);
	static void DrawLine(Vector2 position, Vector2 direction, float maxDistance, Color color);
	static void DrawRectangle(Vector2 center, Vector2 extents, bool onScreen, bool fill, Color color);
	static void RenderCopy(Texture* texture, Vector2 position, Vector2 scale, bool onScreen, Layer layer, SDL_Rect* clip = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static SDL_Texture* CreateTexture(SDL_Surface* loadedSurface);
	static SDL_Texture* CreateTexture(Vector2 size);
	static void ClearTexture(SDL_Texture* texture);

	// Core
	static bool Initialize();
	static void Loop();
	static void Close();

	// Game
	static void InitializeGameObject();
	static void RegisterGameObject(GameObject* gameObject);
	static void UnregisterGameObject(GameObject* gameObject);

	// Getter
	static float Time();
	static float DeltaTime();
	static Vector2 WindowResolution();

	// Camera control
	static void LetCameraFocus(GameObject* gameObject);
	static void SetCameraZoom(float zoom);
	static bool SelectedUI();

};