#include <Texture.h>
#include <SDL_image.h>
#include <GameCore.h>

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
	texture = GameCore::CreateTexture(loadedSurface);
	if (!texture) {

		std::cout << "Cannot get texture. SDL Error: " << SDL_GetError() << std::endl;
		return false;

	}

	// Finish up
	textureDimension = Vector2(loadedSurface->w, loadedSurface->h);

	// Clean
	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;

	return true;

}