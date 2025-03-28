#include <HotBarUI.h>

#include <GameComponent.h>
#include <GameCore.h>
#include <Item.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Texture.h>

HotBarUI::HotBarUI() {

	Vector2 slotPosition = HOTBAR_POSITION;

	for (int i = static_cast<int>(InventorySlotIndex::First); i <= static_cast<int>(InventorySlotIndex::Fifth); i++) {

		SlotUI* hotBarSlot = new SlotUI;

		hotBarSlot->itemIndex = ItemIndex::None;

		hotBarSlot->frame = new GameObject("Hot bar slot frame", Layer::GUI);
		Image* hotBarSlotFrame_image = hotBarSlot->frame->AddComponent<Image>();
		hotBarSlotFrame_image->showOnScreen = true;
		hotBarSlotFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::HotBar_Slot), true);
		hotBarSlotFrame_image->transform->position = Math::SDLToC00(slotPosition,hotBarSlotFrame_image->transform->scale);
		hotBarSlot->frame->Render = [hotBarSlotFrame_image]() {
			hotBarSlotFrame_image->Render();
			};

		hotBarSlot->visual = new GameObject("Hot bar slot visual", Layer::GUI);
		Image* hotBarSlotVisual_image = hotBarSlot->visual->AddComponent<Image>();
		hotBarSlotVisual_image->showOnScreen = true;
		hotBarSlotVisual_image->transform->position = hotBarSlotFrame_image->transform->position;
		hotBarSlot->visual->Render = [hotBarSlotVisual_image]() {
			hotBarSlotVisual_image->Render();
			};

		hotBarSlot->label = new GameObject("Hot bar slot visual", Layer::GUI);
		Text* hotBarSlotLabel_text = hotBarSlot->label->AddComponent<Text>();
		hotBarSlotLabel_text->showOnScreen = true;
		hotBarSlotLabel_text->LoadText("", Color::WHITE, LABEL_FONT_SIZE);
		Align::Bottom(hotBarSlotLabel_text->transform, hotBarSlot->frame->transform);
		Align::MiddleHorizontally(hotBarSlotLabel_text->transform, hotBarSlot->frame->transform);
		hotBarSlotLabel_text->transform->position.y += LABEL_OFFSET;
		hotBarSlot->label->Render = [hotBarSlotLabel_text]() {
			hotBarSlotLabel_text->Render();
			};

		hotbarSlotMap[static_cast<InventorySlotIndex>(i)] = hotBarSlot;

		slotPosition.y += hotBarSlotFrame_image->transform->scale.y + HOTBAR_SLOT_GAP;

	}

	hotbarSelection = new GameObject("HotBar selection", Layer::GUI);
	Image* hotbarSelection_image = hotbarSelection->AddComponent<Image>();
	hotbarSelection_image->showOnScreen = true;
	hotbarSelection_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::HotBar_Selection), true);
	hotbarSelection->Render = [hotbarSelection_image]() {
		hotbarSelection_image->Render();
		};
	hotbarSelection->Disable();

	slotSelected = false;
	targetSelectionPosition = Vector2::zero;

}

void HotBarUI::Update() {

	if (!slotSelected)
		return;

	hotbarSelection->transform->position = Vector2::Lerp(
		hotbarSelection->transform->position, targetSelectionPosition, GameCore::DeltaTime() * SELECTION_SWITCH_SPEED
	);

}

void HotBarUI::SwitchSlot(InventorySlotIndex slotIndex) {

	if (slotIndex == InventorySlotIndex::None) {

		slotSelected = false;
		hotbarSelection->Disable();
		return;

	}

	slotSelected = true;
	hotbarSelection->Enable();

	targetSelectionPosition = hotbarSlotMap.at(slotIndex)->frame->transform->position;

}

void HotBarUI::UpdateSlot(InventorySlotIndex slotIndex, ItemIndex itemIndex, int amount) {

	if (slotIndex == InventorySlotIndex::None)
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