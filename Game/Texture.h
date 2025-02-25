#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <Type.h>
#include <GameComponent.h>
#include <functional>

struct ButtonUIGroup {

	GameObject* button;
	GameObject* label;
	GameObject* image;

};

enum class ImageFill {

	Horizontal,
	Vertical,
	None,

};

class GameObject;

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

	float angle;
	float fillAmount;
	Color backgroundColor;
	Color outlineColor;

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

class Button : public GameComponent, public Texture {

private:

	bool isActive;

public:

	Color backgroundColor;

	Button(GameObject* initOwner);

	void Render() override;
	Bound GetBound();

	function<void()> OnClick;

	bool IsActive() const;

	void Disable();
	void Enable();

};