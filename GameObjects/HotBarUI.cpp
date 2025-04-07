/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <HotBarUI.h>

#include <GameComponent.h>
#include <GameCore.h>
#include <Inventory.h>
#include <Item.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Texture.h>
#include <Transform.h>

HotBarUI* HotBarUI::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void HotBarUI::SwitchSlot(HotBarSlotIndex slotIndex) {

	if (slotIndex == HotBarSlotIndex::None) {

		slotSelected = false;
		hotbarSelection->Disable();
		return;

	}

	slotSelected = true;
	hotbarSelection->Enable();

	targetSelectionPosition = hotbarSlotMap.at(slotIndex)->frame->transform->position;

}

void HotBarUI::UpdateSlot(HotBarSlotIndex slotIndex, ItemIndex itemIndex, int amount) {

	if (slotIndex == HotBarSlotIndex::None)
		return;

	if (itemIndex == ItemIndex::None) {

		hotbarSlotMap.at(slotIndex)->visual->Disable();
		hotbarSlotMap.at(slotIndex)->label->Disable();
		return;

	}

	hotbarSlotMap.at(slotIndex)->visual->Enable();

	if (amount != 1) {

		hotbarSlotMap.at(slotIndex)->label->Enable();
		hotbarSlotMap.at(slotIndex)->label->GetComponent<Text>()->LoadText(
			std::to_string(amount), Color::WHITE, LABEL_FONT_SIZE
		);

	} else
		hotbarSlotMap.at(slotIndex)->label->Disable();

	ItemManager::Instance()->LinkItemIcon(itemIndex, hotbarSlotMap.at(slotIndex)->visual->GetComponent<Image>());

}

void HotBarUI::Update() {

	if (!slotSelected)
		return;

	hotbarSelection->transform->position = Vector2::Lerp(
		hotbarSelection->transform->position, targetSelectionPosition, GameCore::DeltaTime() * SELECTION_SWITCH_SPEED
	);

}

HotBarUI::HotBarUI() {

	if (instance)
		throw std::exception("Hot Bar UI can only have one instance!");

	instance = this;

	slotSelected = false;

	Vector2 slotPosition = HOTBAR_POSITION;
	for (int i = static_cast<int>(HotBarSlotIndex::First); i <= static_cast<int>(HotBarSlotIndex::Fifth); i++) {

		SlotUI* hotBarSlot = new SlotUI;

		hotBarSlot->itemIndex = ItemIndex::None;

		hotBarSlot->frame = GameObject::Instantiate("Hot bar slot frame", Layer::GUI);
		Image* hotBarSlotFrame_image = hotBarSlot->frame->AddComponent<Image>();
		hotBarSlotFrame_image->showOnScreen = true;
		hotBarSlotFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::HotBar_Slot), true);
		hotBarSlotFrame_image->transform->position = Math::SDLToC00(slotPosition, hotBarSlotFrame_image->transform->scale);
		hotBarSlot->frame->Render = [this, hotBarSlotFrame_image]() {
			if (IsActive())
				hotBarSlotFrame_image->Render();
			};

		hotBarSlot->visual = GameObject::Instantiate("Hot bar slot visual", Layer::GUI);
		Image* hotBarSlotVisual_image = hotBarSlot->visual->AddComponent<Image>();
		hotBarSlotVisual_image->showOnScreen = true;
		hotBarSlotVisual_image->transform->position = hotBarSlotFrame_image->transform->position;
		hotBarSlot->visual->Render = [this, hotBarSlotVisual_image]() {
			if (IsActive())
				hotBarSlotVisual_image->Render();
			};

		hotBarSlot->label = GameObject::Instantiate("Hot bar slot visual", Layer::GUI);
		Text* hotBarSlotLabel_text = hotBarSlot->label->AddComponent<Text>();
		hotBarSlotLabel_text->showOnScreen = true;
		hotBarSlotLabel_text->LoadText("", Color::WHITE, LABEL_FONT_SIZE);
		Align::Bottom(hotBarSlotLabel_text->transform, hotBarSlot->frame->transform);
		Align::MiddleHorizontally(hotBarSlotLabel_text->transform, hotBarSlot->frame->transform);
		hotBarSlotLabel_text->transform->position.y += LABEL_OFFSET;
		hotBarSlot->label->Render = [this, hotBarSlotLabel_text]() {
			if (IsActive())
				hotBarSlotLabel_text->Render();
			};

		hotbarSlotMap[static_cast<HotBarSlotIndex>(i)] = hotBarSlot;

		slotPosition.y += hotBarSlotFrame_image->transform->scale.y + HOTBAR_SLOT_GAP;

	}

	targetSelectionPosition = Vector2::zero;

	hotbarSelection = GameObject::Instantiate("HotBar selection", Layer::GUI);
	Image* hotbarSelection_image = hotbarSelection->AddComponent<Image>();
	hotbarSelection_image->showOnScreen = true;
	hotbarSelection_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::HotBar_Selection), true);
	hotbarSelection->Render = [this, hotbarSelection_image]() {
		if (IsActive())
			hotbarSelection_image->Render();
		};
	hotbarSelection->Disable();

}

HotBarUI::~HotBarUI() {

	for (auto it = hotbarSlotMap.begin(); it != hotbarSlotMap.end(); it++) {

		GameObject::Destroy((it->second)->frame);
		GameObject::Destroy((it->second)->visual);
		GameObject::Destroy((it->second)->label);

		delete (it->second);
		it->second = nullptr;

	}

	hotbarSlotMap.clear();

	GameObject::Destroy(hotbarSelection);
	hotbarSelection = nullptr;
	
	instance = nullptr;

}

HotBarUI* HotBarUI::Instance() { return instance; }