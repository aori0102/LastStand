﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <PlayerStatistic.h>

#include <cmath>

#include <DataManager.h>
#include <GameComponent.h>
#include <Humanoid.h>
#include <Player.h>
#include <Shop.h>
#include <WaveManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

PlayerStatistic* PlayerStatistic::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

PlayerStatistic::PlayerStatistic() {

	if (instance)
		throw std::exception("Player Statistic can only have one instance");

	instance = this;

	playerMoney = 0;
	playerSkillPoint = 0;
	playerLevel = 0;
	playerEXP = 0;
	playerEXPNeeded = PLAYER_BASE_EXP;

}

PlayerStatistic::~PlayerStatistic() {

	SaveData();

	instance = nullptr;

}

void PlayerStatistic::AddEXP(int amount) {

	playerEXP += amount;

	if (playerEXP >= playerEXPNeeded) {

		playerEXP -= playerEXPNeeded;
		playerLevel++;
		playerSkillPoint++;
		Shop::Instance()->UpdateSkillPoint(playerSkillPoint);
		playerEXPNeeded = std::powf(PLAYER_EXP_MULTIPLIER, playerLevel) * static_cast<float>(PLAYER_BASE_EXP);

	}

}

void PlayerStatistic::AddMoney(int amount) {

	playerMoney += amount;

}

void PlayerStatistic::SaveData() {

	PlayerSaveData* playerSaveData = DataManager::Instance()->playerSaveData;

	playerSaveData->money = playerMoney;
	playerSaveData->exp = playerEXP;
	playerSaveData->level = playerLevel;
	playerSaveData->skillPoint = playerSkillPoint;

}

void PlayerStatistic::LoadData() {
	PlayerSaveData* data = DataManager::Instance()->playerSaveData;

	playerMoney = data->money;
	playerSkillPoint = data->skillPoint;
	playerLevel = data->level;
	playerEXP = data->exp;

}

bool PlayerStatistic::IsMoneySufficient(int amount) {

	return playerMoney >= amount;

}

bool PlayerStatistic::TrySpendMoney(int amount) {

	if (!IsMoneySufficient(amount))
		return false;

	playerMoney -= amount;
	return true;

}

bool PlayerStatistic::TryConsumeSkillPoint(int amount) {

	if (amount > playerSkillPoint)
		return false;

	playerSkillPoint -= amount;
	Shop::Instance()->UpdateSkillPoint(playerSkillPoint);

	return true;

}

int PlayerStatistic::GetLevel() const {

	return playerLevel;

}

int PlayerStatistic::GetEXP() const {

	return playerEXP;

}

int PlayerStatistic::GetMoney() const {

	return playerMoney;

}

int PlayerStatistic::GetEXPNeeded() const {

	return playerEXPNeeded;

}

float PlayerStatistic::GetHealth() const {

	return Player::Instance()->GetComponent<Humanoid>()->GetHealth();

}

float PlayerStatistic::GetMaxHealth() const {

	return Player::Instance()->GetComponent<Humanoid>()->GetMaxHealth();

}

float PlayerStatistic::GetStamina() const {

	return Player::Instance()->GetComponent<Humanoid>()->GetStamina();

}

float PlayerStatistic::GetMaxStamina() const {

	return Player::Instance()->GetComponent<Humanoid>()->GetMaxStamina();

}

PlayerStatistic* PlayerStatistic::Instance() { return instance; }