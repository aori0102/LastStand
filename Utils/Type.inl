#include <../Utils/Type.h>
#include <algorithm>

template <typename T>
void Algorithm::Shuffle(std::vector<T>& array) {

	for (int i = array.size() - 1; i > 0; i--) {

		int randomIndex = Random::Int(0, i);
		std::swap(array[i], array[randomIndex]);

	}

}

template <typename T>
requires std::is_arithmetic_v<T>
T Random::Sign(T value) {

	if (Random::Int(0, INT_MAX) & 1)
		return value;
	else
		return -value;

}