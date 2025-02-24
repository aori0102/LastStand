#pragma once

#include <unordered_set>

using namespace std;

class Button;

class UIEvent {

private:

	static unordered_set<Button*> buttonSet;

public:

	static bool Update();	// Return whether a UI is clicked
	static void RegisterButton(Button* button);

};