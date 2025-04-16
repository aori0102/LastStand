/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <DataManager.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include <Firearm.h>
#include <GameCore.h>
#include <ItemManager.h>
#include <Player.h>
#include <SkillList.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

DataManager* DataManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

PlayerConfig::PlayerConfig() {

	masterVolume = 1.0f;
	sfxVolume = 1.0f;
	musicVolume = 1.0f;

	keyBindingMap = GameCore::DEFAULT_KEY_BINDING_MAP;

}

void DataManager::SavePlayerData() {

	std::fstream file(dataPath + PLAYER_DATA_FILE, std::ios::out | std::ios::trunc);
	if (!file.is_open())
		throw std::exception("Error saving data. File cannot be opened");

	file << "Level:" << playerSaveData->level << std::endl;
	file << "EXP:" << playerSaveData->exp << std::endl;
	file << "Money:" << playerSaveData->money << std::endl;
	file << "SkillPoint:" << playerSaveData->skillPoint << std::endl;
	file << "Health:" << playerSaveData->health << std::endl;
	file << "Wave:" << playerSaveData->wave << std::endl;
	file << "Zombie:" << playerSaveData->zombieKilled << std::endl;
	file << "AccumulatedEXP:" << playerSaveData->accumulatedEXP << std::endl;
	file << "Damage:" << playerSaveData->damage << std::endl;

	for (auto it = playerSaveData->storage.begin(); it != playerSaveData->storage.end(); it++)
		file << "Item:" << static_cast<int>(it->first) << "|" << it->second << std::endl;

	for (auto it = playerSaveData->skillProgress.begin(); it != playerSaveData->skillProgress.end(); it++)
		file << "Skill:" << static_cast<int>(it->first) << "|" << it->second << std::endl;

	for (auto it = playerSaveData->firearmUpgradeProgress.begin(); it != playerSaveData->firearmUpgradeProgress.end(); it++) {

		for (auto it_attribute = (it->second).begin(); it_attribute != (it->second).end(); it_attribute++)
			file << "FirearmInfo:" << static_cast<int>(it->first) << "#"
			<< static_cast<int>(it_attribute->first) << "|"
			<< it_attribute->second << std::endl;

	}

	for (auto it = playerSaveData->playerAttribute.begin(); it != playerSaveData->playerAttribute.end(); it++)
		file << "PlayerAttribute:" << static_cast<int>(it->first) << "|" << it->second << std::endl;

	file.close();

}

void DataManager::LoadPlayerData() {

	std::fstream file(dataPath + PLAYER_DATA_FILE, std::ios::in);
	if (!file.is_open()) {
		// The save file does not exist, hence, no save available

		file.close();
		file.open(dataPath + PLAYER_DATA_FILE, std::ios::out);
		file.close();

		return;

	}

	playerSaveData->newSave = false;

	std::string line;
	while (std::getline(file, line)) {

		if (line.find("Level") != std::string::npos)
			playerSaveData->level = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("Money") != std::string::npos)
			playerSaveData->money = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("AccumulatedEXP") != std::string::npos)
			playerSaveData->accumulatedEXP = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("EXP") != std::string::npos)
			playerSaveData->exp = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("SkillPoint") != std::string::npos)
			playerSaveData->skillPoint = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("Wave") != std::string::npos)
			playerSaveData->wave = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("Health") != std::string::npos)
			playerSaveData->health = std::stof(line.substr(line.find(':') + 1));
		else if (line.find("Zombie") != std::string::npos)
			playerSaveData->zombieKilled = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("Damage") != std::string::npos)
			playerSaveData->damage = std::stof(line.substr(line.find(':') + 1));
		else if (line.find("Item") != std::string::npos)
			playerSaveData->storage[
				static_cast<ItemIndex>(std::stoi(line.substr(line.find(':') + 1, line.rfind('|') - line.find(':') - 1)))
			] = std::stoi(line.substr(line.find('|') + 1));
		else if (line.find("Skill") != std::string::npos)
			playerSaveData->skillProgress[
				static_cast<SkillListIndex>(std::stoi(line.substr(line.find(':') + 1, line.rfind('|') - line.find(':') - 1)))
			] = std::stoi(line.substr(line.find('|') + 1));
		else if (line.find("FirearmInfo") != std::string::npos)
			playerSaveData->firearmUpgradeProgress[
				static_cast<ItemIndex>(std::stoi(line.substr(line.find(':') + 1, line.rfind('#') - line.find(':') - 1)))
			][
				static_cast<FirearmAttributeIndex>(std::stoi(line.substr(line.find('#') + 1, line.rfind('|') - line.find('#') - 1)))
			] = std::stoi(line.substr(line.find('|') + 1));
		else if (line.find("PlayerAttribute") != std::string::npos)
			playerSaveData->playerAttribute[
				static_cast<PlayerAttribute>(std::stoi(line.substr(line.find(':') + 1, line.rfind('|') - line.find(':') - 1)))
			] = std::stoi(line.substr(line.find('|') + 1));

	}

	file.close();

}

