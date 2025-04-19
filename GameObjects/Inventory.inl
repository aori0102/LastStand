/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameComponent.h>

#include <vector>

#include <Item.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

template <class T>
std::vector<T*> Inventory::GetItemListOfType() {

	std::vector<T*> res;

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if ((it->second)->IsType<T>())
			res.push_back((it->second)->ToType<T>());

	}

	return res;

}