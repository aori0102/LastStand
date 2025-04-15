/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <WaveManager.h>

#include <cmath>
#include <exception>
#include <string>

#include <DataManager.h>
#include <DeathMessage.h>
#include <GameCore.h>
#include <GameManager.h>
#include <PlayerStatistic.h>
#include <MediaManager.h>
#include <Texture.h>
#include <Zombie.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

WaveManager* WaveManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void WaveManager::EndWave() {

	waveInProgress = false;

	PlayerStatistic::Instance()->AddMoney(BASE_WAVE_REWARD * std::powf(REWARD_MULTIPLIER, currentWave));

	PlayerStatistic::Instance()->SaveData();
	DataManager::Instance()->playerSaveData->wave = currentWave;
	DataManager::Instance()->playerSaveData->zombieKilled = zombieKilledTotal;

}

void WaveManager::SpawnZombie(int amount, ZombieIndex zombieIndex) {

	std::vector<Vector2> spawnPositionList = SPAWN_POSITION_LIST;
	Algorithm::Shuffle(spawnPositionList);

	for (int i = 0; i < amount; i++) {

		Zombie* zombie = GameObject::Instantiate<Zombie>("Zombie", Layer::Zombie);
		zombie->SetIndex(zombieIndex);
		zombie->transform->position = spawnPositionList[i];
		zombieSet.insert(zombie);

	}

}

WaveManager::WaveManager() {

	if (instance)
		throw std::exception("Wave handler should only have one instance!");

	waveInfoUI = GameObject::Instantiate<WaveInfoUI>("Wave Info UI", Layer::GUI);

	isActive = true;

	waveInProgress = false;
	currentWave = DataManager::Instance()->playerSaveData->wave;
	totalZombie = 0;
	zombieLeft = 0;
	zombieToSpawn = 0;
	zombieKilledThisWave = 0;
	zombieKilledTotal = DataManager::Instance()->playerSaveData->zombieKilled;
	lastSpawnTick = 0.0f;
	difficulty = 1.0f;
	currentProgress = 0.0f;

	instance = this;

}

WaveManager::~WaveManager() {

	GameObject::Destroy(waveInfoUI);
	waveInfoUI = nullptr;

	instance = nullptr;

}

void WaveManager::InitiateWave() {

	if (waveInProgress)
		return;

	waveInProgress = true;

	currentWave++;

	zombieKilledThisWave = 0;
	zombieLeft = 0;

	currentProgress = 0.0f;

	zombieToSpawn = static_cast<int>(BASE_SPAWN * std::powf(SPAWN_MULTIPLIER, currentWave));
	totalZombie = zombieToSpawn;

}

void WaveManager::Update() {

	if (!isActive)
		return;

	if (waveInProgress && zombieToSpawn > 0 && GameCore::Time() >= lastSpawnTick + SPAWN_DELAY) {

		int spawnAmount = Random::Int(std::min(zombieToSpawn, MIN_HORDE), std::min(zombieToSpawn, MAX_HORDE));
		zombieToSpawn -= spawnAmount;
		zombieLeft += spawnAmount;

		lastSpawnTick = GameCore::Time();

		SpawnZombie(
			spawnAmount,
			static_cast<ZombieIndex>(
				Random::Int(static_cast<int>(ZombieIndex::Normal), static_cast<int>(ZombieIndex::Tanker))
				)
		);

	}

}

void WaveManager::Enable() {

	isActive = true;
	waveInfoUI->Enable();

}

void WaveManager::Disable() {

	isActive = false;
	waveInfoUI->Disable();

}

void WaveManager::RemoveZombie(Zombie* zombie) {

	zombieLeft--;
	zombieKilledThisWave++;
	zombieKilledTotal++;

	currentProgress = static_cast<float>(zombieKilledThisWave) / static_cast<float>(totalZombie);

	zombieSet.erase(zombie);

	GameObject::Destroy(zombie);

	if (zombieLeft == 0 && zombieToSpawn == 0)
		EndWave();

}

void WaveManager::ResetStat() {

	waveInProgress = false;
	zombieKilledThisWave = 0;
	zombieKilledTotal = 0;
	zombieLeft = 0;
	currentProgress = 0.0f;
	currentWave = 0;

	for (auto zombie : zombieSet)
		GameObject::Destroy(zombie);

	zombieSet.clear();

}

bool WaveManager::WaveInProgress() const { return waveInProgress; }

int WaveManager::GetCurrentWave() const { return currentWave; }

int WaveManager::GetTotalZombie() const { return totalZombie; }

int WaveManager::GetZombieLeft() const { return zombieLeft; }

int WaveManager::GetTotalZombieKilled() const { return zombieKilledTotal; }

float WaveManager::GetDifficulty() const { return difficulty; }

float WaveManager::GetCurrentProgress() const { return currentProgress; }

WaveManager* WaveManager::Instance() { return instance; }