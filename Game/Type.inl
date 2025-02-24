#include <Type.h>
#include <algorithm>

template <typename T>
void Algorithm::Shuffle(vector<T>& array) {

	for (int i = array.size() - 1; i > 0; i--) {

		int randomIndex = Random::Int(0, i);
		std::swap(array[i], array[randomIndex]);

	}

}