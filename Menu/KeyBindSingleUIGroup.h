/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameObject.h>
#include <Utils.h>

enum class ActionIndex;

class KeyBindSingleUIGroup : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const int LABEL_FONT_SIZE;
	static const int KEY_FONT_SIZE;
	static const float LABEL_OFFSET;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool isSelected;
	ActionIndex bindAction;

	GameObject* label;
	GameObject* frame;
	GameObject* keyLabel;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void UpdateVisual(std::string keyString);
	void Show();
	void Hide();

public:

	KeyBindSingleUIGroup();
	~KeyBindSingleUIGroup();
	void SetPosition(Vector2 positionInSDL);
	void SetLabel(std::string initLabel);
	void BindAction(ActionIndex initBindAction);
	void Update() override;

};