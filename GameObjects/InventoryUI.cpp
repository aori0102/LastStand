#include <InventoryUI.h>

#include <exception>

#include <Inventory.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <Texture.h>
#include <Transform.h>

InventoryUI* InventoryUI::instance = nullptr;

void InventoryUI::InitializeInventorySlots() {

	storageGrid = std::vector<std::vector<SlotUI*>>(MAX_ROW);
	Vector2 slotPosition = FIRST_INVENTORY_SLOT_POSITION;
	for (int i = 0; i < MAX_ROW; i++) {

		storageGrid[i].resize(MAX_COLUMN, nullptr);

		for (int j = 0; j < MAX_COLUMN; j++) {

			// Instantiate slot
			SlotUI* slotUI = new SlotUI;

			slotUI->isHotBar = false;

			GameObject* frame = GameObject::Instantiate("Inventory Slot UI Frame", Layer::Menu);
			Image* frame_image = frame->AddComponent<Image>();
			frame_image->showOnScreen = true;
			frame_image->LinkSprite(
				MediaManager::Instance()->GetUISprite(MediaUI::Inventory_Slot), true
			);
			frame->transform->position = Math::SDLToC00(slotPosition, frame->transform->scale);
			frame->Render = [this, frame_image]() {
				if (IsActive())
					frame_image->Render();
				};
			Button* frame_button = frame->AddComponent<Button>();
			frame_button->backgroundColor = Color::TRANSPARENT;
			frame_button->OnClick = [this, slotUI]() {
				if (!IsActive())
					return false;
				SelectSlot(slotUI);
				return true;
				};
			slotUI->frame = frame;

			GameObject* itemCountLabel = GameObject::Instantiate("Inventory Slot UI Item Count Label", Layer::Menu);
			Text* itemCountLabel_text = itemCountLabel->AddComponent<Text>();
			itemCountLabel_text->showOnScreen = true;
			itemCountLabel_text->LoadText("", Color::WHITE, ITEM_COUNT_FONT_SIZE);
			Align::Right(itemCountLabel->transform, frame->transform);
			Align::Bottom(itemCountLabel->transform, frame->transform);
			itemCountLabel->Render = [this, itemCountLabel_text]() {
				if (IsActive())
					itemCountLabel_text->Render();
				};
			slotUI->itemCountLabel = itemCountLabel;

			GameObject* visual = GameObject::Instantiate("Inventory Slot UI Visual", Layer::Menu);
			Image* visual_image = visual->AddComponent<Image>();
			visual_image->showOnScreen = true;
			visual->transform->position = frame->transform->position;
			visual->Render = [this, visual_image]() {
				if (IsActive())
					visual_image->Render();
				};
			visual->Disable();
			slotUI->visual = visual;

			slotUI->itemIndex = ItemIndex::None;
			slotUI->hotBarSlotIndex = HotBarSlotIndex::None;

			// Add to grid
			storageGrid[i][j] = slotUI;

			// Increment position
			slotPosition.x += INVENTORY_SLOT_OFFSET;

		}

		slotPosition.x = FIRST_INVENTORY_SLOT_POSITION.x;
		slotPosition.y += INVENTORY_SLOT_OFFSET;

	}

}

void InventoryUI::InitializeHotBarSlots() {

	Vector2 slotPosition = FIRST_HOTBAR_SLOT_POSITION;
	for (int i = static_cast<int>(HotBarSlotIndex::First); i <= static_cast<int>(HotBarSlotIndex::Fifth); i++) {

		HotBarSlotIndex slotIndex = static_cast<HotBarSlotIndex>(i);

		SlotUI* slotUI = new SlotUI;

		slotUI->isHotBar = true;

		GameObject* frame = GameObject::Instantiate("Inventory UI Hot Bar Slot Frame", Layer::Menu);
		Image* frame_image = frame->AddComponent<Image>();
		frame_image->showOnScreen = true;
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Inventory_HotBarSlot), true);
		frame->transform->position = Math::SDLToC00(slotPosition, frame->transform->scale);
		frame->Render = [this, frame_image]() {
			if (IsActive())
				frame_image->Render();
			};
		Button* frame_button = frame->AddComponent<Button>();
		frame_button->backgroundColor = Color::TRANSPARENT;
		frame_button->OnClick = [this, slotUI]() {
			if (!IsActive())
				return false;
			SelectSlot(slotUI);
			return true;
			};
		slotUI->frame = frame;

		GameObject* visual = GameObject::Instantiate("Inventory UI Hot Bar Slot Visual", Layer::Menu);
		Image* visual_image = visual->AddComponent<Image>();
		visual_image->showOnScreen = true;
		visual->transform->position = frame->transform->position;
		visual->Render = [this, visual_image]() {
			if (IsActive())
				visual_image->Render();
			};
		visual->Disable();
		slotUI->visual = visual;

		GameObject* itemCountLabel = GameObject::Instantiate("Inventory UI Hot Bar Item Count Label", Layer::Menu);
		Text* itemCountLabel_text = itemCountLabel->AddComponent<Text>();
		itemCountLabel_text->showOnScreen = true;
		itemCountLabel_text->LoadText("", Color::WHITE, ITEM_COUNT_FONT_SIZE);
		Align::Left(itemCountLabel->transform, frame->transform);
		Align::Bottom(itemCountLabel->transform, frame->transform);
		itemCountLabel->Render = [this, itemCountLabel_text]() {
			if (IsActive())
				itemCountLabel_text->Render();
			};
		slotUI->itemCountLabel = itemCountLabel;

		slotUI->itemIndex = ItemIndex::None;
		slotUI->hotBarSlotIndex = slotIndex;

		hotbarSlotMap[slotIndex] = slotUI;

		slotPosition.x += HOTBAR_SLOT_OFFSET;

	}


}

