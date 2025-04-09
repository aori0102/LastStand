#pragma once

#include <string>
#include <unordered_map>

enum class ItemIndex;

class PlayerSaveData {

private:

	friend class PlayerStatistic;
	friend class DataManager;
	friend class Inventory;
	friend class WaveManager;

	int level;
	int money;
	int exp;
	int skillPoint;
	int wave;
	float health;
	bool newSave;
	std::unordered_map<ItemIndex, int> storage;

	PlayerSaveData();

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

private:

	void SavePlayerData();
	void LoadPlayerData();

public:

	DataManager();
	~DataManager();

	static DataManager* Instance();

};