/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
const Color Color::RED = Color(255, 0, 0, 255);
const Color Color::GREEN = Color(0, 255, 0, 255);
const Color Color::BLUE = Color(0, 0, 255, 255);
const Color Color::WHITE = Color(255, 255, 255, 255);
const Color Color::YELLOW = Color(255, 255, 0, 255);
const Color Color::BLACK = Color(0, 0, 0, 255);

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Color::Color(Uint8 initR, Uint8 initG, Uint8 initB, Uint8 initA) {

	r = initR;
	g = initG;
	b = initB;
	a = initA;

}

Color::Color()
	: r(255), g(255), b(255), a(255) {}

SDL_Color Color::ToSDLColor() {

	return { r, g, b, a };

}