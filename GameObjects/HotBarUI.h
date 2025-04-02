/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameComponent.h>
#include <Utils.h>

enum class HotBarSlotIndex;
enum class ItemIndex;

class HotBarUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

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

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool slotSelected;
	std::unordered_map<HotBarSlotIndex, SlotUI*> hotbarSlotMap;
	Vector2 targetSelectionPosition;
	GameObject* hotbarSelection;

	friend class Inventory;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	HotBarUI();
	void SwitchSlot(HotBarSlotIndex slotIndex);
	void UpdateSlot(HotBarSlotIndex slotIndex, ItemIndex itemIndex, int amount = 1);
	void Update() override;
	void OnDestroy() override;

};