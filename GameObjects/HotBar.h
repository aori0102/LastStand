#pragma once

#include <unordered_map>

#include <GameObject.h>

class HotBarUI;
class Item;
enum class ItemIndex;

enum class HotBarSlotIndex {

	First,
	Second,
	Third,
	Forth,
	Fifth,

	Total,
	None,

};

class HotBar : public GameObject {

private:

	struct SlotInfo {
		int previousCount;
		ItemIndex index;
	};

private:

	std::unordered_map<HotBarSlotIndex, SlotInfo*> hotBar;
	HotBarSlotIndex currentSlotIndex;
	HotBarUI* hotBarUI;

	static HotBar* instance;

public:

	HotBar();
	~HotBar();
	void SelectSlot(HotBarSlotIndex slotIndex);
	void RemoveItem(ItemIndex itemIndex);
	void LinkItemToSlot(ItemIndex itemIndex, HotBarSlotIndex slotIndex);
	void Update() override;
	bool TryAddItem(ItemIndex itemIndex);
	ItemIndex GetSelectedItemIndex();
	Item* GetSelectedItem();

	static HotBar* Instance();

};