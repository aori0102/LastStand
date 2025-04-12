#include <GameComponent.h>

#include <vector>

#include <Item.h>

template <class T>
std::vector<T*> Inventory::GetItemListOfType() {

	std::vector<T*> res;

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if ((it->second)->item->IsType<T>())
			res.push_back((it->second)->item->ToType<T>());

	}

	return res;

}