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
/// METHOD DEFINITIONS
/// ----------------------------------

Pistol::Pistol(FirearmID initFirearmID) : Firearm(initFirearmID), Item(ItemIndex::Pistol) {

	switch (initFirearmID) {

	case FirearmID::M1911:
		break;

	default:
		throw std::exception("Invalid ID for pistol");

	}

	OnEquip = [this]() { ShowUI(); };
	OnDequip = [this]() { HideUI(); };

}

bool Pistol::TryUse(Player* player) {

	if (!TryShoot())
		return false;

	float damage = attributeMap.at(FirearmAttributeIndex::Damage);
	if (IsCrit())
		damage *= (1.0f + attributeMap.at(FirearmAttributeIndex::CriticalDamage));

	// Won't cause memory leak because of self destruction
	new Bullet(player, player->transform->position, player->GetAimingDirection(), damage);

	return true;

}