#include <Texture.h>
#include <Game.h>
#include <MediaManager.h>

// Font data -- TODO: Refactor, make it clean
const std::string FONT_PATH = "./Asset/Font.ttf";
const int FONT_SIZE = 16;

Text::Text(GameObject* initOwner) : GameComponent(initOwner) {

	wrapLength = 0;

	mediaFont = MediaFont::RimouskiSb_Regular;

}

Text::~Text() {

	FreeTexture();

}

bool Text::LoadText(std::string text, Color color, int fontSize) {

	FreeTexture();

	// Load text
	TTF_SetFontSize(MediaManager::Instance()->GetFont(mediaFont), fontSize);
	SDL_Surface* loadedSurface = TTF_RenderText_Blended_Wrapped(MediaManager::Instance()->GetFont(mediaFont), text.c_str(), color.ToSDLColor(), wrapLength);

	// Validate
	if (!loadedSurface) {

		std::cout << "Error loading text. TTF Error: " << TTF_GetError() << std::endl;
		return false;

	}

	// Apply texture and validate
	texture = Game::CreateTexture(loadedSurface);
	if (!texture) {

		std::cout << "Error loading texture. SDL Error: " << SDL_GetError() << std::endl;
		return false;

	}

	textureDimension = Vector2(loadedSurface->w, loadedSurface->h);
	Owner()->GetComponent<Transform>()->scale = textureDimension;

	// Clean up
	SDL_FreeSurface(loadedSurface);

	return true;

}

void Text::Render() {

	Transform* transform = GetComponent<Transform>();

	Game::RenderCopy(this, transform->position, transform->scale, showOnScreen);

}