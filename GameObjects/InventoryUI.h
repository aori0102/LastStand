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

	static const int MAX_COLUMN;
	static const int MAX_ROW;
	static const int ITEM_COUNT_FONT_SIZE;
	static const int INVENTORY_TITLE_FONT_SIZE;
	static const float INVENTORY_TITLE_OFFSET;
	static const float INVENTORY_SLOT_OFFSET;
	static const float HOTBAR_SLOT_OFFSET;
	static const std::string INVENTORY_TITLE;
	static const Vector2 FIRST_INVENTORY_SLOT_POSITION;
	static const Vector2 FIRST_HOTBAR_SLOT_POSITION;

	std::vector<std::vector<SlotUI*>> storageGrid;
	std::unordered_map<HotBarSlotIndex, SlotUI*> hotbarSlotMap;
	GameObject* background;
	GameObject* title;
	SlotUI* selectedSlotUI;

private:

	void InitializeInventorySlots();
	void InitializeHotBarSlots();
	void SwapSlots(SlotUI* first, SlotUI* second);
	void UpdateSlot(SlotUI* slotUI);

public:

	InventoryUI();
	void SelectSlot(SlotUI* slotUI);
	void UpdateInventorySlot(ItemIndex itemIndex, int amount);
	void UpdateHotBarSlot(ItemIndex itemIndex, int amount, HotBarSlotIndex hotBarSlotIndex);

};