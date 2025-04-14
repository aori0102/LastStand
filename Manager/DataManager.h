#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>

enum class ActionIndex;
enum class ItemIndex;
enum class SkillListIndex;
enum class FirearmAttributeIndex;
enum class PlayerAttribute;

class PlayerSaveData {

private:

	friend class PlayerStatistic;
	friend class DataManager;
	friend class Inventory;
	friend class WaveManager;
	friend class SkillList;
	friend class FirearmUpgrade;
	friend class Player;

	int level;
	int money;
	int exp;
	int skillPoint;
	int wave;
	float health;
	bool newSave;
	std::unordered_map<ItemIndex, int> storage;
	std::unordered_map<SkillListIndex, int> skillProgress;
	std::unordered_map<ItemIndex, std::unordered_map<FirearmAttributeIndex, int>> firearmUpgradeProgress;
	std::unordered_map<PlayerAttribute, float> playerAttribute;

	PlayerSaveData();

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

	static DataManager* instance;

public:

	PlayerSaveData* playerSaveData;
	PlayerConfig* playerConfig;

private:

	void SavePlayerData();
	void LoadPlayerData();

	void SavePlayerConfig();
	void LoadPlayerConfig();

public:

	DataManager();
	~DataManager();

	static DataManager* Instance();

};