#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>

enum class ActionIndex;
enum class ItemIndex;
enum class SkillListIndex;
enum class FirearmAttributeIndex;
enum class PlayerAttribute;

struct PlayerSaveData {

	int level = 0;
	int money = 0;
	int exp = 0;
	int accumulatedEXP = 0;
	int skillPoint = 0;
	int wave = 0;
	int zombieKilled = 0;
	float health = 0.0f;
	float damage = 0.0f;
	bool newSave = true;
	std::unordered_map<ItemIndex, int> storage = {};
	std::unordered_map<SkillListIndex, int> skillProgress = {};
	std::unordered_map<ItemIndex, std::unordered_map<FirearmAttributeIndex, int>> firearmUpgradeProgress = {};
	std::unordered_map<PlayerAttribute, float> playerAttribute = {};

};

class PlayerConfig {

private:

	friend class GameCore;
	friend class DataManager;

	float masterVolume;
	float sfxVolume;
	float musicVolume;
	std::unordered_map<ActionIndex, SDL_Keycode> keyBindingMap;

	PlayerConfig();

};

class DataManager {

private:

	const std::string GAME_DATA_FOLDER = "\\LastStand\\";
	const std::string PLAYER_DATA_FILE = "player.txt";
	const std::string CONFIG_DATA_FILE = "config.txt";

private:

	std::string dataPath;
	PlayerSaveData defaultPlayerSaveData;

	static DataManager* instance;

public:

	PlayerSaveData* playerSaveData;
	PlayerConfig* playerConfig;

private:

	void SavePlayerData();
	void LoadPlayerData();
	void InitializePlayerData();

	void SavePlayerConfig();
	void LoadPlayerConfig();

public:

	DataManager();
	~DataManager();
	void ResetPlayerData();

	static DataManager* Instance();

};