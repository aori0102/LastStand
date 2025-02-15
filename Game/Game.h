#pragma once

#include <unordered_map>
#include <unordered_set>
#include <SDL.h>
#include <Type.h>
#include <vector>

using namespace std;

enum class MouseButton {

	Left,
	Right,
	Middle,

	Total

};

class GameObject;
class Game {

public:

	struct ActionState {
		bool started = false;
		bool canceled = true;
	};

private:

	static void HandleEvent();

	static unordered_map<SDL_Keycode, ActionState> keyStateDictionary;
	static unordered_set<GameObject*> gameObjectSet;
	static vector<ActionState> mouseButtonState;

	static ActionState* FindKeyState(SDL_Keycode keycode);

public:

	// Game component
	static SDL_Window* gWindow;
	static SDL_Renderer* gRenderer;

	// Game control
	static SDL_Event* gEvent;
	static bool gQuit;
	static float time;
	static float deltaTime;

	static ActionState GetKeyState(SDL_Keycode keycode);
	static Vector2 GetMouseInput();
	static void SetRenderDrawColor(SDL_Color color);
	static void DrawLine(Vector2 start, Vector2 end, SDL_Color color);
	static ActionState GetMouseState(MouseButton mouseButton);

	// Initialization
	static bool Initialize();
	static void Loop();

	// Game
	static void InitializeGameObject();
	static void RegisterGameObject(GameObject* gameObject);
	static void UnregisterGameObject(GameObject* gameObject);

};

class Color {

public:

	static constexpr SDL_Color TRANSPARENT = { 0, 0, 0, 0 };
	static constexpr SDL_Color WHITE = { 255, 255, 255, 255 };
	static constexpr SDL_Color RED = { 255, 0, 0, 255 };
	static constexpr SDL_Color GREEN = { 0, 255, 0, 255 };
	static constexpr SDL_Color BLUE = { 0, 0, 255, 255 };

};