/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

float Bound::Top() {

	return (center - extents).y;

}

float Bound::Left() {

	return (center - extents).x;

}

float Bound::Bottom() {

	return (center + extents).y;

}

float Bound::Right() {

	return (center + extents).x;

}