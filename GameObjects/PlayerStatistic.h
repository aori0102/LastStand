﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

class Player;

class PlayerStatistic {

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
	int playerEXPNeeded;
	static PlayerStatistic* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	PlayerStatistic();

	void AddEXP(int amount);
	void AddMoney(int amount);
	int GetLevel() const;
	int GetEXP() const;
	int GetMoney() const;
	int GetEXPNeeded() const;
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetStamina() const;
	float GetMaxStamina() const;
	bool TrySpendMoney(int amount);
	static PlayerStatistic* Instance();

};