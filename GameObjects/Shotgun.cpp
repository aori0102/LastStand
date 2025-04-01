/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <exception>

#include <Bullet.h>
#include <ItemManager.h>
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

	float baseDamage = attributeMap.at(FirearmAttributeIndex::Damage);;
	float damage;
	bool isCrit;
	Vector2 direction = player->GetAimingDirection();

	for (int i = 0; i < PELLET; i++) {

		isCrit = IsCrit();

		if (isCrit)
			damage = baseDamage * (1.0f + attributeMap.at(FirearmAttributeIndex::CriticalDamage));
		else
			damage = baseDamage;

		float angle = Math::DegToRad(Random::Float(-PELLET_SPAN_DEGREE, PELLET_SPAN_DEGREE));

		// Won't cause memory leak because of self destruction
		new Bullet(player->transform->position, direction.Rotate(angle), damage, isCrit);

	}

	return true;

}