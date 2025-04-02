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
/// METHOD DEFINITIONS
/// ----------------------------------

Rifle::Rifle(ItemIndex initItemIndex) : Firearm(initItemIndex) {

	switch (initItemIndex) {

	case ItemIndex::Rifle_M4:
		break;

	default:
		throw std::exception("Invalid ID for pistol");

	}

}

bool Rifle::TryUse(Player* player) {
	
	if (!TryShoot())
		return false;

	float damage = attributeMap.at(FirearmAttributeIndex::Damage);
	bool isCrit = IsCrit();
	if (isCrit)
		damage *= (1.0f + attributeMap.at(FirearmAttributeIndex::CriticalDamage));

	// Won't cause memory leak because of self destruction
	new Bullet(player->transform->position, player->GetAimingDirection(), damage, isCrit);

	return true;

}