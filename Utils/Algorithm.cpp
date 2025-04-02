/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

std::vector<int> Algorithm::perlinPermutationTable = std::vector<int>(512, 0);

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

float Algorithm::PerlinGrad(int hash, Vector2 v) {

	int h = hash & 3;	// Select one of 4 gradient directions
	float a = h & 1 ? v.x : -v.x;
	float b = h & 2 ? v.y : -v.y;

	return a + b;

}

void Algorithm::PerlinInit() {

	std::vector<int> p(256);
	for (int i = 0; i < 256; i++)
		p[i] = i;

	Shuffle(p);

	for (int i = 0; i < 256; i++) {

		perlinPermutationTable[i] = p[i];
		perlinPermutationTable[256 + i] = p[i];	// Double array to prevent overflow

	}

}

float Algorithm::PerlinNoise(Vector2 v) {

	// Get integer grid coord
	int x_coord = (int)std::floorf(v.x) & 255;
	int y_coord = (int)std::floorf(v.y) & 255;

	// Get fractional part
	Vector2 fractional(v.x - floorf(v.x), v.y - floorf(v.y));

	// Apply fade function
	float a = Math::Fade(fractional.x);
	float b = Math::Fade(fractional.y);

	// Get gradient hashes for four corner
	int c1 = perlinPermutationTable[x_coord + perlinPermutationTable[y_coord]];
	int c2 = perlinPermutationTable[x_coord + perlinPermutationTable[y_coord + 1]];
	int c3 = perlinPermutationTable[x_coord + 1 + perlinPermutationTable[y_coord]];
	int c4 = perlinPermutationTable[x_coord + 1 + perlinPermutationTable[y_coord + 1]];

	// Compute dot product
	float g1 = PerlinGrad(c1, fractional);
	float g2 = PerlinGrad(c2, fractional + Vector2::left);
	float g3 = PerlinGrad(c3, fractional + Vector2::down);
	float g4 = PerlinGrad(c4, fractional + Vector2::left + Vector2::down);

	// Interpolate
	float lerp_x1 = Math::Lerp(g1, g2, a);
	float lerp_x2 = Math::Lerp(g3, g4, a);
	return Math::Lerp(lerp_x1, lerp_x2, b);

}