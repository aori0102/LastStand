#pragma once

#include <unordered_set>

using namespace std;

class Player;
class Enemy;
class GameObject;
class Shop;

class GameManager {

private:

	// Entity
	static Player* player;
	static unordered_set<Enemy*> enemySet;

	// Systems
	static Shop* shop;

	// Player stats
	static int money;
	static int experience;
	static int level;
	static int expToNextLvl;
	static const int BASE_EXP;			// Base experience to get from level 0 to 1
	static const float EXP_MULTIPLIER;	// How much greater the exp to progress to next level

	// UI elements
	static GameObject* infoBackground;
	static GameObject* moneyLabel;
	static GameObject* moneyText;
	static GameObject* experienceBackground;
	static GameObject* experienceBar;
	static GameObject* levelLabel;
	static GameObject* expLabel;

public:

	static void InitializeObject();

	static void ReportDead(GameObject* gameObject);

	static void Update();

	static bool TrySpendMoney(int amount);

};