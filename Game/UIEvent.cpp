#include <UIEvent.h>
#include <Texture.h>
#include <Game.h>

unordered_set<Button*> UIEvent::buttonSet = {};

void UIEvent::Update() {

	if (!Game::GetMouseState(MouseButton::Left).started)
		return;

	Vector2 mousePosition = Game::GetMouseInput();

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
			return;

		}

		it++;

	}

}

void UIEvent::RegisterButton(Button* button) {

	buttonSet.insert(button);

}