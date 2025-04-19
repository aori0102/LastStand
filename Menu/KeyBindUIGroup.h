/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameObject.h>
#include <SDL.h>
#include <Utils.h>

class KeyBindSingleUIGroup;
enum class ActionIndex;

class KeyBindUIGroup : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class UIElementIndex {

		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		Sprint,
		Reload,
		ToggleInventory,
		ToggleShop,

		Total,

	};

	static const int MAX_COLUMN;
	static const Vector2 FRAME_OFFSET;
	static const Vector2 LIST_POSITION;
	static const std::unordered_map<UIElementIndex, SDL_Keycode> DEFAULT_KEY_MAP;
	static const std::unordered_map<UIElementIndex, std::string> LABEL_MAP;
	static const std::unordered_map<UIElementIndex, ActionIndex> ACTION_INDEX_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<UIElementIndex, KeyBindSingleUIGroup*> uiElementMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void Show();
	void Hide();

public:

	KeyBindUIGroup();
	~KeyBindUIGroup();
	void UpdateConfig();

};