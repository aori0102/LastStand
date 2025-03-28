#include <ItemSelectionUI.h>

#include <Item.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Shop.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int ItemSelectionUI::MAX_COLUMN = 2;
const Vector2 ItemSelectionUI::CELL_SIZE = Vector2(292.0f, 112.0f);

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

SlotNode::SlotNode() {

	nextSlot = nullptr;
	frame = nullptr;
	cell = nullptr;
	visual = nullptr;
	itemIndex = ItemIndex::None;

}

void ItemSelectionUI::UpdateNodeVisual() {

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

ItemSelectionUI::ItemSelectionUI() {

	headNode = nullptr;
	lastNode = nullptr;

}

void ItemSelectionUI::AddItem(ItemIndex newItemIndex) {

	SlotNode* tempNode = headNode;
	while (tempNode) {

		// Firearm already added
		if (tempNode->itemIndex == newItemIndex)
			return;

		tempNode = tempNode->nextSlot;

	}

	SlotNode* newSlot = new SlotNode;

	if (!headNode) {

		headNode = newSlot;
		lastNode = headNode;

	} else {

		lastNode->nextSlot = newSlot;
		lastNode = lastNode->nextSlot;

	}

	lastNode->nextSlot = nullptr;
	lastNode->itemIndex = newItemIndex;

	lastNode->frame = new GameObject("", Layer::Menu);
	Image* frame_image = lastNode->frame->AddComponent<Image>();
	frame_image->showOnScreen = true;
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityItemBar), true);
	Button* frame_button = lastNode->frame->AddComponent<Button>();
	frame_button->backgroundColor = Color::TRANSPARENT;
	frame_button->OnClick = [this, newSlot]() {
		if (!IsActive())
			return false;
		// Shop select item
		Shop::Instance()->SelectItem(newSlot->itemIndex);
		return true;
		};
	lastNode->frame->Render = [this, frame_image]() {
		if (IsActive())
			frame_image->Render();
		};

	lastNode->visual = new GameObject("", Layer::Menu);
	Image* visual_image = lastNode->visual->AddComponent<Image>();
	visual_image->showOnScreen = true;
	ItemManager::Instance()->LinkItemIcon(newItemIndex, visual_image);
	lastNode->visual->transform->position = lastNode->frame->transform->position;
	lastNode->visual->Render = [this, visual_image]() {
		if (IsActive())
			visual_image->Render();
		};

	UpdateNodeVisual();

}

void ItemSelectionUI::RemoveItem(ItemIndex removingItemIndex) {

	SlotNode* tempNode = headNode;
	SlotNode* prevNode = nullptr;
	while (tempNode) {

		if (tempNode->itemIndex == removingItemIndex) {

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

void ItemSelectionUI::SetPosition(Vector2 positionInSDL) {

	position = positionInSDL;

	UpdateNodeVisual();

}