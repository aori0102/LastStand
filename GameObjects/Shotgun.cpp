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

Shotgun::Shotgun(ItemIndex initItemIndex) : Firearm(initItemIndex) {

	switch (initItemIndex) {

	case ItemIndex::Shotgun_Beretta1301:
		break;

	default:
		throw std::exception("Invalid ID for shotgun");

	}

}

bool Shotgun::TryUse(Player* player) {

	if (!TryShoot())
		return false;

	float damage = attributeMap.at(FirearmAttributeIndex::Damage);
	if (IsCrit())
		damage *= (1.0f + attributeMap.at(FirearmAttributeIndex::CriticalDamage));

	Vector2 direction = player->GetAimingDirection();
	for (int i = 0; i < PELLET; i++) {

		float angle = Math::DegToRad(Random::Float(-PELLET_SPAN_DEGREE, PELLET_SPAN_DEGREE));

		// Won't cause memory leak because of self destruction
		new Bullet(player, player->transform->position, direction.Rotate(angle), damage);

	}

	return true;

}