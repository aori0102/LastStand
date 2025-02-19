#include <Shop.h>
#include <Texture.h>
#include <Type.h>
#include <Game.h>
#include <Player.h>

// Settings
const Vector2 SHOP_BACKGROUND_SIZE = Vector2(800.0f, 500.0f);
const Vector2 BUY_BUTTON_SIZE = Vector2(150.0f, 70.0f);
const Vector2 NAVIGATION_BUTTON_SIZE = Vector2(250.0f, 60.0f);
const Vector2 NAVIGATION_BUTTON_OFFSET = Vector2(5.0f, 5.0f);

Shop::Shop(Player* initPlayer) {

	if (!initPlayer)
		throw new exception("Initialize shop with null player");

	linkedPlayer = initPlayer;

	// Background
	background = new GameObject("Background");
	background->AddComponent<Image>()->backgroundColor = Color(0, 0, 0, 100);
	Transform* background_transform = background->GetComponent<Transform>();
	background_transform->position = Game::WindowResolution() / 2.0f;
	background_transform->scale = SHOP_BACKGROUND_SIZE;

	// Buy button
	buyButton = new GameObject("Buy button");
	Button* buyButton_button = buyButton->AddComponent<Button>();
	buyButton_button->backgroundColor = Color::WHITE;
	buyButton_button->OnClick = []() {cout << "Buy button is pressed" << endl; };
	Transform* buyButton_transform = buyButton->GetComponent<Transform>();
	buyButton_transform->scale = BUY_BUTTON_SIZE;
	buyButton_transform->position = Vector2(
		background_transform->position.x,
		background_transform->position.y + (background_transform->scale.y - BUY_BUTTON_SIZE.y) / 2.0f
	);

	buyButtonLabel = new GameObject("Buy button label");
	Text* buyButtonLabel_text = buyButtonLabel->AddComponent<Text>();
	buyButtonLabel_text->LoadText("Buy", Color::BLUE, 24);
	buyButtonLabel_text->showOnScreen = true;
	Transform* buyButtonLabel_transform = buyButtonLabel->GetComponent<Transform>();
	buyButtonLabel_transform->position = buyButton_transform->position;

	// Firearm navigation button
	firearmButton = new GameObject("Firearm button");
	Button* firearmButton_button = firearmButton->AddComponent<Button>();
	firearmButton_button->backgroundColor = Color::WHITE;
	firearmButton_button->OnClick = []() {cout << "Firearm button is pressed" << endl; };
	Transform* firearmButton_transform = firearmButton->GetComponent<Transform>();
	firearmButton_transform->scale = NAVIGATION_BUTTON_SIZE;
	firearmButton_transform->position = Vector2(
		background_transform->position.x,
		background_transform->position.y - (background_transform->scale.y - NAVIGATION_BUTTON_SIZE.y) / 2.0f + NAVIGATION_BUTTON_OFFSET.y
	);

	firearmButtonLabel = new GameObject("Firearm button label");
	Text* firearmButtonLabel_text = firearmButtonLabel->AddComponent<Text>();
	firearmButtonLabel_text->LoadText("Firearm", Color::BLUE, 24);
	firearmButtonLabel_text->showOnScreen = true;
	Transform* firearmButtonLabel_transform = firearmButtonLabel->GetComponent<Transform>();
	firearmButtonLabel_transform->position = firearmButton_transform->position;

	// Melee navigation button
	meleeButton = new GameObject("Melee button");
	Button* meleeButton_button = meleeButton->AddComponent<Button>();
	meleeButton_button->backgroundColor = Color::WHITE;
	meleeButton_button->OnClick = []() {cout << "Melee button is pressed" << endl; };
	Transform* meleeButton_transform = meleeButton->GetComponent<Transform>();
	meleeButton_transform->scale = NAVIGATION_BUTTON_SIZE;
	meleeButton_transform->position = Vector2(
		firearmButton_transform->position.x - (firearmButton_transform->scale.x + meleeButton_transform->scale.x) / 2.0f - NAVIGATION_BUTTON_OFFSET.x,
		background_transform->position.y - (background_transform->scale.y - NAVIGATION_BUTTON_SIZE.y) / 2.0f + NAVIGATION_BUTTON_OFFSET.y
	);

	meleeButtonLabel = new GameObject("Melee button label");
	Text* meleeButtonLabel_text = meleeButtonLabel->AddComponent<Text>();
	meleeButtonLabel_text->LoadText("Melee", Color::BLUE, 24);
	meleeButtonLabel_text->showOnScreen = true;
	Transform* meleeButtonLabel_transform = meleeButtonLabel->GetComponent<Transform>();
	meleeButtonLabel_transform->position = meleeButton_transform->position;

	// Utility navigation button
	utilityButton = new GameObject("Utility button");
	Button* utilityButton_button = utilityButton->AddComponent<Button>();
	utilityButton_button->backgroundColor = Color::WHITE;
	utilityButton_button->OnClick = []() {cout << "Utility button is pressed" << endl; };
	Transform* utilityButton_transform = utilityButton->GetComponent<Transform>();
	utilityButton_transform->scale = NAVIGATION_BUTTON_SIZE;
	utilityButton_transform->position = Vector2(
		firearmButton_transform->position.x + (firearmButton_transform->scale.x + utilityButton_transform->scale.x) / 2.0f + NAVIGATION_BUTTON_OFFSET.x,
		background_transform->position.y - (background_transform->scale.y - NAVIGATION_BUTTON_SIZE.y) / 2.0f + NAVIGATION_BUTTON_OFFSET.y
	);

	utilityButtonLabel = new GameObject("Utility button label");
	Text* utilityButtonLabel_text = utilityButtonLabel->AddComponent<Text>();
	utilityButtonLabel_text->LoadText("Utility", Color::BLUE, 24);
	utilityButtonLabel_text->showOnScreen = true;
	Transform* utilityButtonLabel_transform = utilityButtonLabel->GetComponent<Transform>();
	utilityButtonLabel_transform->position = utilityButton_transform->position;

	showShop = false;

}

void Shop::Update() {

	if (Game::GetKeyState(SDLK_TAB).started)
		showShop = !showShop;

	if (showShop) {

		linkedPlayer->DisableInteraction();
		Show();

	} else {

		linkedPlayer->EnableInteraction();
		Hide();

	}

	Render();

}

void Shop::Show() {

	buyButton->GetComponent<Button>()->Enable();

	firearmButton->GetComponent<Button>()->Enable();

	meleeButton->GetComponent<Button>()->Enable();

	utilityButton->GetComponent<Button>()->Enable();

}

void Shop::Hide() {

	buyButton->GetComponent<Button>()->Disable();

	firearmButton->GetComponent<Button>()->Disable();

	meleeButton->GetComponent<Button>()->Disable();

	utilityButton->GetComponent<Button>()->Disable();

}

void Shop::Render() {

	if (!showShop)
		return;

	background->GetComponent<Image>()->Render();

	buyButton->GetComponent<Button>()->Render();
	buyButtonLabel->GetComponent<Text>()->Render();

	firearmButton->GetComponent<Button>()->Render();
	firearmButtonLabel->GetComponent<Text>()->Render();

	meleeButton->GetComponent<Button>()->Render();
	meleeButtonLabel->GetComponent<Text>()->Render();

	utilityButton->GetComponent<Button>()->Render();
	utilityButtonLabel->GetComponent<Text>()->Render();

}