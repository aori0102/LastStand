#include <Texture.h>
#include <SDL_image.h>
#include <Game.h>

Image::Image(GameObject* initOwner) : GameComponent(initOwner) {

	angle = 0.0f;

	imageFill = ImageFill::None;
	fillAmount = 1.0f;

	backgroundColor = Color::WHITE;
	outlineColor = Color::TRANSPARENT;

	linkedSprite = nullptr;

}

void Image::LinkSprite(Sprite* sprite) {

	linkedSprite = sprite;

	transform->scale = sprite->textureDimension;

}

void Image::Render() {

	if (linkedSprite && linkedSprite->texture) {

		// Format
		SDL_Rect clip = linkedSprite->clip;

		Vector2 position = transform->position;
		Vector2 scale = transform->scale;

		fillAmount = Math::Clamp(fillAmount, 0.0f, 1.0f);

		if (imageFill == ImageFill::Vertical) {

			clip.h *= fillAmount;
			position.y -= (scale.y * (1.0f - fillAmount)) / 2.0f;
			scale.y *= fillAmount;

		} else if (imageFill == ImageFill::Horizontal) {

			clip.w *= fillAmount;
			position.x -= (scale.x * (1.0f - fillAmount)) / 2.0f;
			scale.x *= fillAmount;

		}

		// Render
		Game::RenderCopy(
			linkedSprite,
			position,
			scale,
			showOnScreen,
			&clip,
			angle
		);

	} else {

		// No image texture, render background instead
		Vector2 center = transform->position;
		Vector2 extents = transform->scale / 2.0f;

		if (imageFill == ImageFill::Vertical) {

			center.y -= extents.y * (1.0f - fillAmount);
			extents.y *= fillAmount;

		} else if (imageFill == ImageFill::Horizontal) {

			center.x -= extents.x * (1.0f - fillAmount);
			extents.x *= fillAmount;

		}

		Game::DrawRectangle(center, extents, showOnScreen, true, backgroundColor);
		Game::DrawRectangle(center, extents, showOnScreen, false, outlineColor);

	}

}