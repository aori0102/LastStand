#include <DataManager.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include <GameCore.h>
#include <ItemManager.h>

DataManager* DataManager::instance = nullptr;

PlayerSaveData::PlayerSaveData() {

	level = 0;
	exp = 0;
	money = 0;
	skillPoint = 0;
	wave = 0;
	health = 100.0f;
	newSave = true;
	storage = {};

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

	int storageSize = playerSaveData->storage.size();
	file << storageSize << std::endl;
	for (auto it = playerSaveData->storage.begin(); it != playerSaveData->storage.end(); it++)
		file << "Item:" << static_cast<int>(it->first) << "|" << it->second << std::endl;

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
		else if (line.find("EXP") != std::string::npos)
			playerSaveData->exp = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("SkillPoint") != std::string::npos)
			playerSaveData->skillPoint = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("Wave") != std::string::npos)
			playerSaveData->wave = std::stoi(line.substr(line.find(':') + 1));
		else if (line.find("Item") != std::string::npos)
			playerSaveData->storage[
				static_cast<ItemIndex>(std::stoi(line.substr(line.find(':') + 1, line.rfind('|') - line.find(':') - 1)))
			] = std::stoi(line.substr(line.find('|') + 1));

	}

	file.close();

}

DataManager::DataManager() {

	if (instance)
		throw std::exception("DataManager can only have one instance");

	instance = this;

	dataPath = GameCore::GetAppDataPath() + GAME_DATA_FOLDER;

	std::filesystem::create_directories(dataPath);

	playerSaveData = new PlayerSaveData;
	LoadPlayerData();

}

DataManager::~DataManager() {

	SavePlayerData();
	delete playerSaveData;
	playerSaveData = nullptr;

	instance = nullptr;

}

DataManager* DataManager::Instance() { return instance; }