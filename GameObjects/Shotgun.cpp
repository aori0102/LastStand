/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <Player.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Shotgun::Shotgun() : Item(ItemIndex::Shotgun) {



}

bool Shotgun::TryUse(Player* player) {

	std::cout << "Shoot Shotgun!!" << std::endl;

	return true;

}

float Shotgun::GetAttribute(FirearmAttributeIndex attributeIndex) {

	return Firearm::BASE_ATTRIBUTE_MAP.at(ItemIndex::Shotgun).at(attributeIndex) * attributeMultiplierMap.at(attributeIndex);

}