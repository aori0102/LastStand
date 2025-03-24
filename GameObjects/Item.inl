#include <Item.h>

template <class T>
bool Item::IsType() {

	return ToType<T>() != nullptr;

}

template <class T>
T* Item::ToType() {

	T* converted = dynamic_cast<T*>(this);

	return converted;

}

