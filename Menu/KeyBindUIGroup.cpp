/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <KeyBindUIGroup.h>

#include <GameCore.h>
#include <KeyBindSingleUIGroup.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int KeyBindUIGroup::MAX_COLUMN = 2;
const Vector2 KeyBindUIGroup::FRAME_OFFSET = Vector2(250.0f, 68.0f);
const Vector2 KeyBindUIGroup::LIST_POSITION = Vector2(501.0f, 328.0f);
const std::unordered_map<KeyBindUIGroup::UIElementIndex, SDL_Keycode> KeyBindUIGroup::DEFAULT_KEY_MAP = {
	{ KeyBindUIGroup::UIElementIndex::MoveUp, SDLK_w },
	{ KeyBindUIGroup::UIElementIndex::MoveDown, SDLK_s },
	{ KeyBindUIGroup::UIElementIndex::MoveLeft, SDLK_a },
	{ KeyBindUIGroup::UIElementIndex::MoveRight, SDLK_d },
	{ KeyBindUIGroup::UIElementIndex::Sprint, SDLK_LSHIFT },
	{ KeyBindUIGroup::UIElementIndex::Reload, SDLK_r },
	{ KeyBindUIGroup::UIElementIndex::ToggleInventory, SDLK_i },
	{ KeyBindUIGroup::UIElementIndex::ToggleShop, SDLK_TAB },
};

const std::unordered_map<KeyBindUIGroup::UIElementIndex, std::string> KeyBindUIGroup::LABEL_MAP = {
	{ KeyBindUIGroup::UIElementIndex::MoveUp, "Move Up" },
	{ KeyBindUIGroup::UIElementIndex::MoveDown, "Move Down" },
	{ KeyBindUIGroup::UIElementIndex::MoveLeft, "Move Left" },
	{ KeyBindUIGroup::UIElementIndex::MoveRight, "Move Right" },
	{ KeyBindUIGroup::UIElementIndex::Sprint, "Sprint" },
	{ KeyBindUIGroup::UIElementIndex::Reload, "Reload" },
	{ KeyBindUIGroup::UIElementIndex::ToggleInventory, "Toggle Inventory" },
	{ KeyBindUIGroup::UIElementIndex::ToggleShop, "Toggle Shop" },
};
const std::unordered_map<KeyBindUIGroup::UIElementIndex, ActionIndex> KeyBindUIGroup::ACTION_INDEX_MAP = {
	{ KeyBindUIGroup::UIElementIndex::MoveUp, ActionIndex::MoveUp },
	{ KeyBindUIGroup::UIElementIndex::MoveDown, ActionIndex::MoveDown },
	{ KeyBindUIGroup::UIElementIndex::MoveLeft, ActionIndex::MoveLeft },
	{ KeyBindUIGroup::UIElementIndex::MoveRight, ActionIndex::MoveRight },
	{ KeyBindUIGroup::UIElementIndex::Sprint, ActionIndex::Sprint },
	{ KeyBindUIGroup::UIElementIndex::Reload, ActionIndex::Reload },
	{ KeyBindUIGroup::UIElementIndex::ToggleInventory, ActionIndex::ToggleInventory },
	{ KeyBindUIGroup::UIElementIndex::ToggleShop, ActionIndex::ToggleShop },
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void KeyBindUIGroup::Show() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

}

void KeyBindUIGroup::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

KeyBindUIGroup::KeyBindUIGroup() {

	int col = 0;
	Vector2 position = LIST_POSITION;
	for (int i = 0; i < static_cast<int>(UIElementIndex::Total); i++) {

		KeyBindSingleUIGroup* singleKeyGroup = GameObject::Instantiate<KeyBindSingleUIGroup>(
			"Key Bind Single UI Group", Layer::Menu
		);
		singleKeyGroup->SetLabel(LABEL_MAP.at(static_cast<UIElementIndex>(i)));
		singleKeyGroup->SetPosition(position);
		uiElementMap[static_cast<UIElementIndex>(i)] = singleKeyGroup;

		col++;
		if (col == MAX_COLUMN) {

			col = 0;
			position.y += FRAME_OFFSET.y;
			position.x = LIST_POSITION.x;

		} else
			position.x += FRAME_OFFSET.x;

	}

	// Activate, deactivate
	OnEnabled = [this]() { Show();  };
	OnDisabled = [this]() { Hide(); };

}

KeyBindUIGroup::~KeyBindUIGroup() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	uiElementMap.clear();

}

void KeyBindUIGroup::UpdateConfig() {

	for (int i = 0; i < static_cast<int>(UIElementIndex::Total); i++) {

		UIElementIndex index = static_cast<UIElementIndex>(i);
		uiElementMap.at(index)->As<KeyBindSingleUIGroup>()->BindAction(ACTION_INDEX_MAP.at(index));

	}

}