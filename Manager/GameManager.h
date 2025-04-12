/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include <GameComponent.h>
#include <Utils.h>

class AudioManager;
class AnimationManager;
class DataManager;
class Inventory;
class ItemManager;
class MediaManager;
class Menu;
class PauseMenu;
class PhysicsManager;
class Player;
class PlayerStatistic;
class RenderManager;
class SettingsUI;
class Shop;
class StatusBar;
class UIEventManager;
class WaveManager;
class Zombie;
enum class ZombieIndex;

enum class SceneIndex {

	MainMenu,
	Settings,
	InGame,
	InGamePaused,

};

class GameManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

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

public:

	const Vector2 MAP_SIZE = Vector2(3700.0f, 3700.0f);

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool gameRunning;
	SceneIndex currentScene;
	SceneIndex previousScene;
	AudioManager* audioManager;
	AnimationManager* animationManager;
	DataManager* dataManager;
	PhysicsManager* physicsManager;
	MediaManager* mediaManager;
	Menu* menu;
	UIEventManager* uiEventManager;
	RenderManager* renderManager;
	ItemManager* itemManager;
	WaveManager* waveManager;
	GameObject* background;
	GameObject* northBorder;
	GameObject* southBorder;
	GameObject* westBorder;
	GameObject* eastBorder;
	Player* player;
	PlayerStatistic* playerStatistic;
	StatusBar* statusBar;
	Shop* shop;
	Inventory* inventory;
	SettingsUI* settingsUI;
	PauseMenu* pauseMenu;

	static GameManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeObject();
	void EnableSceneObject();
	void DisableSceneObject();

public:

	GameManager();
	~GameManager();
	void ReportDead(GameObject* gameObject);
	void SpawnZombie(int amount, ZombieIndex zombieIndex);
	void Update();
	void SwitchScene(SceneIndex targetScene);
	void SwitchToPreviousScene();
	void FreezeGame();
	void UnfreezeGame();
	bool GameRunning() const;
	
	static GameManager* Instance();

};