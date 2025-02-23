#pragma once

#include <unordered_set>
#include <string>
#include <Type.h>
#include <GameComponent.h>

using namespace std;

class Player;
class Zombie;
class Shop;

class GameManager : public GameObject {

private:

	static GameManager* instance;

	// Entity
	Player* player;
	unordered_set<Zombie*> enemySet;

	// Systems
	Shop* shop;

	// Player stats
	int money;
	int experience;
	int level;
	int expToNextLvl;

	const int BASE_EXP = 10;			// Base experience to get from level 0 to 1
	const float EXP_MULTIPLIER = 1.65f;	// How much greater the exp to progress to next level

	// Map setting
	GameObject* background;

	const string BACKGROUND_PATH = "./Asset/Background.png";
	const Vector2 MAP_SIZE = Vector2(3000.0f, 3000.0f);

	// Game settings
	int currentWave;
	int currentEnemyCount;
	int enemyTotal;
	int enemySpawned;
	bool isInWave;

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

	GameObject* experienceBackground;
	GameObject* experienceBar;
	GameObject* experienceLabel;
	const Vector2 EXPERIENCE_BAR_SCALE = Vector2(100.0f, 7.0f);
	const string EXP_SLASH = " | ";
	const int EXP_LABEL_SIZE = 18;

	GameObject* levelLabel;
	const string LEVEL_PREFIX = "Level: ";

	GameObject* spawnWaveButton;
	GameObject* spawnWaveLabel;
	const Vector2 SPAWN_WAVE_BUTTON_SCALE = Vector2(200.0f, 80.0f);

	void Render();


public:

	GameManager();

	void InitializeObject();
	void InitializeUI();

	void ReportDead(GameObject* gameObject);

	void Update();

	bool TrySpendMoney(int amount);

	void StartWave();

	static GameManager* Instance() { return instance; }

};