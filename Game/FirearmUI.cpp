#include <PlayerUI.h>
#include <Firearm.h>
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
		throw new std::exception("Initializing reload UI with a null firearm");

	linkedFirearm = initFirearm;

}

void ReloadUI::Update() {


}

FirearmUI::FirearmUI(Firearm* initFirearm) {

	if (!linkedFirearm)
		throw new std::exception("Initialize firearm UI with null firearm");

	linkedFirearm = initFirearm;
	previousAmmo = linkedFirearm->CurrentAmmo();

	Text* text = AddComponent<Text>();
	text->LoadText(std::to_string(previousAmmo), Color::WHITE, AMMO_FONT_SIZE);

}

void FirearmUI::Update() {

	// Render the firearm's ammo count
	int ammo = linkedFirearm->CurrentAmmo();
	Text* text = GetComponent<Text>();

	if (ammo != previousAmmo) {

		// Update UI and data
		previousAmmo = ammo;

		text->LoadText(std::to_string(ammo), Color::WHITE, AMMO_FONT_SIZE);

	}

	Transform* textTransform = text->GetComponent<Transform>();
	textTransform->position = Vector2(
		Game::WindowResolution().x - textTransform->scale.x,
		Game::WindowResolution().y - textTransform->scale.y
	);
	text->Render();

}