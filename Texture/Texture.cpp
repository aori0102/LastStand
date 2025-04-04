/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Texture.h>

#include <SDL.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Texture::Texture() {

	texture = nullptr;
	textureDimension = Vector2::zero;
	opacity = 1.0f;

}

Texture::~Texture() {

	FreeTexture();

}

void Texture::FreeTexture() {

	SDL_DestroyTexture(texture);
	texture = nullptr;

}

void Texture::SetOpacity(float amount) {

	opacity = amount;

	SDL_SetTextureAlphaMod(texture, opacity * 255);

}

SDL_Texture* Texture::GetTexture() { return texture; }

Vector2 Texture::GetTextureDimension() const { return textureDimension; }