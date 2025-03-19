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

	// Won't cause memory leak because of self destruction
	new Bullet(player, player->transform->position, player->GetAimingDirection(), 10);

	return true;

}

float Pistol::GetAttribute(FirearmAttributeIndex attributeIndex) {

	std::cout << "Undefined Pistol::GetAttribute()" << std::endl;

	return 0;

}