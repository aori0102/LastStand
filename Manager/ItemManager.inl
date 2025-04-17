#include <ItemManager.h>

#include <type_traits>

class Firearm;
class Ammunition;
class Consumable;
class Pistol;
class Rifle;
class Shotgun;

template <class T>
bool ItemManager::IsIndexOfType(ItemIndex itemIndex) {

	if (itemIndex == ItemIndex::None)
		return false;

	if (std::is_same<T, Firearm>::value) {

		switch (itemIndex) {

		case ItemIndex::Pistol_M1911:
		case ItemIndex::Shotgun_Beretta1301:
		case ItemIndex::Rifle_M4:
			return true;

		}

	} else if (std::is_same<T, Consumable>::value) {

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

	} else if (std::is_same<T, Pistol>::value) {

		switch (itemIndex) {

		case ItemIndex::Pistol_M1911:
			return true;

		}

	} else if (std::is_same<T, Shotgun>::value) {

		switch (itemIndex) {

		case ItemIndex::Shotgun_Beretta1301:
			return true;

		}

	} else if (std::is_same<T, Rifle>::value) {

		switch (itemIndex) {

		case ItemIndex::Rifle_M4:
			return true;

		}

	}

	return false;

}