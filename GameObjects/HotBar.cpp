#include <HotBar.h>

#include <HotBarUI.h>
#include <Inventory.h>
#include <InventoryUI.h>
#include <ItemManager.h>

HotBar* HotBar::instance = nullptr;

HotBar::HotBar() {

	if (instance)
		throw std::exception("Hot Bar can only have one instance");

	instance = this;

	for (int i = 0; i < static_cast<int>(HotBarSlotIndex::Total); i++) {

		SlotInfo* slotInfo = new SlotInfo{
			.previousCount = -1,
			.index = ItemIndex::None,
		};

		hotBar[static_cast<HotBarSlotIndex>(i)] = slotInfo;

	}

	currentSlotIndex = HotBarSlotIndex::None;

	hotBarUI = GameObject::Instantiate<HotBarUI>("Hot Bar UI", Layer::GUI);
	hotBarUI->Disable();

}

HotBar::~HotBar() {

	for (auto it = hotBar.begin(); it != hotBar.end(); it++)
		delete it->second;

	hotBar.clear();

	GameObject::Destroy(hotBarUI);
	hotBarUI = nullptr;

	instance = nullptr;

}

void HotBar::SelectSlot(HotBarSlotIndex slotIndex) {

	Item* currentItem = nullptr;
	if (currentSlotIndex != HotBarSlotIndex::None)
		currentItem = Inventory::Instance()->GetItem(hotBar.at(currentSlotIndex)->index);

	if (currentItem)
		currentItem->Dequip();

	if (currentSlotIndex == slotIndex)
		currentSlotIndex = HotBarSlotIndex::None;
	else
		currentSlotIndex = slotIndex;

	if (currentSlotIndex != HotBarSlotIndex::None)
		currentItem = Inventory::Instance()->GetItem(hotBar.at(currentSlotIndex)->index);

	if (currentItem)
		currentItem->Equip();

	HotBarUI::Instance()->SwitchSlot(currentSlotIndex);

}

void HotBar::RemoveItem(ItemIndex itemIndex) {

	for (auto it = hotBar.begin(); it != hotBar.end(); it++) {

		if ((it->second)->index == itemIndex) {

			(it->second)->index = ItemIndex::None;
			(it->second)->previousCount = -1;
			HotBarUI::Instance()->RemoveSlotItem(it->first);
			InventoryUI::Instance()->UpdateHotBarSlot(it->first, ItemIndex::None);
			return;

		}

	}

}

void HotBar::LinkItemToSlot(ItemIndex itemIndex, HotBarSlotIndex slotIndex) {

	if (slotIndex == HotBarSlotIndex::None)
		return;

	auto slot = hotBar.at(slotIndex);

	slot->index = itemIndex;
	slot->previousCount = Inventory::Instance()->GetItemCount(itemIndex);
	HotBarUI::Instance()->UpdateSlotItemVisual(slotIndex, itemIndex);
	HotBarUI::Instance()->UpdateSlotItemCount(slotIndex, slot->previousCount);

}

void HotBar::Update() {

	for (auto it = hotBar.begin(); it != hotBar.end(); it++) {

		if ((it->second)->index == ItemIndex::None)
			continue;

		int currentCount = Inventory::Instance()->GetItemCount((it->second)->index);
		if (currentCount != (it->second)->previousCount) {

			(it->second)->previousCount = currentCount;
			HotBarUI::Instance()->UpdateSlotItemCount(it->first, currentCount);

		}

	}

}

bool HotBar::TryAddItem(ItemIndex itemIndex) {

	for (auto it = hotBar.begin(); it != hotBar.end(); it++) {

		if ((it->second)->index == itemIndex)
			return true;

		if ((it->second)->index == ItemIndex::None) {

			(it->second)->index = itemIndex;
			HotBarUI::Instance()->UpdateSlotItemVisual(it->first, itemIndex);
			InventoryUI::Instance()->UpdateHotBarSlot(it->first, itemIndex);
			return true;

		}

	}

	return false;

}

ItemIndex HotBar::GetSelectedItemIndex() {

	if (currentSlotIndex == HotBarSlotIndex::None)
		return ItemIndex::None;

	return hotBar.at(currentSlotIndex)->index;

}

Item* HotBar::GetSelectedItem() {

	if (currentSlotIndex == HotBarSlotIndex::None)
		return nullptr;

	return Inventory::Instance()->GetItem(hotBar.at(currentSlotIndex)->index);

}

HotBar* HotBar::Instance() { return instance; }