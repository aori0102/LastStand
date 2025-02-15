#include <GameComponent.h>
#include <SDL_image.h>
#include <Game.h>
#include <cmath>

Image::Image(GameObject* initOwner) : GameComponent(initOwner) {

	texture = nullptr;

	position = Vector2::zero;
	size = Vector2::zero;
	imageDimension = Vector2::zero;

	pivot = Vector2(0.5f, 0.5f);
	angle = 0.0f;

	imageFill = ImageFill::None;
	fillAmount = 1.0f;

}

Image::~Image() {

	FreeImage();

}

bool Image::LoadImage(string path) {

	// Load image to surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	// Validate surface
	if (!loadedSurface) {

		cout << "Cannot load image. IMG Error: " << IMG_GetError() << endl;
		return false;

	}

	// Get size
	size = Vector2(loadedSurface->w, loadedSurface->h);
	imageDimension = size;

	// Create image texture
	SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);

	// Validate texture
	if (!loadedTexture) {

		cout << "Cannot get texture. SDL Error: " << SDL_GetError() << endl;
		return false;

	}

	// Finish up
	texture = loadedTexture;

	// Clean
	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;

	return true;

}

void Image::Render() {

	if (!texture)
		return;

	// Calculate image position
	pivot = Vector2(Math::Clamp(pivot.x, 0.0f, 1.0f), Math::Clamp(pivot.y, 0.0f, 1.0f));
	SDL_FPoint center = { size.x * pivot.x, size.y * pivot.y };
	SDL_FRect renderQuad = { position.x - center.x, position.y - center.y, size.x, size.y };

	// Calculate image clip
	SDL_Rect clip = { 0, 0, imageDimension.x, imageDimension.y };
	if (imageFill == ImageFill::Vertical) {
		clip.h *= Math::Clamp(fillAmount, 0.0f, 1.0f);
		renderQuad.h *= Math::Clamp(fillAmount, 0.0f, 1.0f);
	} else if (imageFill == ImageFill::Horizontal) {
		clip.w *= Math::Clamp(fillAmount, 0.0f, 1.0f);
		renderQuad.w *= Math::Clamp(fillAmount, 0.0f, 1.0f);
	}

	// Render
	SDL_RenderCopyExF(Game::gRenderer, texture, &clip, &renderQuad, angle, &center, SDL_FLIP_NONE);

}

void Image::FreeImage() {

	SDL_DestroyTexture(texture);
	texture = nullptr;

}