/// >> > >> > >> > >> > >> > >> > ------ - << < << < << < << < << < << < << <
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameComponent.h>
#include <Utils.h>

class Firearm;

class FirearmSelectionUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	struct SlotNode {

		SlotNode* nextSlot;
		GameObject* frame;
		GameObject* visual;
		Firearm* firearm;

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

	void UpdateListPosition();
	void Show();
	void Hide();

public:

	FirearmSelectionUI();
	~FirearmSelectionUI();
	void RemoveFirearm(Firearm* removingFirearm);
	void SetPosition(Vector2 positionInSDL);
	void ClearSelection();
	bool TryAddFirearm(Firearm* newFirearm);

};