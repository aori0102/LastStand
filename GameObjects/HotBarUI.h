#pragma once

#include <unordered_map>

#include <GameComponent.h>
#include <Type.h>

enum class InventorySlotIndex;
enum class ItemIndex;

class HotBarUI : public GameObject {

private:

	struct SlotUI {
		GameObject* frame;
		GameObject* visual;
		GameObject* label;
		ItemIndex itemIndex;
	};

	const Vector2 HOTBAR_POSITION = Vector2(1173.0f, 113.0f);
	const float HOTBAR_SLOT_GAP = 11.0f;
	const float SELECTION_SWITCH_SPEED = 14.0f;
	const float LABEL_OFFSET = 8.0f;
	const int LABEL_FONT_SIZE = 12;

	bool slotSelected;
	Vector2 targetSelectionPosition;
	GameObject* hotbarSelection;
	std::unordered_map<InventorySlotIndex, SlotUI*> hotbarSlotMap;

	HotBarUI();

	void Update() override;
	void SwitchSlot(InventorySlotIndex slotIndex);
	void UpdateSlot(InventorySlotIndex slotIndex, ItemIndex itemIndex, int amount = 1);

	friend class Inventory;

};