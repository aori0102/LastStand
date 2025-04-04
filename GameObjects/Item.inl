/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Item.h>

#include <type_traits>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

template <class T>
bool Item::IsType() {

	return ToType<T>() != nullptr;

}

template <class T>
T* Item::ToType() {

	static_assert(std::is_base_of<Item, T>::value, "T must inherit from Item!");

	T* converted = dynamic_cast<T*>(this);

	return converted;

}

