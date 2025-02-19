#pragma once

#include <unordered_set>

using namespace std;

class Button;

class UIEvent {

private:

	static unordered_set<Button*> buttonSet;

public:

	static void Update();
	static void RegisterButton(Button* button);

};