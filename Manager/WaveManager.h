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

class WaveManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	const int BASE_SPAWN = 15;
	const float SPAWN_MULTIPLIER = 1.7f;
	const float SPAWN_DELAY = 1.0f;
	const int MIN_HORDE = 4;
	const int MAX_HORDE = 8;

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
	int zombieKilled;
	float lastSpawnTick;
	float difficulty;
	float currentProgress;
	WaveInfoUI* waveInfoUI;

	static WaveManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	WaveManager();
	~WaveManager();
	void InitiateWave();
	void Update();
	void Disable();
	void Enable();
	void RemoveZombie();
	bool WaveInProgress() const;
	int GetCurrentWave() const;
	int GetTotalZombie() const;
	int GetZombieLeft() const;
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