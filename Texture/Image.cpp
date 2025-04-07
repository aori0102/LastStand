/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Texture.h>

#include <GameCore.h>
#include <SDL_image.h>
#include <Transform.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Image::Image(GameObject* initOwner) : GameComponent(initOwner) {

	angle = 0.0f;

	imageFill = ImageFill::None;
	fillAmount = 1.0f;
	scale = 1.0f;

	stretchToTransform = false;

	clip = { 0, 0, 0, 0 };

	backgroundColor = Color::WHITE;
	outlineColor = Color::TRANSPARENT;

	linkedSprite = nullptr;

}

void Image::LinkSprite(Sprite* sprite, bool stretchWithTransform) {

	linkedSprite = sprite;

	stretchToTransform = stretchWithTransform;

	if (stretchToTransform)
		transform->scale = sprite->GetTextureDimension();

	clip = { 0, 0, static_cast<int>(sprite->GetTextureDimension().x), static_cast<int>(sprite->GetTextureDimension().y) };

}

void Image::Render() {

	if (linkedSprite && linkedSprite->GetTexture()) {

		SDL_Rect formatClip = clip;

		// Format
		Vector2 position = transform->position;
		Vector2 size = stretchToTransform ? transform->scale : Vector2(formatClip.w, formatClip.h);

		fillAmount = Math::Clamp(fillAmount, 0.0f, 1.0f);

		if (imageFill == ImageFill::Vertical) {

			formatClip.h *= fillAmount;
			position.y -= (size.y * (1.0f - fillAmount)) / 2.0f;
			size.y *= fillAmount;

		} else if (imageFill == ImageFill::Horizontal) {

			formatClip.w *= fillAmount;
			position.x -= (size.x * (1.0f - fillAmount)) / 2.0f;
			size.x *= fillAmount;

		}

		// Render
		GameCore::RenderCopy(
			linkedSprite,
			position,
			size * scale,
			showOnScreen,
			Owner()->GetLayer(),
			&formatClip,
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

		GameCore::DrawRectangle(center, extents, showOnScreen, true, backgroundColor, Owner()->GetLayer());
		GameCore::DrawRectangle(center, extents, showOnScreen, false, outlineColor, Owner()->GetLayer());

	}

}