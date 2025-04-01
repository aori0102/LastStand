/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameManager.h>

#include <exception>
#include <string>

#include <GameComponent.h>
#include <GameCore.h>
#include <MediaManager.h>
#include <Player.h>
#include <PlayerStatistic.h>
#include <RenderManager.h>
#include <Shop.h>
#include <StatusBar.h>
#include <Texture.h>
#include <WaveManager.h>
#include <Zombie.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

GameManager* GameManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

GameManager::GameManager() {

	if (instance)
		throw std::exception("Only one GameManager is allowed");

	instance = this;

	InitializeObject();

}

GameManager::~GameManager() {

	delete background;
	background = nullptr;

	delete northBorder;
	northBorder = nullptr;

	delete southBorder;
	southBorder = nullptr;

	delete westBorder;
	westBorder = nullptr;

	delete eastBorder;
	eastBorder = nullptr;

	delete player;
	player = nullptr;

	delete playerStatistic;
	playerStatistic = nullptr;

	delete statusBar;
	statusBar = nullptr;

	delete shop;
	shop = nullptr;

	instance = nullptr;

}

void GameManager::InitializeObject() {

	northBorder = new GameObject("North border");
	Transform* northBorder_transform = northBorder->GetComponent<Transform>();
	northBorder_transform->scale = Vector2(MAP_SIZE.x, 1.0f);
	northBorder_transform->position = Vector2(0.0f, -MAP_SIZE.y / 2.0f);
	northBorder->AddComponent<BoxCollider>();

	southBorder = new GameObject("South border");
	Transform* southBorder_transform = southBorder->GetComponent<Transform>();
	southBorder_transform->scale = Vector2(MAP_SIZE.x, 1.0f);
	southBorder_transform->position = Vector2(0.0f, MAP_SIZE.y / 2.0f);
	southBorder->AddComponent<BoxCollider>();

	westBorder = new GameObject("West border");
	Transform* westBorder_transform = westBorder->GetComponent<Transform>();
	westBorder_transform->scale = Vector2(1.0f, MAP_SIZE.y);
	westBorder_transform->position = Vector2(-MAP_SIZE.x / 2.0f, 0.0f);
	westBorder->AddComponent<BoxCollider>();

	eastBorder = new GameObject("East border");
	Transform* eastBorder_transform = eastBorder->GetComponent<Transform>();
	eastBorder_transform->scale = Vector2(1.0f, MAP_SIZE.y);
	eastBorder_transform->position = Vector2(MAP_SIZE.x / 2.0f, 0.0f);
	eastBorder->AddComponent<BoxCollider>();

	// Map background
	background = new GameObject("Background", Layer::Background);
	Image* background_image = background->AddComponent<Image>();
	background_image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_Background), true);
	background_image->showOnScreen = false;
	background->GetComponent<Transform>()->position = Vector2::zero;
	background->Render = [background_image]() {
		background_image->Render();
		};

	// Player
	player = new Player();
	GameCore::LetCameraFocus(Player::Instance());
	playerStatistic = new PlayerStatistic();
	statusBar = new StatusBar;
	shop = new Shop;

}

void GameManager::ReportDead(GameObject* gameObject) {

	if (gameObject->IsA<Player>()) {

		throw std::exception("You're dead. You fucking suck. Also, say goodbye to your PC :)");

	} else if (gameObject->IsA<Zombie>()) {

		// Point, xp, money, etc
		PlayerStatistic::Instance()->AddMoney(10);
		PlayerStatistic::Instance()->AddEXP(gameObject->As<Zombie>()->GetExp());

		WaveManager::Instance()->RemoveZombie();

	}

}

void GameManager::SpawnZombie(int amount, ZombieIndex zombieIndex) {

	std::vector<Vector2> spawnPositionList = SPAWN_POSITION_LIST;
	Algorithm::Shuffle(spawnPositionList);

	for (int i = 0; i < amount; i++) {

		Zombie* zombie = new Zombie(zombieIndex);

		zombie->transform->position = spawnPositionList[i];

	}

}

void GameManager::Update() {

	WaveManager::Instance()->Update();

}

GameManager* GameManager::Instance() { return instance; }