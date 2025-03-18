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

Pistol::Pistol() : Item(ItemIndex::Pistol) {



}

bool Pistol::TryUse(Player* player) {

	std::cout << "Shoot pistol!!" << std::endl;

	return true;

}

float Pistol::GetAttribute(FirearmAttributeIndex attributeIndex) {

	return Firearm::BASE_ATTRIBUTE_MAP.at(ItemIndex::Pistol).at(attributeIndex)* attributeMultiplierMap.at(attributeIndex);

}