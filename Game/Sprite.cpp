#include <Texture.h>
#include <SDL_image.h>
#include <Game.h>

bool Sprite::LoadImage(std::string path) {

	FreeTexture();

	// Load image to surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	// Validate surface
	if (!loadedSurface) {

		std::cout << "Cannot load image. IMG Error: " << IMG_GetError() << std::endl;
		return false;

	}

	// Create image texture and validate
	texture = Game::CreateTexture(loadedSurface);
	if (!texture) {

		std::cout << "Cannot get texture. SDL Error: " << SDL_GetError() << std::endl;
		return false;

	}

	// Finish up
	textureDimension = Vector2(loadedSurface->w, loadedSurface->h);
	clip = { 0, 0, static_cast<int>(textureDimension.x), static_cast<int>(textureDimension.y) };

	// Clean
	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;

	return true;

}