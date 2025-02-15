#include <PlayerUI.h>
#include <Item.h>
#include <Game.h>

const Vector2 RELOAD_BAR_SIZE = Vector2(100.0f, 30.0f);
const float RELOAD_OUTLINE_PADDING = 5.0f;
const float RELOAD_BAR_CENTER_Y = 500.0f;

ReloadUI::ReloadUI(Firearm* initFirearm) {

	if (initFirearm)
		throw new exception("Initializing reload UI with a null linkedFirearm");

	linkedFirearm = initFirearm;

}

void ReloadUI::Update() {

	if (linkedFirearm->IsReloading()) {



	}

}