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
#include <Utils.h>

class Color;
class GameObject;
class GameManager;
class Texture;

enum class MouseButton {

	Left,
	Right,
	Middle

};

enum class ActionIndex {

	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	Sprint,
	Reload,
	ToggleInventory,
	ToggleShop,

};

struct ActionState {
	bool started = false;
	bool performed = false;
	bool canceled = true;
};

class GameCore {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const float CAMERA_ZOOM_SPEED;
	static const float CAMERA_FOLLOW_SPEED;
	static const float MAX_CAMERA_DISTANCE;
	static const Vector2 MAP_ZONE;

public:

	static const std::unordered_map<ActionIndex, SDL_Keycode> DEFAULT_KEY_BINDING_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:
	
	static bool quit;
	static bool selectedUI;
	static bool isAnyKeyPressed;
	static float time;
	static float deltaTime;
	static float currentCameraZoom;
	static float targetCameraZoom;
	static float musicVolume;
	static float sfxVolume;
	static float masterVolume;
	static std::string gameName;
	static std::unordered_map<SDL_Keycode, ActionState> keyStateDictionary;
	static std::unordered_map<MouseButton, ActionState> mouseButtonStateDictionary;
	static std::unordered_map<ActionIndex, SDL_Keycode> keyMappingDictionary;
	static Vector2 cameraPosition;
	static Vector2 windowResolution;
	static SDL_Keycode lastKeyPressed;
	static GameManager* gameManager;
	static GameObject* cameraFocusObject;
	static SDL_Event* gameEvent;
	static SDL_Renderer* renderer;
	static SDL_Window* window;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	static void HandleEvent();
	static void UpdateEvent();
	static void UpdateCamera();
	static void FlushManager();
	static bool InitializeProgram();
	static bool InitializeManager();
	static bool InitializeSystem();
	static ActionState* FindKeyState(SDL_Keycode keycode);
	static ActionState* FindMouseButtonState(MouseButton mouseButton);

public:

	static void SetRenderDrawColor(Color color);
	static void DrawLine(Vector2 position, Vector2 direction, float maxDistance, Color color);
	static void DrawRectangle(Vector2 center, Vector2 extents, bool onScreen, bool fill, Color color, Layer layer);
	static void RenderCopy(Texture* texture, Vector2 position, Vector2 scale, bool onScreen, Layer layer, SDL_Rect* clip = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static void Loop();
	static void Close();
	static void LetCameraFocus(GameObject* gameObject);
	static void SetCameraZoom(float zoom);
	static void ClearTexture(SDL_Texture* texture);
	static void SetMusicVolume(float amount);
	static void SetSFXVolume(float amount);
	static void SetMasterVolume(float amount);
	static void SetActionKeyBind(ActionIndex actionIndex, SDL_Keycode keycode);
	static void SaveConfig();
	static void LoadConfig();
	static void QuitGame();
	static bool SelectedUI();
	static bool Initialize();
	static bool IsAnyKeyPressed();
	static float Time();
	static float DeltaTime();
	static float GetMasterVolume();
	static float GetSFXVolume();
	static float GetMusicVolume();
	static std::string GetVersionString();
	static std::string GetAppDataPath();
	static std::string GetLastKeyInString();
	static ActionState GetKeyState(SDL_Keycode keycode);
	static ActionState GetMouseState(MouseButton mouseButton);
	static ActionState GetActionState(ActionIndex actionIndex);
	static Vector2 WindowResolution();
	static Vector2 GetMouseInput();
	static Vector2 ScreenToWorldPosition(Vector2 screenPosition);
	static SDL_Keycode GetKeyBinded(ActionIndex actionIndex);
	static SDL_Keycode GetLastKey();
	static SDL_Texture* CreateTexture(SDL_Surface* loadedSurface);
	static SDL_Texture* CreateTexture(Vector2 size);

};