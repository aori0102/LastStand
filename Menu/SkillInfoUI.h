#pragma once

#include <GameComponent.h>
#include <Utils.h>

struct SkillNode;

class SkillInfoUI : public GameObject {

private:

	static const float BUTTON_COST_LABEL_OFFSET;
	static const float BUTTON_POINT_ICON_OFFSET;
	static const int COST_LABEL_FONT_SIZE;
	static const int SKILL_LABEL_FONT_SIZE;
	static const int SKILL_DESCRIPTION_FONT_SIZE;
	static const int COST_LABEL_FONT_SIZE;
	static const int FRAME_UNSELECTED_MESSAGE_FONT_SIZE;
	static const std::string FRAME_UNSELECTED_MESSAGE;
	static const Vector2 FRAME_POSITION;
	static const Vector2 ICON_FRAME_POSITION;
	static const Vector2 BUTTON_FRAME_POSITION;
	static const Vector2 SKILL_LABEL_OFFSET;
	static const Vector2 SKILL_DESCRIPTION_OFFSET;

	friend class Shop;

	GameObject* frame;
	GameObject* iconFrame;
	GameObject* buyButton;
	GameObject* buttonCostLabel;
	GameObject* buttonIcon;
	GameObject* skillLabel;
	GameObject* skillDescription;
	GameObject* frameUnselected;
	GameObject* frameUnselectedMessage;

	bool showingSkill;

	SkillInfoUI();
	void UpdateSkillInfo(SkillNode* skillNode);

};