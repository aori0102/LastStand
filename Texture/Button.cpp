#include <Texture.h>
#include <UIEventManager.h>
#include <GameCore.h>

Button::Button(GameObject* initOwner) : GameComponent(initOwner) {

	backgroundColor = Color::WHITE;
	isActive = true;

	UIEventManager::Instance()->RegisterButton(this);

	OnClick = []() { return false; };
	OnMouseEnter = []() {};
	OnMouseLeave = []() {};

}

void Button::Render() {

	Transform* transform = GetComponent<Transform>();

	GameCore::DrawRectangle(transform->position, transform->scale / 2.0f, true, true, backgroundColor, Owner()->GetLayer());

}

Bound Button::GetBound() {

	Transform* transform = GetComponent<Transform>();

	Bound bound;
	bound.center = transform->position;
	bound.extents = transform->scale / 2.0f;

	return bound;

}

void Button::Disable() {

	isActive = false;

}

void Button::Enable() {

	isActive = true;

}

bool Button::IsActive() const { return isActive; }