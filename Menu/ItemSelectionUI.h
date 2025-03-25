/// >> > >> > >> > >> > >> > >> > ------ - << < << < << < << < << < << < << <
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameComponent.h>
#include <Type.h>

enum class ItemIndex;

class ItemSelectionUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	struct SlotNode {

		SlotNode* nextSlot = nullptr;
		GameObject* frame = nullptr;
		GameObject* cell = nullptr;
		GameObject* visual = nullptr;
		ItemIndex itemIndex = ItemIndex::None;

	};

	static const int MAX_COLUMN;
	static const Vector2 CELL_SIZE;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	Vector2 position;
	SlotNode* headNode;
	SlotNode* lastNode;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void UpdateNodeVisual();

public:

	ItemSelectionUI();

	void AddItem(ItemIndex newItemIndex);
	void RemoveItem(ItemIndex removingItemIndex);
	void SetPosition(Vector2 positionInSDL);

};