void InventoryUI::SwapSlots(SlotUI* first, SlotUI* second) {

	if (!first || !second)
		throw std::exception("Cannot swap null inventory slot UI");

	first->frame->GetComponent<Image>()->LinkSprite(
		MediaManager::Instance()->GetUISprite(first->isHotBar ? MediaUI::Inventory_HotBarSlot : MediaUI::Inventory_Slot), true
	);
	second->frame->GetComponent<Image>()->LinkSprite(
		MediaManager::Instance()->GetUISprite(second->isHotBar ? MediaUI::Inventory_HotBarSlot : MediaUI::Inventory_Slot), true
	);

	std::swap(first->itemIndex, second->itemIndex);

	UpdateSlot(first);
	UpdateSlot(second);

}

void InventoryUI::UpdateSlot(SlotUI* slotUI) {

	if (!slotUI)
		return;

	if (slotUI->isHotBar)
		Player::Instance()->GetComponent<Inventory>()->LinkItemToHotBar(slotUI->hotBarSlotIndex, slotUI->itemIndex);

	if (slotUI->itemIndex == ItemIndex::None) {

		slotUI->visual->Disable();
		return;

	}
	slotUI->visual->Enable();
	ItemManager::Instance()->LinkItemIcon(slotUI->itemIndex, slotUI->visual->GetComponent<Image>());

}

InventoryUI::InventoryUI() {

	if (instance)
		throw std::exception("Inventory UI can only have one instance");

	instance = this;

	background = GameObject::Instantiate("Inventory UI Background", Layer::Menu);
	Image* background_image = background->AddComponent<Image>();
	background_image->showOnScreen = true;
	background_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Inventory_Background), true);
	background->transform->position = Vector2::zero;
	background->Render = [this, background_image]() {
		if (IsActive())
			background_image->Render();
		};

	title = GameObject::Instantiate("Inventory UI Title", Layer::Menu);
	Text* title_text = title->AddComponent<Text>();
	title_text->showOnScreen = true;
	title_text->LoadText(INVENTORY_TITLE, Color::WHITE, INVENTORY_TITLE_FONT_SIZE);
	Align::MiddleHorizontally(title->transform, background->transform);
	Align::Top(title->transform, background->transform);
	title->transform->position.y += INVENTORY_TITLE_OFFSET;
	title->Render = [this, title_text]() {
		if (IsActive())
			title_text->Render();
		};

	InitializeInventorySlots();

	InitializeHotBarSlots();

	selectedSlotUI = nullptr;

}

InventoryUI::~InventoryUI() {

	for (std::vector<SlotUI*> storageRow : storageGrid) {

		for (auto slot : storageRow) {

			GameObject::Destroy(slot->frame);
			GameObject::Destroy(slot->visual);
			GameObject::Destroy(slot->itemCountLabel);

			delete slot;

		};

		storageRow.clear();

	}

	storageGrid.clear();

	for (auto it = hotbarSlotMap.begin(); it != hotbarSlotMap.end(); it++) {

		GameObject::Destroy((it->second)->frame);
		GameObject::Destroy((it->second)->itemCountLabel);
		GameObject::Destroy((it->second)->visual);

		delete it->second;

	}

	hotbarSlotMap.clear();

	GameObject::Destroy(background);
	background = nullptr;

	GameObject::Destroy(title);
	title = nullptr;

	selectedSlotUI = nullptr;

	instance = nullptr;

}

void InventoryUI::SelectSlot(SlotUI* slotUI) {

	if (!slotUI)
		return;

	if (selectedSlotUI) {

		SwapSlots(selectedSlotUI, slotUI);
		selectedSlotUI = nullptr;
		return;

	}

	selectedSlotUI = slotUI;
	selectedSlotUI->frame->GetComponent<Image>()->LinkSprite(
		MediaManager::Instance()->GetUISprite(selectedSlotUI->isHotBar ? MediaUI::Inventory_HotBarSlot_Selected : MediaUI::Inventory_Slot_Selected), true
	);

}

void InventoryUI::UpdateInventorySlot(ItemIndex itemIndex, int amount) {

	if (itemIndex == ItemIndex::None)
		return;

	SlotUI* firstEmptySlot = nullptr;

	for (int i = 0; i < MAX_ROW; i++) {

		for (int j = 0; j < MAX_COLUMN; j++) {

			if (!firstEmptySlot && storageGrid[i][j]->itemIndex == ItemIndex::None)
				firstEmptySlot = storageGrid[i][j];
			else if (itemIndex == storageGrid[i][j]->itemIndex) {

				if (amount == 0)
					storageGrid[i][j]->itemIndex = ItemIndex::None;
				else
					storageGrid[i][j]->itemIndex = itemIndex;
				UpdateSlot(storageGrid[i][j]);
				return;

			}

		}

	}

	if (firstEmptySlot && amount > 0) {
		firstEmptySlot->itemIndex = itemIndex;
		UpdateSlot(firstEmptySlot);
	} else
		throw std::exception("No available grid to store item while adding or inventory content does not match when removing");

}

void InventoryUI::UpdateHotBarSlot(ItemIndex itemIndex, int amount, HotBarSlotIndex hotBarSlotIndex) {

	if (hotBarSlotIndex == HotBarSlotIndex::None)
		return;
	
	if (amount > 0)
		hotbarSlotMap.at(hotBarSlotIndex)->itemIndex = itemIndex;
	else
		hotbarSlotMap.at(hotBarSlotIndex)->itemIndex = ItemIndex::None;

	UpdateSlot(hotbarSlotMap.at(hotBarSlotIndex));

}

InventoryUI* InventoryUI::Instance() { return instance; }