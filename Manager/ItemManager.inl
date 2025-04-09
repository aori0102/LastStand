#include <ItemManager.h>

#include <type_traits>

class Firearm;
class Ammunition;
class Consumable;
template <class T> 
bool ItemManager::IsIndexOfType(ItemIndex itemIndex) {

	if (itemIndex == ItemIndex::None)
		return false;

	static_assert(std::is_base_of<Item, T>::value, "T must inherit from Item");

	if (std::is_same<T, Firearm>::value) {

		switch (itemIndex) {

		case ItemIndex::Pistol_M1911:
		case ItemIndex::Shotgun_Beretta1301:
		case ItemIndex::Rifle_M4:
			return true;

		}

	}else if (std::is_same<T, Consumable>::value) {

		switch (itemIndex) {

		case ItemIndex::MedKit:
			return true;

		}

	} else if (std::is_same<T, Ammunition>::value) {

		switch (itemIndex) {

		case ItemIndex::Ammo_Slug:
		case ItemIndex::Ammo_556:
		case ItemIndex::Ammo_9mm:
			return true;

		}

	}

	return false;

}