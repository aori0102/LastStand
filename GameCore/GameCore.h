/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <SDL.h>
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

struct ActionState {
	bool started = false;
	bool performed = false;
	bool canceled = true;
};

class AnimationManager;
class Color;
class GameObject;
class GameManager;
class ItemManager;
class MediaManager;
class PhysicsManager;
class Texture;

class GameCore {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const float CAMERA_ZOOM_SPEED;
	static const float CAMERA_FOLLOW_SPEED;
	static const float CAMERA_WOBBLE_AMPLITUDE;
	static const float CAMERA_NOISE_AMPLITUDE;
	static const float CAMERA_WOBBLE_BASE_FREQUENCY;
	static const float CAMERA_POSITIONAL_DISTORTION_FREQUENCY;
	static const float CAMERA_ROTATIONAL_DISTORTION_FREQUENCY;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	// Run control
	static bool gQuit;

	// Interaction control
	static bool selectedUI;

	// Time
	static float time;
	static float deltaTime;

	// Camera settings
	static float currentCameraZoom;
	static float targetCameraZoom;

	static std::string gameName;

	static std::unordered_map<SDL_Keycode, ActionState> keyStateDictionary;
	static std::unordered_map<MouseButton, ActionState> mouseButtonStateDictionary;

	static std::unordered_set<GameObject*> gameObjectSet;
	
	static Vector2 cameraPosition;
	static Vector2 windowResolution;

	// SDL components
	static SDL_Event* gEvent;
	static SDL_Renderer* gRenderer;
	static SDL_Window* gWindow;

	// Managers
	static AnimationManager* animationManager;
	static GameManager* gameManager;
	static ItemManager* itemManager;
	static MediaManager* mediaManager;
	static PhysicsManager* physicsManager;

	// Camera
	static GameObject* cameraFocusObject;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	static void HandleEvent();
	static void UpdateEvent();
	static void UpdateCamera();

	static ActionState* FindKeyState(SDL_Keycode keycode);
	static ActionState* FindMouseButtonState(MouseButton mouseButton);

public:

	static void SetRenderDrawColor(Color color);
	static void DrawLine(Vector2 position, Vector2 direction, float maxDistance, Color color);
	static void DrawRectangle(Vector2 center, Vector2 extents, bool onScreen, bool fill, Color color, Layer layer);
	static void RenderCopy(Texture* texture, Vector2 position, Vector2 scale, bool onScreen, Layer layer, SDL_Rect* clip = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static void Loop();
	static void Close();
	static void InitializeGame();
	static void RegisterGameObject(GameObject* gameObject);
	static void UnregisterGameObject(GameObject* gameObject);
	static void LetCameraFocus(GameObject* gameObject);
	static void SetCameraZoom(float zoom);
	static void ClearTexture(SDL_Texture* texture);

	static bool SelectedUI();
	static bool Initialize();

	static float Time();
	static float DeltaTime();

	static ActionState GetKeyState(SDL_Keycode keycode);
	static ActionState GetMouseState(MouseButton mouseButton);

	static Vector2 WindowResolution();
	static Vector2 GetMouseInput();
	static Vector2 ScreenToWorldPosition(Vector2 screenPosition);

	static SDL_Texture* CreateTexture(SDL_Surface* loadedSurface);
	static SDL_Texture* CreateTexture(Vector2 size);

};