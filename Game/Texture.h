#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <Type.h>
#include <GameComponent.h>

enum class ImageFill {

	Horizontal,
	Vertical,
	None,

};

class Texture {

protected:

	SDL_Texture* texture;

	Vector2 textureDimension;

	Texture();

	void FreeTexture();

public:

	bool showOnScreen;

	virtual void Render() = 0;

	SDL_Texture* GetTexture();
	Vector2 TextureDimension() const;

};

class Image : public GameComponent, public Texture {

public:

	Vector2 pivot;
	float angle;
	float fillAmount;
	Color backgroundColor;

	ImageFill imageFill;

	Image(GameObject* initOwner);
	~Image();

	bool LoadImage(string path);

	void Render() override;

};

class Text : public GameComponent, public Texture {

private:

	TTF_Font* font;

public:

	Text(GameObject* initOwner);
	~Text();

	bool LoadText(string text, Color color, int fontSize);

	void Render() override;

};