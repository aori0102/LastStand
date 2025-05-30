﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <FirearmSelectionUI.h>

#include <AudioManager.h>
#include <Firearm.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Shop.h>
#include <Texture.h>
#include <Transform.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int FirearmSelectionUI::MAX_COLUMN = 3;
const Vector2 FirearmSelectionUI::CELL_SIZE = Vector2(320.0f, 195.0f);

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void FirearmSelectionUI::UpdateListPosition() {

	int row = 0, col = 0;

	SlotNode* tempNode = headNode;
	while (tempNode) {

		tempNode->frame->transform->position = Math::SDLToC00(
			position + Vector2(col * CELL_SIZE.x, row * CELL_SIZE.y),
			CELL_SIZE
		);
		tempNode->visual->transform->position = tempNode->frame->transform->position;

		col++;
		if (col == MAX_COLUMN) {

			col = 0;
			row++;

		}

		tempNode = tempNode->nextSlot;

	}

}

void FirearmSelectionUI::Show() {

	auto node = headNode;
	while (node) {

		node->frame->Enable();
		node->visual->Enable();

		node = node->nextSlot;

	}

}

void FirearmSelectionUI::Hide() {

	auto node = headNode;
	while (node) {

		node->frame->Disable();
		node->visual->Disable();

		node = node->nextSlot;

	}

}

FirearmSelectionUI::FirearmSelectionUI() {

	headNode = nullptr;
	lastNode = nullptr;

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

FirearmSelectionUI::~FirearmSelectionUI() {

	ClearSelection();

}

void FirearmSelectionUI::RemoveFirearm(Firearm* removingFirearm) {

	SlotNode* tempNode = headNode;
	SlotNode* prevNode = nullptr;
	while (tempNode) {

		if (tempNode->firearm == removingFirearm) {

			if (!prevNode)
				headNode = tempNode->nextSlot;
			else
				prevNode->nextSlot = tempNode->nextSlot;

			GameObject::Destroy(tempNode->frame);
			GameObject::Destroy(tempNode->visual);
			delete tempNode;

			UpdateListPosition();

			return;

		}

		prevNode = tempNode;
		tempNode = tempNode->nextSlot;

	}

}

void FirearmSelectionUI::SetPosition(Vector2 positionInSDL) {

	position = positionInSDL;

	UpdateListPosition();

}

void FirearmSelectionUI::ClearSelection() {

	auto node = headNode;
	while (node) {

		GameObject::Destroy(node->frame);
		GameObject::Destroy(node->visual);
		auto nextSlot = node->nextSlot;
		delete node;
		node = nextSlot;

	}

	headNode = nullptr;
	lastNode = nullptr;

}

bool FirearmSelectionUI::TryAddFirearm(Firearm* newFirearm) {

	SlotNode* tempNode = headNode;
	while (tempNode) {

		// Firearm already added
		if (tempNode->firearm == newFirearm)
			return false;

		tempNode = tempNode->nextSlot;

	}

	if (!headNode) {

		headNode = new SlotNode;
		lastNode = headNode;

	} else {

		lastNode->nextSlot = new SlotNode;
		lastNode = lastNode->nextSlot;

	}

	lastNode->nextSlot = nullptr;
	lastNode->firearm = newFirearm;

	lastNode->frame = GameObject::Instantiate("Firearm Selection UI Frame", Layer::Menu);
	Image* frame_image = lastNode->frame->AddComponent<Image>();
	frame_image->showOnScreen = true;
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmSelectionSlot), true);
	Button* frame_button = lastNode->frame->AddComponent<Button>();
	frame_button->backgroundColor = Color::TRANSPARENT;
	frame_button->OnClick = [newFirearm]() {
		Shop::Instance()->SelectFirearm(newFirearm);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		return true;
		};
	frame_button->OnMouseEnter = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmSelectionSlotHovered), true);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		};
	frame_button->OnMouseLeave = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmSelectionSlot), true);
		};
	lastNode->frame->Render = [frame_image]() {
		frame_image->Render();
		};

	lastNode->visual = GameObject::Instantiate("Selection Node Visual", Layer::Menu);
	Image* visual_image = lastNode->visual->AddComponent<Image>();
	ItemManager::Instance()->LinkItemIcon(newFirearm->GetIndex(), visual_image);
	visual_image->showOnScreen = true;
	lastNode->visual->transform->position = lastNode->frame->transform->position;
	lastNode->visual->Render = [visual_image]() {
		visual_image->Render();
		};

	if (!IsActive()) {

		lastNode->frame->Disable();
		lastNode->visual->Disable();

	}

	UpdateListPosition();

	return true;

}