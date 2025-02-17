#include <PlayerUI.h>
#include <Item.h>
#include <Game.h>
#include <SDL.h>
#include <GameComponent.h>
#include <string>

// Reload UI
const Vector2 RELOAD_BAR_SIZE = Vector2(100.0f, 30.0f);
const Vector2 RELOAD_OUTLINE_SIZE = Vector2(110.0f, 40.0f);
const float RELOAD_BAR_CENTER_Y = 300.0f;

// Firearm UI
const int AMMO_FONT_SIZE = 30;

ReloadUI::ReloadUI(Firearm* initFirearm) {

	if (!initFirearm)
		throw new exception("Initializing reload UI with a null linkedFirearm");

	linkedFirearm = initFirearm;

}

void ReloadUI::Update() {

	if (linkedFirearm->IsReloading()) {

		SDL_FRect outlineQuad = {
			(Game::GetResolution().x - RELOAD_OUTLINE_SIZE.x) / 2.0f,
			RELOAD_BAR_CENTER_Y + (Game::GetResolution().y - RELOAD_OUTLINE_SIZE.y) / 2.0f,
			RELOAD_OUTLINE_SIZE.x,
			RELOAD_OUTLINE_SIZE.y
		};

		SDL_FRect fillQuad = {
			(Game::GetResolution().x - RELOAD_BAR_SIZE.x) / 2.0f,
			RELOAD_BAR_CENTER_Y + (Game::GetResolution().y - RELOAD_BAR_SIZE.y) / 2.0f,
			RELOAD_BAR_SIZE.x * linkedFirearm->GetReloadingProgress(),
			RELOAD_BAR_SIZE.y
		};

		Game::SetRenderDrawColor(Color::WHITE);
		Game::DrawRectangle(&outlineQuad, true, false);
		Game::DrawRectangle(&fillQuad, true, true);

	}

}

FirearmUI::FirearmUI(Firearm* initFirearm) {

	if (!linkedFirearm)
		throw new exception("Initialize firearm UI with null firearm");

	linkedFirearm = initFirearm;
	previousAmmo = linkedFirearm->GetCurrentAmmo();

	Text* text = AddComponent<Text>();
	text->LoadText(to_string(previousAmmo), Color::WHITE, AMMO_FONT_SIZE);

}

void FirearmUI::Update() {

	int ammo = linkedFirearm->GetCurrentAmmo();
	Text* text = GetComponent<Text>();

	if (ammo != previousAmmo) {

		// Update UI and data
		previousAmmo = ammo;

		text->LoadText(to_string(ammo), Color::WHITE, AMMO_FONT_SIZE);

	}

	Transform* textTransform = text->GetOwner()->GetComponent<Transform>();
	textTransform->position = Vector2(
		Game::GetResolution().x - textTransform->scale.x,
		Game::GetResolution().y - textTransform->scale.y
	);
	text->Render();

}