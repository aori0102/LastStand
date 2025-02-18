#include <PlayerUI.h>
#include <Item.h>
#include <Game.h>
#include <SDL.h>
#include <GameComponent.h>
#include <string>
#include <Texture.h>

// Reload UI
const Vector2 RELOAD_BAR_SIZE = Vector2(100.0f, 30.0f);
const Vector2 RELOAD_OUTLINE_SIZE = Vector2(110.0f, 40.0f);
const float RELOAD_BAR_CENTER_Y = 300.0f;

// Firearm UI
const int AMMO_FONT_SIZE = 30;

ReloadUI::ReloadUI(Firearm* initFirearm) {

	if (!initFirearm)
		throw new exception("Initializing reload UI with a null firearm");

	linkedFirearm = initFirearm;

}

void ReloadUI::Update() {

	if (linkedFirearm->IsReloading()) {
		// Render a box indicating the reload progress when
		// the firearm reloads
		SDL_FRect outlineQuad = {
			(Game::WindowResolution().x - RELOAD_OUTLINE_SIZE.x) / 2.0f,
			RELOAD_BAR_CENTER_Y + (Game::WindowResolution().y - RELOAD_OUTLINE_SIZE.y) / 2.0f,
			RELOAD_OUTLINE_SIZE.x,
			RELOAD_OUTLINE_SIZE.y
		};

		SDL_FRect fillQuad = {
			(Game::WindowResolution().x - RELOAD_BAR_SIZE.x) / 2.0f,
			RELOAD_BAR_CENTER_Y + (Game::WindowResolution().y - RELOAD_BAR_SIZE.y) / 2.0f,
			RELOAD_BAR_SIZE.x * linkedFirearm->GetReloadingProgress(),
			RELOAD_BAR_SIZE.y
		};

		Game::DrawRectangle(&outlineQuad, true, false, Color::WHITE);
		Game::DrawRectangle(&fillQuad, true, true, Color::WHITE);

	}

}

FirearmUI::FirearmUI(Firearm* initFirearm) {

	if (!linkedFirearm)
		throw new exception("Initialize firearm UI with null firearm");

	linkedFirearm = initFirearm;
	previousAmmo = linkedFirearm->CurrentAmmo();

	Text* text = AddComponent<Text>();
	text->LoadText(to_string(previousAmmo), Color::WHITE, AMMO_FONT_SIZE);

}

void FirearmUI::Update() {

	// Render the firearm's ammo count
	int ammo = linkedFirearm->CurrentAmmo();
	Text* text = GetComponent<Text>();

	if (ammo != previousAmmo) {

		// Update UI and data
		previousAmmo = ammo;

		text->LoadText(to_string(ammo), Color::WHITE, AMMO_FONT_SIZE);

	}

	Transform* textTransform = text->GetComponent<Transform>();
	textTransform->position = Vector2(
		Game::WindowResolution().x - textTransform->scale.x,
		Game::WindowResolution().y - textTransform->scale.y
	);
	text->Render();

}