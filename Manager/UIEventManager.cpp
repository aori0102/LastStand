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

bool UIEventManager::Update() {

	Vector2 mousePosition = Math::SDLToC00(GameCore::GetMouseInput(), Vector2::zero);

	for (auto it = buttonSet.begin(); it != buttonSet.end(); it++) {

		if (!(*it)->IsActive() || !(*it)->Owner()->IsActive())
			continue;

		Bound bound = (*it)->GetBound();

		if (mousePosition.x > bound.Right() ||
			mousePosition.x < bound.Left() ||
			mousePosition.y > bound.Bottom() ||
			mousePosition.y < bound.Top()) {

			(*it)->OnMouseLeave();

			continue;

		}

		if (GameCore::GetMouseState(MouseButton::Left).started) {

			if ((*it)->OnClick())
				return true;

		}

		(*it)->OnMouseEnter();

	}

	return false;

}

UIEventManager* UIEventManager::Instance() { return instance; }