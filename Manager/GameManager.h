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
	std::unordered_set<Zombie*> enemySet;

	StatusBar* statusBarUI;

	// Systems
	Shop* shop;

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

private:

	void Render();

public:

	GameManager();

	void InitializeObject();

	void SpawnZombie(int amount, ZombieIndex zombieIndex);
	void ReportDead(GameObject* gameObject);

	void Update();

	static GameManager* Instance() { return instance; }

};