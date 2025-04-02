/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include <Utils.h>

class GameObject;
class Player;
class PlayerStatistic;
class Shop;
class StatusBar;
class Zombie;
enum class ZombieIndex;

class GameManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	const Vector2 MAP_SIZE = Vector2(3000.0f, 3000.0f);
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

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_set<Zombie*> zombieSet;
	GameObject* background;
	GameObject* northBorder;
	GameObject* southBorder;
	GameObject* westBorder;
	GameObject* eastBorder;
	Player* player;
	PlayerStatistic* playerStatistic;
	StatusBar* statusBar;
	Shop* shop;

	static GameManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	GameManager();
	~GameManager();
	void InitializeObject();
	void ReportDead(GameObject* gameObject);
	void SpawnZombie(int amount, ZombieIndex zombieIndex);
	void Update();

	static GameManager* Instance();

};