#include <UIEventManager.h>
#include <Texture.h>
#include <GameCore.h>

std::unordered_set<Button*> UIEvent::buttonSet = {};

bool UIEvent::Update() {

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

void UIEvent::RegisterButton(Button* button) {

	buttonSet.insert(button);

}