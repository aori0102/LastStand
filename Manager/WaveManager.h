#pragma once

#include <unordered_map>
#include <Type.h>
#include <GameComponent.h>
#include <string>

class WaveHandler : public GameObject {

private:

	const int BASE_SPAWN = 15;
	const float SPAWN_MULTIPLIER = 1.7f;
	const float SPAWN_DELAY = 1.0f;
	const int MIN_HORDE = 4;
	const int MAX_HORDE = 8;

private:

	static WaveHandler* instance;

	int currentWave;

	int totalZombie;
	int zombieLeft;
	int zombieToSpawn;
	int zombieKilled;
	float lastSpawnTick;

	float difficulty;
	float currentProgress;

	bool waveInProgress;

public:

	int GetCurrentWave() const { return currentWave; }
	int GetTotalZombie() const { return totalZombie; }
	int GetZombieLeft() const { return zombieLeft; }
	float GetDifficulty() const { return difficulty; }
	float GetCurrentProgress() const { return currentProgress; }
	bool WaveInProgress() const { return waveInProgress; }
	static WaveHandler* Instance() { return instance; }

public:

	WaveHandler();

	void InitiateWave();
	void Update() override;
	void RemoveZombie();

};

class WaveInfoUI {

private:

	enum class WaveInfoIndex {

		ProgressLabel,
		Progress,
		ProgressBarBackground,
		ProgressBar,
		Wave,
		NextWaveButton,
		NextWaveLabel,

	};

	const std::unordered_map<WaveInfoIndex, std::string> UI_LABEL_MAP = {
		{ WaveInfoIndex::ProgressLabel, "ProgressLabel"},
		{ WaveInfoIndex::Progress, "Progress" },
		{ WaveInfoIndex::ProgressBar, "ProgressBar" },
		{ WaveInfoIndex::ProgressBarBackground, "ProgressBarBackground" },
		{ WaveInfoIndex::Wave, "Wave" },
		{ WaveInfoIndex::NextWaveButton, "NextWaveButton" },
		{ WaveInfoIndex::NextWaveLabel, "NextWaveLabel" },
	};

	const std::unordered_map<WaveInfoIndex, std::string> UI_TEXT_MAP = {
		{ WaveInfoIndex::ProgressLabel, "Wave progress" },
		{ WaveInfoIndex::Wave, "Wave " },
		{ WaveInfoIndex::NextWaveLabel, "Next wave" },
		{ WaveInfoIndex::Progress, "%" },
	};

	const std::unordered_map<WaveInfoIndex, int> UI_TEXT_SIZE_MAP = {
		{ WaveInfoIndex::ProgressLabel, 20 },
		{ WaveInfoIndex::Progress, 15 },
		{ WaveInfoIndex::Wave, 36 },
		{ WaveInfoIndex::NextWaveLabel, 24 },
	};

	const std::unordered_map<WaveInfoIndex, Vector2> UI_POSITION_MAP = {
		{ WaveInfoIndex::ProgressLabel, Vector2(0.0f, 12.0f) },
		{ WaveInfoIndex::Progress, Vector2(0.0f, 56.0f) },
		{ WaveInfoIndex::ProgressBar, Vector2(490.0f, 42.0f) },
		{ WaveInfoIndex::ProgressBarBackground, Vector2(490.0f, 42.0f) },
		{ WaveInfoIndex::NextWaveButton, Vector2(540.0f, 650.0f) },
	};

	const std::string FOLDER_PATH = "./Asset/WaveInfo/";
	const std::string FILE_EXTENSION = ".png";

private:

	static WaveInfoUI* instance;

	std::unordered_map<WaveInfoIndex, GameObject*> uiElementMap;

	int previousProgress;
	int previousWave;

private:

	void InitializeUI();

public:

	WaveInfoUI();

};