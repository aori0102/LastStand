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

class GameManager : public GameObject {

private:

	static GameManager* instance;

	// Entity
	Player* player;
	PlayerStatistic* playerStatistic;
	unordered_set<Zombie*> enemySet;

	StatusBar* statusBarUI;

	// Systems
	Shop* shop;

	// Player stats
	int money;

	// Map setting
	GameObject* background;

	const string BACKGROUND_PATH = "./Asset/Background.png";
	const Vector2 MAP_SIZE = Vector2(3000.0f, 3000.0f);

	// Spawn settings
	float lastSpawnTick;

	const float SPAWN_DELAY = 1.0f;
	const int MIN_HORDE = 4;
	const int MAX_HORDE = 8;
	const vector<Vector2> SPAWN_POSITION_LIST =
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

	// Game settings
	int currentWave;
	int currentEnemyCount;
	int enemyTotal;
	int enemyToSpawn;
	bool isInWave;
	float difficulty;

	const int BASE_SPAWN = 15;
	const float SPAWN_MULTIPLIER = 1.7f;

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
	const string MONEY_LABEL_TEXT = "Money: ";
	const int MONEY_LABEL_SIZE = 20;
	const int LEVEL_LABEL_SIZE = 18;

	const Vector2 SPAWN_WAVE_BUTTON_SCALE = Vector2(200.0f, 80.0f);

	void Render();

	void HandleSpawning();

public:

	GameManager();

	void InitializeObject();
	void InitializeUI();

	void ReportDead(GameObject* gameObject);

	void Update();

	bool TrySpendMoney(int amount);

	void StartWave();

	static GameManager* Instance() { return instance; }

	float GetDifficulty() const;
	int GetCurrentWave() const;

};