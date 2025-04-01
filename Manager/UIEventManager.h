/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_set>

class Button;

class UIEventManager {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_set<Button*> buttonSet;		// Reference to all button UI texture

	static UIEventManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	UIEventManager();
	~UIEventManager();
	void RegisterButton(Button* button);
	bool Update();	// Return whether a UI is clicked

	static UIEventManager* Instance();

};