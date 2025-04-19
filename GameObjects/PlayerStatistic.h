/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameObject.h>

class Player;

class PlayerStatistic : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	const int PLAYER_BASE_EXP = 10;
	const float PLAYER_EXP_MULTIPLIER = 1.78f;
	
	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	int playerMoney;
	int playerLevel;
	int playerEXP;
	int playerTotalEXP;
	int playerEXPNeeded;
	int playerSkillPoint;
	float playerDamage;

	static PlayerStatistic* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	PlayerStatistic();
	~PlayerStatistic();
	void AddEXP(int amount);
	void AddMoney(int amount);
	void AddDamage(float amount);
	void SaveData();
	void LoadData();
	void ResetStat();
	bool IsMoneySufficient(int amount) const;
	bool TrySpendMoney(int amount);
	bool TryConsumeSkillPoint(int amount);
	int GetLevel() const;
	int GetEXP() const;
	int GetTotalEXP() const;
	int GetMoney() const;
	int GetEXPNeeded() const;
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetStamina() const;
	float GetMaxStamina() const;
	float GetDamage() const;

	static PlayerStatistic* Instance();

};