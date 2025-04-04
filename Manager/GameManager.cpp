/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameManager.h>

#include <exception>
#include <string>

#include <AnimationManager.h>
#include <AudioManager.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <PhysicsManager.h>
#include <Player.h>
#include <PlayerStatistic.h>
#include <RenderManager.h>
#include <Shop.h>
#include <StatusBar.h>
#include <Texture.h>
#include <UIEventManager.h>
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

	std::cout << "Initializing UIEventManager..." << std::endl;
	uiEventManager = new UIEventManager;

	std::cout << "Initializing MediaManager..." << std::endl;
	mediaManager = new MediaManager;

	std::cout << "Initializing AudioManager..." << std::endl;
	audioManager = new AudioManager;

	std::cout << "Initializing RenderManager..." << std::endl;
	renderManager = new RenderManager;

	std::cout << "Initializing PhysicsManager..." << std::endl;
	physicsManager = new PhysicsManager;

	std::cout << "Initializing AnimationManager..." << std::endl;
	animationManager = new AnimationManager;

	std::cout << "Initializing ItemManager..." << std::endl;
	itemManager = new ItemManager;

	std::cout << "Initializing WaveManager..." << std::endl;
	waveManager = new WaveManager;

	InitializeObject();

}

GameManager::~GameManager() {

	std::cout << "Flushing game objects...\n";
	GameObject::DropNuke();

	background = nullptr;
	northBorder = nullptr;
	southBorder = nullptr;
	westBorder = nullptr;
	eastBorder = nullptr;
	player = nullptr;
	playerStatistic = nullptr;
	statusBar = nullptr;
	shop = nullptr;

	instance = nullptr;

}

void GameManager::InitializeObject() {

	northBorder = GameObject::Instantiate("North border");
	Transform* northBorder_transform = northBorder->GetComponent<Transform>();
	northBorder_transform->scale = Vector2(MAP_SIZE.x, 1.0f);
	northBorder_transform->position = Vector2(0.0f, -MAP_SIZE.y / 2.0f);
	northBorder->AddComponent<BoxCollider>();

	southBorder = GameObject::Instantiate("South border");
	Transform* southBorder_transform = southBorder->GetComponent<Transform>();
	southBorder_transform->scale = Vector2(MAP_SIZE.x, 1.0f);
	southBorder_transform->position = Vector2(0.0f, MAP_SIZE.y / 2.0f);
	southBorder->AddComponent<BoxCollider>();

	westBorder = GameObject::Instantiate("West border");
	Transform* westBorder_transform = westBorder->GetComponent<Transform>();
	westBorder_transform->scale = Vector2(1.0f, MAP_SIZE.y);
	westBorder_transform->position = Vector2(-MAP_SIZE.x / 2.0f, 0.0f);
	westBorder->AddComponent<BoxCollider>();

	eastBorder = GameObject::Instantiate("East border");
	Transform* eastBorder_transform = eastBorder->GetComponent<Transform>();
	eastBorder_transform->scale = Vector2(1.0f, MAP_SIZE.y);
	eastBorder_transform->position = Vector2(MAP_SIZE.x / 2.0f, 0.0f);
	eastBorder->AddComponent<BoxCollider>();

	// Map background
	background = GameObject::Instantiate("Background", Layer::Background);
	Image* background_image = background->AddComponent<Image>();
	background_image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_Background), true);
	background_image->showOnScreen = false;
	background->GetComponent<Transform>()->position = Vector2::zero;
	background->Render = [background_image]() {
		background_image->Render();
		};

	// Player
	player = GameObject::Instantiate<Player>("Player", Layer::Player);
	GameCore::LetCameraFocus(Player::Instance());
	playerStatistic = new PlayerStatistic;
	statusBar = GameObject::Instantiate<StatusBar>("Status Bar", Layer::GUI);
	shop = GameObject::Instantiate<Shop>("Shop", Layer::GUI);

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

		Zombie* zombie = GameObject::Instantiate<Zombie>();
		zombie->SetIndex(zombieIndex);
		zombie->transform->position = spawnPositionList[i];

	}

}

void GameManager::Update() {

	// Update game object

	GameObject::CleanUpDeleted();

	GameObject::UpdateAll();

	WaveManager::Instance()->Update();

}

GameManager* GameManager::Instance() { return instance; }