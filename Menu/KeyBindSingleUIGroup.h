#pragma once

#include <GameObject.h>
#include <Utils.h>

enum class ActionIndex;

class KeyBindSingleUIGroup : public GameObject {

private:

	static const int LABEL_FONT_SIZE;
	static const int KEY_FONT_SIZE;
	static const float LABEL_OFFSET;

private:

	bool isSelected;
	ActionIndex bindAction;

	GameObject* label;
	GameObject* frame;
	GameObject* keyLabel;

public:

	KeyBindSingleUIGroup();
	~KeyBindSingleUIGroup();
	void SetPosition(Vector2 positionInSDL);
	void SetLabel(std::string initLabel);
	void BindAction(ActionIndex initBindAction);
	void Update() override;

};