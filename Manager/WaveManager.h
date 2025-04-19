/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <string>
#include <unordered_map>

#include <GameObject.h>
#include <Utils.h>

class WaveInfoUI;
class Zombie;
enum class ZombieIndex;

class WaveManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	const int BASE_SPAWN = 7;
	const int MIN_HORDE = 2;
	const int MAX_HORDE = 7;
	const int BASE_WAVE_REWARD = 500;
	const float REWARD_MULTIPLIER = 1.19f;
	const float SPAWN_MULTIPLIER = 1.26f;
	const float SPAWN_DELAY = 4.39f;
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

	bool waveInProgress;
	bool isActive;
	int currentWave;
	int totalZombie;
	int zombieLeft;
	int zombieToSpawn;
	int zombieKilledThisWave;
	int zombieKilledTotal;
	float lastSpawnTick;
	float difficulty;
	float currentProgress;
	std::unordered_set<Zombie*> zombieSet;
	WaveInfoUI* waveInfoUI;

	static WaveManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void EndWave();
	void SpawnZombieHorde(int amount);

public:

	WaveManager();
	~WaveManager();
	void InitiateWave();
	void Update();
	void Disable();
	void Enable();
	void RemoveZombie(Zombie* zombie);
	void ResetStat();
	bool WaveInProgress() const;
	int GetCurrentWave() const;
	int GetSurvivedWave() const;
	int GetTotalZombie() const;
	int GetZombieLeft() const;
	int GetTotalZombieKilled() const;
	float GetDifficulty() const;
	float GetCurrentProgress() const;

	static WaveManager* Instance();

};

class WaveInfoUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class WaveInfoIndex {

		ProgressLabel,
		ProgressBarLabel,
		ProgressBarBackground,
		ProgressBar,
		WaveLabel,
		NextWaveButton,
		NextWaveLabel,

	};

	const std::string FOLDER_PATH = "./Asset/WaveInfo/";
	const std::string FILE_EXTENSION = ".png";
	const std::unordered_map<WaveInfoIndex, int> UI_TEXT_SIZE_MAP = {
		{ WaveInfoIndex::ProgressLabel, 20 },
		{ WaveInfoIndex::ProgressBarLabel, 15 },
		{ WaveInfoIndex::WaveLabel, 36 },
		{ WaveInfoIndex::NextWaveLabel, 24 },
	};
	const std::unordered_map<WaveInfoIndex, std::string> UI_TEXT_MAP = {
		{ WaveInfoIndex::ProgressLabel, "Wave progress" },
		{ WaveInfoIndex::WaveLabel, "Wave " },
		{ WaveInfoIndex::NextWaveLabel, "Next wave" },
		{ WaveInfoIndex::ProgressBarLabel, "%" },
	};
	const std::unordered_map<WaveInfoIndex, Vector2> UI_POSITION_MAP = {
		{ WaveInfoIndex::ProgressLabel, Vector2(0.0f, 12.0f) },
		{ WaveInfoIndex::ProgressBarLabel, Vector2(0.0f, 56.0f) },
		{ WaveInfoIndex::ProgressBar, Vector2(490.0f, 42.0f) },
		{ WaveInfoIndex::ProgressBarBackground, Vector2(490.0f, 42.0f) },
		{ WaveInfoIndex::NextWaveButton, Vector2(540.0f, 650.0f) },
	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	int previousProgress;
	int previousWave;
	std::unordered_map<WaveInfoIndex, GameObject*> uiElementMap;

	static WaveInfoUI* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeUI();

public:

	WaveInfoUI();
	~WaveInfoUI();

	static WaveInfoUI* Instance();

};