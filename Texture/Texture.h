/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>

#include <GameComponent.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <Utils.h>

class GameObject;
class Image;
enum class MediaFont;

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

class RenderComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	bool showOnScreen;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	RenderComponent() : showOnScreen(true) {}
	virtual void Render() = 0;

};

class Texture {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

protected:

	float opacity;
	SDL_Texture* texture;
	Vector2 textureDimension;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Texture();
	virtual ~Texture();
	void FreeTexture();
	void SetOpacity(float amount);
	SDL_Texture* GetTexture();
	Vector2 GetTextureDimension() const;

};

class Sprite : public Texture {

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	bool LoadImage(std::string path);
	void SetColorMod(Color color);

};

class Image : public GameComponent, public RenderComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool stretchToTransform;
	Sprite* linkedSprite;

public:

	float angle;
	float fillAmount;
	float scale;
	Color backgroundColor;
	Color outlineColor;
	Color colorModulo;
	SDL_Rect clip;

	ImageFill imageFill;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Image(GameObject* initOwner);
	void LinkSprite(Sprite* sprite, bool stretchWithTransform);
	void Render();
	void SetColorModulo(Color color);

};

class Text : public GameComponent, public Texture, public RenderComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	int wrapLength;
	MediaFont mediaFont;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Text(GameObject* initOwner);
	~Text();
	bool LoadText(std::string text, Color color, int fontSize);
	void Render() override;

};

class Button : public GameComponent, public RenderComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool isActive;
	bool isHovered;
	bool isHeld;

	friend class UIEventManager;

public:

	std::function<bool()> OnClick;
	std::function<void()> OnMouseEnter;
	std::function<void()> OnMouseLeave;
	std::function<void()> OnMouseBeginHold;
	std::function<void()> OnMouseHolding;
	std::function<void()> OnMouseRelease;
	Color backgroundColor;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void ResetState();

public:

	Button(GameObject* initOwner);
	void Render() override;
	void Disable();
	void Enable();
	bool IsActive() const;
	void OnComponentDestroyed() override;
	Bound GetBound();

};