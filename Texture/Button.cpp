/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Texture.h>

#include <GameCore.h>
#include <Transform.h>
#include <UIEventManager.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Button::ResetState() {

	isHeld = false;
	isHovered = false;

	OnMouseRelease();
	OnMouseLeave();

}

Button::Button(GameObject* initOwner) : GameComponent(initOwner) {

	backgroundColor = Color::WHITE;
	isActive = true;
	isHovered = false;
	isHeld = false;

	UIEventManager::Instance()->RegisterButton(this);

	OnClick = []() { return false; };
	OnMouseEnter = []() {};
	OnMouseLeave = []() {};
	OnMouseHolding = []() {};
	OnMouseBeginHold = []() {};
	OnMouseRelease = []() {};

}

void Button::Render() {

	Transform* transform = GetComponent<Transform>();

	GameCore::DrawRectangle(transform->position, transform->scale / 2.0f, true, true, backgroundColor, Owner()->GetLayer());

}

void Button::Disable() {

	isActive = false;

}

void Button::Enable() {

	isActive = true;

}

void Button::OnComponentDestroyed() {

	UIEventManager::Instance()->UnregisterButton(this);

}

bool Button::IsActive() const { return isActive; }

Bound Button::GetBound() {

	Bound bound;
	bound.center = transform->position;
	bound.extents = transform->scale / 2.0f;

	return bound;

}