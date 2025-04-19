/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>
#include <vector>

#include <GameObject.h>
#include <Utils.h>

enum class ActionIndex;

class Tutorial : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class UIElementIndex {
		Title,
		ReturnButton,
		ReturnLabel,
		Move,
		Sprint,
		Shoot,
		Aim,
		KillZombie,
		Shop,
		Inventory,
		Survive,

		Total,
	};

	const int TITLE_FONT_SIZE = 48;
	const int TUTORIAL_FONT_SIZE = 24;
	const int RETURN_LABEL_FONT_SIZE = 24;
	const float MESSAGE_OFFSET_Y = 59.0f;
	const float TITLE_OFFSET_Y = 33.0f;
	const std::string MESSAGE_PREFIX = "* ";
	const std::unordered_map<UIElementIndex, std::string> UI_LABEL_MAP = {
		{ UIElementIndex::Title, "Tutorial" },
		{ UIElementIndex::Move, "Move around with <Key_W>, <Key_A>, <Key_S>, <Key_D>." },
		{ UIElementIndex::Sprint, "Sprint with <Key_LeftShift>. Sprinting will also drain your stamina." },
		{ UIElementIndex::Shoot, "Use Left Mouse Button to shoot, <Key_R> to reload. Shooting accuracy can vary." },
		{ UIElementIndex::Aim, "Use Right Mouse Button to aim. Aiming help reduce sway, allowing for more accurate shooting." },
		{ UIElementIndex::KillZombie, "Killing zombies will award money and EXP. You will also be awarded money after each wave survived." },
		{ UIElementIndex::Shop, "You can purchase upgrades, items or skills with money and EXP. Press <Key_Tab> to open the shop." },
		{ UIElementIndex::Inventory, "Items you own are stored inside the inventory, which can be accessed by pressing <Key_I>." },
		{ UIElementIndex::Survive, "Survive for as long as you can!" },
		{ UIElementIndex::ReturnLabel, "Return" },
	};
	const Vector2 STARTING_POSITION = Vector2(101.0f, 164.0f);
	const Vector2 RETURN_BUTTON_POSITION = Vector2(540.0f, 654.0f);

	static const std::unordered_map<ActionIndex, std::string> KEY_BIND_PLACEHOLDER_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;

	static Tutorial* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeUI();
	void UpdateUI();
	void Show();
	void Hide();

public:

	Tutorial();
	~Tutorial();
	void UpdateActionBinding(ActionIndex actionIndex);

	static Tutorial* Instance();

};