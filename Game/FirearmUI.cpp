#include <PlayerUI.h>
#include <Item.h>
#include <Game.h>
#include <SDL.h>
#include <GameComponent.h>
#include <string>

const Vector2 RELOAD_BAR_SIZE = Vector2(100.0f, 30.0f);
const Vector2 RELOAD_OUTLINE_SIZE = Vector2(110.0f, 40.0f);
const float RELOAD_BAR_CENTER_Y = 300.0f;

ReloadUI::ReloadUI(Firearm* initFirearm) {

	if (!initFirearm)
		throw new exception("Initializing reload UI with a null linkedFirearm");

	linkedFirearm = initFirearm;

}

void ReloadUI::Update() {

	if (linkedFirearm->IsReloading()) {

		SDL_FRect outlineQuad = {
			(Game::windowResolution.x - RELOAD_OUTLINE_SIZE.x) / 2.0f,
			RELOAD_BAR_CENTER_Y + (Game::windowResolution.y - RELOAD_OUTLINE_SIZE.y) / 2.0f,
			RELOAD_OUTLINE_SIZE.x,
			RELOAD_OUTLINE_SIZE.y
		};

		SDL_FRect fillQuad = {
			(Game::windowResolution.x - RELOAD_BAR_SIZE.x) / 2.0f,
			RELOAD_BAR_CENTER_Y + (Game::windowResolution.y - RELOAD_BAR_SIZE.y) / 2.0f,
			RELOAD_BAR_SIZE.x * linkedFirearm->GetReloadingProgress(),
			RELOAD_BAR_SIZE.y
		};

		Game::SetRenderDrawColor(Color::WHITE);
		Game::DrawRectangle(&outlineQuad, false);
		Game::DrawRectangle(&fillQuad, true);

	}

}

FirearmUI::FirearmUI(Firearm* initFirearm) {

	if (!linkedFirearm)
		throw new exception("Initialize firearm UI with null firearm");
	
	linkedFirearm = initFirearm;
	previousAmmo = linkedFirearm->GetCurrentAmmo();

	AddComponent<Text>();

}

void FirearmUI::Update() {

	int ammo = linkedFirearm->GetCurrentAmmo();
	Text* text = GetComponent<Text>();

	if (ammo != previousAmmo) {

		// Update UI and data
		previousAmmo = ammo;

		text->LoadText(to_string(ammo), Color::WHITE);

	}

	text->GetOwner()->GetComponent<Transform>()->position = Vector2(700.0, 600.f);
	text->Render();

}