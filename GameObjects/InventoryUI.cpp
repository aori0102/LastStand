/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <InventoryUI.h>

#include <exception>

#include <HotBar.h>
#include <Inventory.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <Shop.h>
#include <Texture.h>
#include <Transform.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

InventoryUI* InventoryUI::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void InventoryUI::InitializeInventorySlots() {

	storageGrid = std::vector<std::vector<SlotUI*>>(MAX_ROW);
	Vector2 slotPosition = FIRST_INVENTORY_SLOT_POSITION;
	for (int i = 0; i < MAX_ROW; i++) {

		storageGrid[i].resize(MAX_COLUMN, nullptr);

		for (int j = 0; j < MAX_COLUMN; j++) {

			// 
			// slot
			SlotUI* slotUI = new SlotUI;

			slotUI->isHotBar = false;

			GameObject* frame = GameObject::Instantiate("Inventory Slot UI Frame", Layer::Menu);
			Image* frame_image = frame->AddComponent<Image>();
			frame_image->showOnScreen = true;
			frame_image->LinkSprite(
				MediaManager::Instance()->GetUISprite(MediaUI::Inventory_Slot), true
			);
			frame->transform->position = Math::SDLToC00(slotPosition, frame->transform->scale);
			frame->Render = [frame_image]() {
				frame_image->Render();
				};
			Button* frame_button = frame->AddComponent<Button>();
			frame_button->backgroundColor = Color::TRANSPARENT;
			frame_button->OnClick = [this, slotUI]() {
				SelectSlot(slotUI);
				return true;
				};
			slotUI->frame = frame;

			GameObject* visual = GameObject::Instantiate("Inventory Slot UI Visual", Layer::Menu);
			Image* visual_image = visual->AddComponent<Image>();
			visual_image->showOnScreen = true;
			visual->transform->position = frame->transform->position;
			visual->Render = [visual_image]() {
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
		frame->Render = [frame_image]() {
			frame_image->Render();
			};
		Button* frame_button = frame->AddComponent<Button>();
		frame_button->backgroundColor = Color::TRANSPARENT;
		frame_button->OnClick = [this, slotUI]() {
			SelectSlot(slotUI);
			return true;
			};
		slotUI->frame = frame;

		GameObject* visual = GameObject::Instantiate("Inventory UI Hot Bar Slot Visual", Layer::Menu);
		Image* visual_image = visual->AddComponent<Image>();
		visual_image->showOnScreen = true;
		visual->transform->position = frame->transform->position;
		visual->Render = [visual_image]() {
			visual_image->Render();
			};
		visual->Disable();
		slotUI->visual = visual;

		slotUI->itemIndex = ItemIndex::None;
		slotUI->hotBarSlotIndex = slotIndex;

		hotbarSlotMap[slotIndex] = slotUI;

		slotPosition.x += HOTBAR_SLOT_OFFSET;

	}


}

void InventoryUI::InitializeUI() {

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

}

void InventoryUI::Show() {

	for (auto it = hotbarSlotMap.begin(); it != hotbarSlotMap.end(); it++) {

		(it->second)->frame->Enable();
		if ((it->second)->itemIndex != ItemIndex::None)
			(it->second)->visual->Enable();

	}

	for (auto& row : storageGrid) {

		for (auto slot : row) {

			slot->frame->Enable();
			if (slot->itemIndex != ItemIndex::None)
				slot->visual->Enable();

		}

	}

	background->Enable();
	title->Enable();

	Shop::Instance()->Disable();

}

void InventoryUI::Hide() {

	for (auto it = hotbarSlotMap.begin(); it != hotbarSlotMap.end(); it++) {

		(it->second)->frame->Disable();
		(it->second)->visual->Disable();

	}

	for (auto& row : storageGrid) {

		for (auto slot : row) {

			slot->frame->Disable();
			slot->visual->Disable();

		}

	}

	background->Disable();
	title->Disable();

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
		HotBar::Instance()->LinkItemToSlot(slotUI->itemIndex, slotUI->hotBarSlotIndex);

	if (slotUI->itemIndex == ItemIndex::None) {

		slotUI->visual->Disable();
		return;

	}
	if (IsActive())
		slotUI->visual->Enable();

	ItemManager::Instance()->LinkItemIcon(slotUI->itemIndex, slotUI->visual->GetComponent<Image>());

}

InventoryUI::InventoryUI() {

	if (instance)
		throw std::exception("Inventory UI can only have one instance");

	instance = this;
	selectedSlotUI = nullptr;

	InitializeUI();

	OnEnabled = [this]() {
		Show();
		};
	OnDisabled = [this]() {
		Hide();
		};

}

InventoryUI::~InventoryUI() {

	for (std::vector<SlotUI*> storageRow : storageGrid) {

		for (auto slot : storageRow) {

			GameObject::Destroy(slot->frame);
			GameObject::Destroy(slot->visual);

			delete slot;

		};

		storageRow.clear();

	}

	storageGrid.clear();

	for (auto it = hotbarSlotMap.begin(); it != hotbarSlotMap.end(); it++) {

		GameObject::Destroy((it->second)->frame);
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

void InventoryUI::AddItemToInventory(ItemIndex itemIndex) {

	if (itemIndex == ItemIndex::None)
		return;

	SlotUI* firstEmptySlot = nullptr;

	for (int i = 0; i < MAX_ROW; i++) {

		for (int j = 0; j < MAX_COLUMN; j++) {

			if (!firstEmptySlot && storageGrid[i][j]->itemIndex == ItemIndex::None)
				firstEmptySlot = storageGrid[i][j];
			else if (itemIndex == storageGrid[i][j]->itemIndex)
				return;

		}

	}

	if (firstEmptySlot) {
		firstEmptySlot->itemIndex = itemIndex;
		UpdateSlot(firstEmptySlot);
	} else
		throw std::exception("No available grid to store item while adding or inventory content does not match when removing");

}

void InventoryUI::RemoveItemFromInventory(ItemIndex itemIndex) {

	for (int i = 0; i < MAX_ROW; i++) {

		for (int j = 0; j < MAX_COLUMN; j++) {

			if (storageGrid[i][j]->itemIndex == itemIndex) {

				storageGrid[i][j]->itemIndex = ItemIndex::None;
				UpdateSlot(storageGrid[i][j]);
				return;

			}

		}

	}

}

void InventoryUI::UpdateHotBarSlot(HotBarSlotIndex slotIndex, ItemIndex itemIndex) {

	if (slotIndex == HotBarSlotIndex::None)
		return;

	hotbarSlotMap.at(slotIndex)->itemIndex = itemIndex;
	UpdateSlot(hotbarSlotMap.at(slotIndex));

}

void InventoryUI::Reset() {

	for (int i = 0; i < MAX_ROW; i++) {

		for (int j = 0; j < MAX_COLUMN; j++) {

			storageGrid[i][j]->itemIndex = ItemIndex::None;
			UpdateSlot(storageGrid[i][j]);

		}

	}

	for (int i = 0; i < static_cast<int>(HotBarSlotIndex::Total); i++) {

		auto slot = hotbarSlotMap.at(static_cast<HotBarSlotIndex>(i));
		slot->itemIndex = ItemIndex::None;
		UpdateSlot(slot);

	}

}

InventoryUI* InventoryUI::Instance() { return instance; }