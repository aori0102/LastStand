/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <exception>

#include <Bullet.h>
#include <Player.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int Shotgun::PELLET = 8;
const float Shotgun::PELLET_SPAN_DEGREE = 12.0f;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Shotgun::Shotgun(FirearmID initFirearmID) : Firearm(initFirearmID), Item(ItemIndex::Shotgun) {

	switch (initFirearmID) {

	case FirearmID::Beretta1301:
		break;

	default:
		throw std::exception("Invalid ID for shotgun");

	}

	OnEquip = [this]() { ShowUI(); };
	OnDequip = [this]() { HideUI(); };

}

bool Shotgun::TryUse(Player* player) {

	if (!TryShoot())
		return false;

	Vector2 direction = player->GetAimingDirection();
	for (int i = 0; i < PELLET; i++) {

		float angle = Math::DegToRad(Random::Float(-PELLET_SPAN_DEGREE, PELLET_SPAN_DEGREE));

		// Won't cause memory leak because of self destruction
		new Bullet(player, player->transform->position, direction.Rotate(angle), 8);

	}

	return true;

}

float Shotgun::GetAttribute(FirearmAttributeIndex attributeIndex) {

	std::cout << "Undefined Shotgun::GetAttribute()" << std::endl;

	return 0;

}