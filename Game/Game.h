#pragma once

#include <unordered_map>
#include <unordered_set>
#include <SDL.h>
#include <Type.h>
#include <vector>
#include <iostream>

using namespace std;

enum class MouseButton {

	Left,
	Right,
	Middle,

	Total

};

class GameObject;
class Texture;
class Color;

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

	// const
	static string gameName;
	static Vector2 windowResolution;

	// Game component
	static SDL_Window* gWindow;
	static SDL_Renderer* gRenderer;

	// Game control
	static SDL_Event* gEvent;
	static bool gQuit;
	static float time;
	static float deltaTime;

public:

	static ActionState GetKeyState(SDL_Keycode keycode);
	static Vector2 GetMouseInput();
	static ActionState GetMouseState(MouseButton mouseButton);

	// Rendering
	static void SetRenderDrawColor(Color color);
	static void DrawLine(Vector2 start, Vector2 end, Color color);
	static void DrawRectangle(SDL_FRect* quad, bool fill = false);
	static void RenderCopy(Texture* texture, Vector2 position, Vector2 scale, Vector2 clip = Vector2(1.0f, 1.0f), float angle = 0.0f, Vector2 pivot = Vector2::zero, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static SDL_Texture* CreateTexture(SDL_Surface* loadedSurface);

	// Initialization
	static bool Initialize();
	static void Loop();

	// Game
	static void InitializeGameObject();
	static void RegisterGameObject(GameObject* gameObject);
	static void UnregisterGameObject(GameObject* gameObject);

	// Getter
	static float GetTime();
	static float GetDeltaTime();
	static Vector2 GetResolution();

};

class Color {

public:

	Uint8 r, g, b, a;

	Color(Uint8 initR, Uint8 initG, Uint8 initB, Uint8 initA);

	SDL_Color ToSDLColor();

	static const Color TRANSPARENT;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color BLACK;

};