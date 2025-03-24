#include <FirearmSelectionUI.h>

#include <Firearm.h>
#include <MediaManager.h>
#include <Shop.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int FirearmSelectionUI::MAX_COLUMN = 3;
const Vector2 FirearmSelectionUI::CELL_SIZE = Vector2(340.0f, 195.0f);

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void FirearmSelectionUI::UpdateNodeVisual() {

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

FirearmSelectionUI::FirearmSelectionUI() {

	headNode = nullptr;
	lastNode = nullptr;

}

void FirearmSelectionUI::AddFirearm(Firearm* newFirearm) {

	SlotNode* tempNode = headNode;
	while (tempNode) {

		// Firearm already added
		if (tempNode->firearm == newFirearm)
			return;

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

	lastNode->frame = new GameObject("", Layer::Menu);
	Image* frame_image = lastNode->frame->AddComponent<Image>();
	frame_image->showOnScreen = true;
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_GunSelectionSlot), true);
	Button* frame_button = lastNode->frame->AddComponent<Button>();
	frame_button->backgroundColor = Color::TRANSPARENT;
	frame_button->OnClick = [this, newFirearm]() {
		if (IsActive())
			Shop::Instance()->SelectFirearm(newFirearm);

		};
	frame_button->OnMouseEnter = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_GunSelectionSlotHovered), true);
		};
	frame_button->OnMouseLeave = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_GunSelectionSlot), true);
		};
	lastNode->frame->Render = [this, frame_image]() {
		if (IsActive())
			frame_image->Render();
		};

	lastNode->visual = new GameObject("", Layer::Menu);
	Image* visual_image = lastNode->visual->AddComponent<Image>();
	visual_image->showOnScreen = true;
	visual_image->LinkSprite(newFirearm->GetIconSprite(),true);
	lastNode->visual->transform->position = lastNode->frame->transform->position;
	lastNode->visual->Render = [this, visual_image]() {
		if (IsActive())
			visual_image->Render();
		};

	UpdateNodeVisual();

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

			delete tempNode;

			UpdateNodeVisual();

			return;

		}

		prevNode = tempNode;
		tempNode = tempNode->nextSlot;

	}

}

void FirearmSelectionUI::SetPosition(Vector2 positionInSDL) {

	position = positionInSDL;

	UpdateNodeVisual();

}