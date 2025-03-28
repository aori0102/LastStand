/// >> > >> > >> > >> > >> > >> > ------ - << < << < << < << < << < << < << <
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameComponent.h>
#include <Type.h>

enum class ItemIndex;

class SlotNode {

public:

	SlotNode* nextSlot;
	GameObject* frame;
	GameObject* cell;
	GameObject* visual;
	ItemIndex itemIndex;

	SlotNode();

};

class ItemSelectionUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

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