void DataManager::InitializePlayerData() {

	// Default save data, for renewing
	defaultPlayerSaveData = PlayerSaveData();

	defaultPlayerSaveData.level = 0;
	defaultPlayerSaveData.exp = 0;
	defaultPlayerSaveData.money = 0;
	defaultPlayerSaveData.skillPoint = 0;
	defaultPlayerSaveData.wave = 0;
	defaultPlayerSaveData.accumulatedEXP = 0;
	defaultPlayerSaveData.zombieKilled = 0;
	defaultPlayerSaveData.health = 100.0f;
	defaultPlayerSaveData.damage = 0.0f;
	defaultPlayerSaveData.newSave = true;
	defaultPlayerSaveData.storage = {};
	for (int i = 0; i < static_cast<int>(SkillListIndex::Total); i++)
		defaultPlayerSaveData.skillProgress[static_cast<SkillListIndex>(i)] = 0;

	defaultPlayerSaveData.firearmUpgradeProgress = {
		{ ItemIndex::Pistol_M1911, {
			{ FirearmAttributeIndex::CriticalChance, 0 },
			{ FirearmAttributeIndex::Damage, 0 },
			{ FirearmAttributeIndex::CriticalDamage, 0 },
			{ FirearmAttributeIndex::MagazineCapacity, 0 },
			{ FirearmAttributeIndex::ReloadTime, 0 },
			{ FirearmAttributeIndex::Firerate, 0 },
		}
		},
		{ ItemIndex::Shotgun_Beretta1301, {
			{ FirearmAttributeIndex::CriticalChance, 0 },
			{ FirearmAttributeIndex::Damage, 0 },
			{ FirearmAttributeIndex::CriticalDamage, 0 },
			{ FirearmAttributeIndex::MagazineCapacity, 0 },
			{ FirearmAttributeIndex::ReloadTime, 0 },
			{ FirearmAttributeIndex::Firerate, 0 },
		}
		},
		{ ItemIndex::Rifle_M4, {
			{ FirearmAttributeIndex::CriticalChance, 0 },
			{ FirearmAttributeIndex::Damage, 0 },
			{ FirearmAttributeIndex::CriticalDamage, 0 },
			{ FirearmAttributeIndex::MagazineCapacity, 0 },
			{ FirearmAttributeIndex::ReloadTime, 0 },
			{ FirearmAttributeIndex::Firerate, 0 },
		}
		},
	};

	defaultPlayerSaveData.playerAttribute = Player::Instance()->DEFAULT_PLAYER_ATTRIBUTE_MAP;

	// Copy the data
	playerSaveData = new PlayerSaveData;
	*playerSaveData = defaultPlayerSaveData;

	LoadPlayerData();

}

void DataManager::SavePlayerConfig() {

	std::fstream file(dataPath + CONFIG_DATA_FILE, std::ios::out | std::ios::trunc);
	if (!file.is_open())
		throw std::exception("Error saving data. File cannot be opened");

	file << "Master:" << playerConfig->masterVolume << std::endl;
	file << "SFX:" << playerConfig->sfxVolume << std::endl;
	file << "Music:" << playerConfig->musicVolume << std::endl;

	for (auto it = playerConfig->keyBindingMap.begin(); it != playerConfig->keyBindingMap.end(); it++)
		file << "Key:" << static_cast<int>(it->first) << "|" << static_cast<int>(it->second) << std::endl;

	file.close();

}

void DataManager::LoadPlayerConfig() {

	std::fstream file(dataPath + CONFIG_DATA_FILE, std::ios::in);
	if (!file.is_open()) {
		// The save file does not exist, hence, no save available

		file.close();
		file.open(dataPath + CONFIG_DATA_FILE, std::ios::out);
		file.close();

		return;

	}

	std::string line;
	while (std::getline(file, line)) {

		if (line.find("Master") != std::string::npos)
			playerConfig->masterVolume = std::stof(line.substr(line.find(':') + 1));
		else if (line.find("SFX") != std::string::npos)
			playerConfig->sfxVolume = std::stof(line.substr(line.find(':') + 1));
		else if (line.find("Music") != std::string::npos)
			playerConfig->musicVolume = std::stof(line.substr(line.find(':') + 1));
		else if (line.find("Key") != std::string::npos)
			playerConfig->keyBindingMap[
				static_cast<ActionIndex>(std::stoi(line.substr(line.find(':') + 1, line.rfind('|') - line.find(':') - 1)))
			] = static_cast<SDL_Keycode>(std::stoi(line.substr(line.find('|') + 1)));

	}

	file.close();

}

DataManager::DataManager() {

	if (instance)
		throw std::exception("DataManager can only have one instance");

	instance = this;

	dataPath = GameCore::GetAppDataPath() + GAME_DATA_FOLDER;

	std::filesystem::create_directories(dataPath);

	InitializePlayerData();

	playerConfig = new PlayerConfig;
	LoadPlayerConfig();

}

DataManager::~DataManager() {

	SavePlayerData();
	delete playerSaveData;
	playerSaveData = nullptr;

	SavePlayerConfig();
	delete playerConfig;
	playerConfig = nullptr;

	instance = nullptr;

}

void DataManager::ResetPlayerData() {

	*playerSaveData = defaultPlayerSaveData;

}

DataManager* DataManager::Instance() { return instance; }