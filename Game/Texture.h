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

enum class MediaFont;
class GameObject;
class Image;
class AnimationClip;

class RenderComponent {

public:

	bool showOnScreen;

	virtual void Render() = 0;

};

class Texture {

protected:

	SDL_Texture* texture;

	Vector2 textureDimension;

	Texture();

	void FreeTexture();

public:

	SDL_Texture* GetTexture();
	Vector2 TextureDimension() const;

};

class Sprite : public Texture {

private:

	SDL_Rect clip;

	friend class Image;
	friend class AnimationClip;

public:

	bool LoadImage(std::string path);

};

class Image : public GameComponent, public RenderComponent {

private:

	Sprite* linkedSprite;

public:

	float angle;
	float fillAmount;
	Color backgroundColor;
	Color outlineColor;

	ImageFill imageFill;

	Image(GameObject* initOwner);
	
	void LinkSprite(Sprite* sprite);
	void Render();

};

class Text : public GameComponent, public Texture, public RenderComponent {

private:

public:

	MediaFont mediaFont;

	int wrapLength;

	Text(GameObject* initOwner);
	~Text();

	bool LoadText(std::string text, Color color, int fontSize);

	void Render() override;

};

class Button : public GameComponent, public RenderComponent {

private:

	bool isActive;

public:

	Color backgroundColor;

	Button(GameObject* initOwner);

	void Render() override;
	Bound GetBound();

	std::function<void()> OnClick;

	bool IsActive() const;

	void Disable();
	void Enable();

};