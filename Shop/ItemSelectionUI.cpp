/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <ItemSelectionUI.h>

#include <AudioManager.h>
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
	visual = nullptr;
	itemIndex = ItemIndex::None;

}

void ItemSelectionUI::UpdateListPositioning() {

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

void ItemSelectionUI::Show() {

	auto node = headNode;
	while (node) {

		node->frame->Enable();
		node->visual->Enable();

		node = node->nextSlot;

	}

}

void ItemSelectionUI::Hide() {

	auto node = headNode;
	while (node) {

		node->frame->Disable();
		node->visual->Disable();

		node = node->nextSlot;

	}

}

ItemSelectionUI::ItemSelectionUI() {

	headNode = nullptr;
	lastNode = nullptr;

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

ItemSelectionUI::~ItemSelectionUI() {

	auto node = headNode;
	while (node) {

		GameObject::Destroy(node->frame);
		GameObject::Destroy(node->visual);

		auto next = node->nextSlot;

		delete node;
		node = next;

	}

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

	// Add new slot
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

	// Update UI
	lastNode->frame = GameObject::Instantiate("Item Selection UI Frame", Layer::Menu);
	Image* frame_image = lastNode->frame->AddComponent<Image>();
	frame_image->showOnScreen = true;
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityItemBar), true);
	Button* frame_button = lastNode->frame->AddComponent<Button>();
	frame_button->backgroundColor = Color::TRANSPARENT;
	frame_button->OnClick = [newItemIndex]() {
		Shop::Instance()->SelectItem(newItemIndex);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		return true;
		};
	frame_button->OnMouseEnter = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityItemBar_Selected),true);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		};
	frame_button->OnMouseLeave = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityItemBar), true);
		};
	lastNode->frame->Render = [frame_image]() {
		frame_image->Render();
		};

	lastNode->visual = GameObject::Instantiate("Item Selection UI Visual", Layer::Menu);
	Image* visual_image = lastNode->visual->AddComponent<Image>();
	visual_image->showOnScreen = true;
	ItemManager::Instance()->LinkItemIcon(newItemIndex, visual_image);
	lastNode->visual->transform->position = lastNode->frame->transform->position;
	lastNode->visual->Render = [this, visual_image]() {
		visual_image->Render();
		};
	if (!IsActive()) {

		lastNode->frame->Disable();
		lastNode->visual->Disable();

	}

	UpdateListPositioning();

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

			GameObject::Destroy(tempNode->frame);
			GameObject::Destroy(tempNode->visual);
			delete tempNode;

			UpdateListPositioning();

			return;

		}

		prevNode = tempNode;
		tempNode = tempNode->nextSlot;

	}

}

void ItemSelectionUI::SetPosition(Vector2 positionInSDL) {

	position = positionInSDL;

	UpdateListPositioning();

}