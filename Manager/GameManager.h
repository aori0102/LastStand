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
class DeathMessage;
class HotBar;
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
	GameOver,
	Tutorial,
	Statistic,

};

class GameManager {

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
	UIEventManager* uiEventManager;
	RenderManager* renderManager;
	ItemManager* itemManager;
	WaveManager* waveManager;
	GameObject* background;
	GameObject* northBorder;
	GameObject* southBorder;
	GameObject* westBorder;
	GameObject* eastBorder;

	static GameManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeObject();
	void EnableSceneObject();
	void DisableSceneObject();
	void SaveGame();
	void LoadGame();

public:

	GameManager();
	~GameManager();
	void ReportDead(GameObject* gameObject);
	void Update();
	void SwitchScene(SceneIndex targetScene);
	void SwitchToPreviousScene();
	void FreezeGame();
	void UnfreezeGame();
	void ResetGameData();
	bool GameRunning() const;
	
	static GameManager* Instance();

};