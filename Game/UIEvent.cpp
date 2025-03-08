#include <UIEvent.h>
#include <Texture.h>
#include <Game.h>

std::unordered_set<Button*> UIEvent::buttonSet = {};

bool UIEvent::Update() {

	if (!Game::GetMouseState(MouseButton::Left).started)
		return false;

	Vector2 mousePosition = Math::SDLToC00(Game::GetMouseInput(), Vector2::zero);

	auto it = buttonSet.begin();
	while (it != buttonSet.end()) {

		Bound bound = (*it)->GetBound();

		if (mousePosition.x > bound.Right() ||
			mousePosition.x < bound.Left() ||
			mousePosition.y > bound.Bottom() ||
			mousePosition.y < bound.Top()) {

			it++;

			continue;

		}

		// Button is pressed
		if ((*it)->IsActive() && (*it)->Owner()->IsActive()) {

			(*it)->OnClick();
			return true;

		}

		it++;

	}

	return false;

}

void UIEvent::RegisterButton(Button* button) {

	buttonSet.insert(button);

}