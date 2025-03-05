#include <PlayerStatistic.h>
#include <Player.h>
#include <GameComponent.h>
#include <cmath>

PlayerStatistic::PlayerStatistic(Player* initLinkedPlayer) {

	linkedPlayer = initLinkedPlayer;
	if (!linkedPlayer->TryGetComponent<Humanoid>())
		throw new exception("Linked player to statistic requires a humanoid");

	playerLevel = 0;
	playerEXP = 0;
	playerEXPNeeded = PLAYER_BASE_EXP;

}

int PlayerStatistic::GetLevel() const {

	return playerLevel;

}

int PlayerStatistic::GetEXP() const {

	return playerEXP;

}

int PlayerStatistic::GetEXPNeeded() const {

	return playerEXPNeeded;

}

float PlayerStatistic::GetHealth() const {

	return linkedPlayer->GetComponent<Humanoid>()->GetHealth();

}

float PlayerStatistic::GetMaxHealth() const {

	return linkedPlayer->GetComponent<Humanoid>()->GetMaxHealth();

}

float PlayerStatistic::GetStamina() const {

	return linkedPlayer->GetComponent<Humanoid>()->GetStamina();

}

float PlayerStatistic::GetMaxStamina() const {

	return linkedPlayer->GetComponent<Humanoid>()->GetMaxStamina();

}

void PlayerStatistic::AddEXP(int amount) {

	playerEXP += amount;

	if (playerEXP >= playerEXPNeeded) {

		playerEXP -= playerEXPNeeded;
		playerLevel++;
		playerEXPNeeded = std::powf(PLAYER_EXP_MULTIPLIER, playerLevel) * static_cast<float>(PLAYER_BASE_EXP);

	}
	
}