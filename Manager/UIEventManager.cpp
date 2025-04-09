/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <UIEventManager.h>

#include <exception>

#include <Texture.h>
#include <GameCore.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

UIEventManager* UIEventManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

UIEventManager::UIEventManager() {

	if (instance)
		throw std::exception("UIEventManager can only have 1 instance!");

	buttonSet = {};

	instance = this;

}

UIEventManager::~UIEventManager() {

	buttonSet.clear();

	instance = nullptr;

}

void UIEventManager::RegisterButton(Button* button) {

	buttonSet.insert(button);

}

void UIEventManager::UnregisterButton(Button* button) {

	buttonSet.erase(button);

}

bool UIEventManager::Update() {

	Vector2 mousePosition = Math::SDLToC00(GameCore::GetMouseInput(), Vector2::zero);
	bool buttonInteracted = false;

	for (auto button : buttonSet) {

		if (!button)
			continue;

		if (!button->isActive || !button->Owner()->IsActive()) {

			button->ResetState();
			continue;

		}

		Bound bound = button->GetBound();

		if (mousePosition.x > bound.Right() ||
			mousePosition.x < bound.Left() ||
			mousePosition.y > bound.Top() ||
			mousePosition.y < bound.Bottom()) {

			// Mouse is out of button's bound

			if (button->isHovered) {

				button->OnMouseLeave();
				button->OnMouseRelease();
				button->ResetState();

			}

			continue;

		}

		// The mouse is in the button's area
		if (!button->isHovered) {

			button->OnMouseEnter();
			button->isHovered = true;

		}

		if (GameCore::GetMouseState(MouseButton::Left).started && !button->isHeld) {

			button->OnMouseBeginHold();
			button->isHeld = true;
			buttonInteracted = true;

		} else if (GameCore::GetMouseState(MouseButton::Left).performed) {

			button->OnMouseHolding();
			buttonInteracted = true;

		} else if (GameCore::GetMouseState(MouseButton::Left).canceled && button->isHeld) {

			buttonInteracted = button->OnClick();
			button->OnMouseRelease();
			button->isHeld = false;

		}

	}

	return buttonInteracted;

}

UIEventManager* UIEventManager::Instance() { return instance; }