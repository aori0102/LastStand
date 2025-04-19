/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <vector>

#include <GameComponent.h>
#include <Utils.h>

enum class HotBarSlotIndex;
enum class ItemIndex;

class SlotUI {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	friend class InventoryUI;

	bool isHotBar;
	GameObject* frame;
	GameObject* visual;
	ItemIndex itemIndex;
	HotBarSlotIndex hotBarSlotIndex;

};

class InventoryUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	const int MAX_COLUMN = 5;
	const int MAX_ROW = 2;
	const int ITEM_COUNT_FONT_SIZE = 10;
	const int INVENTORY_TITLE_FONT_SIZE = 30;
	const float INVENTORY_TITLE_OFFSET = -8.0f;
	const float INVENTORY_SLOT_OFFSET = 93.0f;
	const float HOTBAR_SLOT_OFFSET = 90.0f;
	const std::string INVENTORY_TITLE = "Inventory";
	const Vector2 FIRST_INVENTORY_SLOT_POSITION = Vector2(416.0f, 285.0f);
	const Vector2 FIRST_HOTBAR_SLOT_POSITION = Vector2(425.0f, 527.0f);

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::vector<std::vector<SlotUI*>> storageGrid;
	std::unordered_map<HotBarSlotIndex, SlotUI*> hotbarSlotMap;
	GameObject* background;
	GameObject* title;
	SlotUI* selectedSlotUI;

	static InventoryUI* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeInventorySlots();
	void InitializeHotBarSlots();
	void InitializeUI();
	void Show();
	void Hide();
	void SwapSlots(SlotUI* first, SlotUI* second);
	void UpdateSlot(SlotUI* slotUI);

public:

	InventoryUI();
	~InventoryUI();
	void SelectSlot(SlotUI* slotUI);
	void AddItemToInventory(ItemIndex itemIndex);
	void RemoveItemFromInventory(ItemIndex itemIndex);
	void UpdateHotBarSlot(HotBarSlotIndex slotIndex, ItemIndex itemIndex);
	void Reset();

	static InventoryUI* Instance();

};