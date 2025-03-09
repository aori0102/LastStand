#include <Texture.h>
#include <SDL.h>

Texture::Texture() {

	texture = nullptr;

	textureDimension = Vector2::zero;

}

void Texture::FreeTexture() {

	SDL_DestroyTexture(texture);
	texture = nullptr;

}

SDL_Texture* Texture::GetTexture() { return texture; }

Vector2 Texture::TextureDimension() const { return textureDimension; }