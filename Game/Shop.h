#pragma once

#include <GameComponent.h>

class Player;

class Shop : public GameObject {

private:

	enum class ShopMenuIndex {

		Firearm,
		Melee,
		Utility

	};
	
	// Player to control interaction
	Player* linkedPlayer;

	// Shop items

	// UI elements
	GameObject* background;

	GameObject* buyButton;
	GameObject* buyButtonLabel;

	GameObject* firearmButton;
	GameObject* firearmButtonLabel;

	GameObject* meleeButton;
	GameObject* meleeButtonLabel;

	GameObject* utilityButton;
	GameObject* utilityButtonLabel;

	// Control
	bool showShop;
	ShopMenuIndex shopMenuIndex;

	void Render();
	void Show();
	void Hide();

public:

	Shop(Player* initPlayer);
	void Update() override;

};