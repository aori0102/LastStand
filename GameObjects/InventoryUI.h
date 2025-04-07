#pragma once

#include <vector>

#include <GameComponent.h>
#include <Utils.h>

enum class HotBarSlotIndex;
enum class ItemIndex;

class SlotUI {

private:

	friend class InventoryUI;

	bool isHotBar;
	GameObject* frame;
	GameObject* itemCountLabel;
	GameObject* visual;
	ItemIndex itemIndex;
	HotBarSlotIndex hotBarSlotIndex;

};

class InventoryUI : public GameObject {

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

private:

	std::vector<std::vector<SlotUI*>> storageGrid;
	std::unordered_map<HotBarSlotIndex, SlotUI*> hotbarSlotMap;
	GameObject* background;
	GameObject* title;
	SlotUI* selectedSlotUI;

	static InventoryUI* instance;

private:

	void InitializeInventorySlots();
	void InitializeHotBarSlots();
	void SwapSlots(SlotUI* first, SlotUI* second);
	void UpdateSlot(SlotUI* slotUI);

public:

	InventoryUI();
	~InventoryUI();
	void SelectSlot(SlotUI* slotUI);
	void UpdateInventorySlot(ItemIndex itemIndex, int amount);
	void UpdateHotBarSlot(ItemIndex itemIndex, int amount, HotBarSlotIndex hotBarSlotIndex);

	static InventoryUI* Instance();

};