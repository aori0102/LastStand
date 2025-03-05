#pragma once

class Player;

class PlayerStatistic {

private:

	Player* linkedPlayer;

	int playerLevel;
	int playerEXP;
	int playerEXPNeeded;

	const int PLAYER_BASE_EXP = 10;
	const float PLAYER_EXP_MULTIPLIER = 1.78f;

public:

	PlayerStatistic(Player* initLinkedPlayer);

	void AddEXP(int amount);

	int GetLevel() const;
	int GetEXP() const;
	int GetEXPNeeded() const;
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetStamina() const;
	float GetMaxStamina() const;

};