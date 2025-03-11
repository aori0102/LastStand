#pragma once

#include <unordered_set>
#include <string>
#include <Type.h>
#include <GameComponent.h>
#include <vector>

class PlayerStatistic;
class Zombie;
class Shop;
class StatusBar;
enum class ZombieIndex;

class GameManager : public GameObject {

private:

	static GameManager* instance;

	// Entity
	Player* player;
	PlayerStatistic* playerStatistic;
	std::unordered_set<Zombie*> enemySet;

	StatusBar* statusBarUI;

	// Systems
	Shop* shop;

	// Player stats
	int money;

	// Map setting
	GameObject* background;

	const Vector2 MAP_SIZE = Vector2(3000.0f, 3000.0f);

	// Spawn settings
	const std::vector<Vector2> SPAWN_POSITION_LIST =
	{
	Vector2(-1450.0f, 500.0f),
	Vector2(-1450.0f, -500.0f),
	Vector2(-500.0f, 1450.0f),
	Vector2(500.0f, 1450.0f),
	Vector2(1450.0f, -500.0f),
	Vector2(1450.0f, 500.0f),
	Vector2(-500.0f, -1450.0f),
	Vector2(500.0f, -1450.0f)
	};

	// Border
	GameObject* northBorder;
	GameObject* southBorder;
	GameObject* westBorder;
	GameObject* eastBorder;

	// UI elements
	GameObject* infoBackground;
	const Vector2 INFO_BOARD_SCALE = Vector2(300.0f, 225.0f);

	GameObject* moneyLabel;
	GameObject* moneyText;
	const std::string MONEY_LABEL_TEXT = "Money: ";
	const int MONEY_LABEL_SIZE = 20;
	const int LEVEL_LABEL_SIZE = 18;

	const Vector2 SPAWN_WAVE_BUTTON_SCALE = Vector2(200.0f, 80.0f);

private:

	void Render();

public:

	GameManager();

	void InitializeObject();
	void InitializeUI();

	void SpawnZombie(int amount, ZombieIndex zombieIndex);
	void ReportDead(GameObject* gameObject);

	void Update();

	bool TrySpendMoney(int amount);

	static GameManager* Instance() { return instance; }

};