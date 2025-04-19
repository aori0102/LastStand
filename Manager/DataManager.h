/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

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

public:
	
	int level;
	int money;
	int exp;
	int accumulatedEXP;
	int skillPoint;
	int waveSurvived;
	int mostWaveSurvived;
	int zombieKilled;
	int mostZombieKilled;
	float health;
	float damageDealt;
	float mostDamageDealt;
	bool newSave;
	std::unordered_map<ItemIndex, int> storage;
	std::unordered_map<SkillListIndex, int> skillProgress;
	std::unordered_map<ItemIndex, std::unordered_map<FirearmAttributeIndex, int>> firearmUpgradeProgress;
	std::unordered_map<PlayerAttribute, float> playerAttribute;

};

class PlayerConfig {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	friend class GameCore;
	friend class DataManager;

	float masterVolume;
	float sfxVolume;
	float musicVolume;
	std::unordered_map<ActionIndex, SDL_Keycode> keyBindingMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	PlayerConfig();

};

class DataManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	const std::string GAME_DATA_FOLDER = "\\LastStand\\";
	const std::string PLAYER_DATA_FILE = "player.txt";
	const std::string CONFIG_DATA_FILE = "config.txt";

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::string dataPath;
	PlayerSaveData defaultPlayerSaveData;

	static DataManager* instance;

public:

	PlayerSaveData* playerSaveData;
	PlayerConfig* playerConfig;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

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