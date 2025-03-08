#pragma once

#include <unordered_set>

class Button;

class UIEvent {

private:

	static std::unordered_set<Button*> buttonSet;

public:

	static bool Update();	// Return whether a UI is clicked
	static void RegisterButton(Button* button);

};