#include <GameComponent.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Game.h>
#include <cmath>
#include <Type.h>

// Font data
const string FONT_PATH = "./Asset/Font.ttf";
const int FONT_SIZE = 16;

Texture::Texture() {

	texture = nullptr;

	textureDimension = Vector2::zero;

	showOnScreen = true;

}

void Texture::FreeTexture() {

	SDL_DestroyTexture(texture);
	texture = nullptr;

}

SDL_Texture* Texture::GetTexture() { return texture; }

Vector2 Texture::GetTextureDimension() { return textureDimension; }

Image::Image(GameObject* initOwner) : GameComponent(initOwner) {

	pivot = Vector2(0.5f, 0.5f);
	angle = 0.0f;

	imageFill = ImageFill::None;
	fillAmount = 1.0f;

	backgroundColor = Color::WHITE;

}

Image::~Image() {

	FreeTexture();

}

bool Image::LoadImage(string path) {

	FreeTexture();

	// Load image to surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	// Validate surface
	if (!loadedSurface) {

		cout << "Cannot load image. IMG Error: " << IMG_GetError() << endl;
		return false;

	}

	// Create image texture and validate
	texture = Game::CreateTexture(loadedSurface);
	if (!texture) {

		cout << "Cannot get texture. SDL Error: " << SDL_GetError() << endl;
		return false;

	}

	// Finish up
	textureDimension = Vector2(loadedSurface->w, loadedSurface->h);
	GetOwner()->GetComponent<Transform>()->scale = textureDimension;

	// Clean
	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;

	return true;

}

void Image::Render() {

	Transform* transform = GetOwner()->GetComponent<Transform>();

	if (texture) {

		Vector2 clip(1.0f, 1.0f);
		if (imageFill == ImageFill::Vertical)
			clip.y = fillAmount;
		else if (imageFill == ImageFill::Horizontal)
			clip.x = fillAmount;

		Game::RenderCopy(
			this,
			transform->position,
			transform->scale,
			showOnScreen,
			clip,
			angle,
			pivot
		);

	} else {

		// No image texture, render background instead
		Game::SetRenderDrawColor(backgroundColor);
		SDL_FRect quad = {
			transform->position.x - transform->scale.x * pivot.x,
			transform->position.y - transform->scale.y * pivot.y,
			transform->scale.x,
			transform->scale.y
		};

		if (imageFill == ImageFill::Vertical)
			quad.h *= fillAmount;
		else if (imageFill == ImageFill::Horizontal)
			quad.w *= fillAmount;

		Game::DrawRectangle(&quad, showOnScreen, true);

	}

}

Text::Text(GameObject* initOwner) : GameComponent(initOwner) {

	font = TTF_OpenFont(FONT_PATH.c_str(), FONT_SIZE);
	if (!font)
		throw new exception("Cannot load font");

}

Text::~Text() {

	FreeTexture();

}

bool Text::LoadText(string text, Color color, int fontSize) {

	FreeTexture();

	// Load text
	TTF_SetFontSize(font, fontSize);
	SDL_Surface* loadedSurface = TTF_RenderText_Blended(font, text.c_str(), color.ToSDLColor());

	// Validate
	if (!loadedSurface) {

		cout << "Error loading text. TTF Error: " << TTF_GetError() << endl;
		return false;

	}

	// Apply texture and validate
	texture = Game::CreateTexture(loadedSurface);
	if (!texture) {

		cout << "Error loading texture. SDL Error: " << SDL_GetError() << endl;
		return false;

	}

	textureDimension = Vector2(loadedSurface->w, loadedSurface->h);
	GetOwner()->GetComponent<Transform>()->scale = textureDimension;

	// Clean up
	SDL_FreeSurface(loadedSurface);

	return true;

}

void Text::Render() {

	Transform* transform = GetOwner()->GetComponent<Transform>();

	Game::RenderCopy(this, transform->position, transform->scale, showOnScreen);

}