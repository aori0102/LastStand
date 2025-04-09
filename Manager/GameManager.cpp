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
#include <DataManager.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Menu.h>
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

void GameManager::InitializeObject() {

	menu = GameObject::Instantiate<Menu>("Game Menu");

	northBorder = GameObject::Instantiate("North border");
	Transform* northBorder_transform = northBorder->GetComponent<Transform>();
	northBorder_transform->scale = Vector2(MAP_SIZE.x, 1.0f);
	northBorder_transform->position = Vector2(0.0f, -MAP_SIZE.y / 2.0f);
	northBorder->AddComponent<BoxCollider>();
	northBorder->Disable();

	southBorder = GameObject::Instantiate("South border");
	Transform* southBorder_transform = southBorder->GetComponent<Transform>();
	southBorder_transform->scale = Vector2(MAP_SIZE.x, 1.0f);
	southBorder_transform->position = Vector2(0.0f, MAP_SIZE.y / 2.0f);
	southBorder->AddComponent<BoxCollider>();
	southBorder->Disable();

	westBorder = GameObject::Instantiate("West border");
	Transform* westBorder_transform = westBorder->GetComponent<Transform>();
	westBorder_transform->scale = Vector2(1.0f, MAP_SIZE.y);
	westBorder_transform->position = Vector2(-MAP_SIZE.x / 2.0f, 0.0f);
	westBorder->AddComponent<BoxCollider>();
	westBorder->Disable();

	eastBorder = GameObject::Instantiate("East border");
	Transform* eastBorder_transform = eastBorder->GetComponent<Transform>();
	eastBorder_transform->scale = Vector2(1.0f, MAP_SIZE.y);
	eastBorder_transform->position = Vector2(MAP_SIZE.x / 2.0f, 0.0f);
	eastBorder->AddComponent<BoxCollider>();
	eastBorder->Disable();

	// Map background
	background = GameObject::Instantiate("Background", Layer::Background);
	Image* background_image = background->AddComponent<Image>();
	background_image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_Background), true);
	background_image->showOnScreen = false;
	background->GetComponent<Transform>()->position = Vector2::zero;
	background->Render = [background_image]() {
		background_image->Render();
		};
	background->Disable();

	// Player
	player = GameObject::Instantiate<Player>("Player", Layer::Player);
	player->Disable();
	GameCore::LetCameraFocus(Player::Instance());
	playerStatistic = new PlayerStatistic;
	statusBar = GameObject::Instantiate<StatusBar>("Status Bar", Layer::GUI);
	statusBar->Disable();
	shop = GameObject::Instantiate<Shop>("Shop", Layer::GUI);

}

void GameManager::EnableSceneObject() {

	switch (currentScene) {

	case SceneIndex::Game:

		waveManager->Enable();

		player->Enable();
		statusBar->Enable();
		background->Enable();
		northBorder->Enable();
		southBorder->Enable();
		westBorder->Enable();
		eastBorder->Enable();

		break;

	case SceneIndex::MainMenu:

		menu->Enable();

		break;

	}

}

void GameManager::DisableSceneObject() {

	switch (currentScene) {

	case SceneIndex::Game:

		waveManager->Disable();

		player->Disable();
		statusBar->Disable();
		background->Disable();
		northBorder->Disable();
		southBorder->Disable();
		westBorder->Disable();
		eastBorder->Disable();

		break;

	case SceneIndex::MainMenu:

		menu->Disable();

		break;

	}

}

GameManager::GameManager() {

	if (instance)
		throw std::exception("Only one GameManager is allowed");

	instance = this;

	currentScene = SceneIndex::MainMenu;

	std::cout << "Initializing DataManager..." << std::endl;
	dataManager = new DataManager;

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
	waveManager->Disable();

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

	delete dataManager;
	dataManager = nullptr;

	delete uiEventManager;
	uiEventManager = nullptr;

	delete mediaManager;
	mediaManager = nullptr;

	delete audioManager;
	audioManager = nullptr;

	delete renderManager;
	renderManager = nullptr;

	delete physicsManager;
	physicsManager = nullptr;

	delete animationManager;
	animationManager = nullptr;

	delete itemManager;
	itemManager = nullptr;

	delete waveManager;
	waveManager = nullptr;

	instance = nullptr;

}

void GameManager::ReportDead(GameObject* gameObject) {

	if (gameObject->IsA<Player>()) {

		throw std::exception("You're dead. You fucking suck. Also, say goodbye to your PC :)");

	} else if (gameObject->IsA<Zombie>()) {

		// Point, xp, money, etc
		PlayerStatistic::Instance()->AddMoney(10);
		PlayerStatistic::Instance()->AddEXP(gameObject->As<Zombie>()->GetExp());

		WaveManager::Instance()->RemoveZombie();

		GameObject::Destroy(gameObject);

	}

}

void GameManager::SpawnZombie(int amount, ZombieIndex zombieIndex) {

	std::vector<Vector2> spawnPositionList = SPAWN_POSITION_LIST;
	Algorithm::Shuffle(spawnPositionList);

	for (int i = 0; i < amount; i++) {

		Zombie* zombie = GameObject::Instantiate<Zombie>("Zombie", Layer::Zombie);
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

void GameManager::SwitchScene(SceneIndex targetScene) {

	if (currentScene == targetScene)
		return;

	DisableSceneObject();

	currentScene = targetScene;

	EnableSceneObject();

}

GameManager* GameManager::Instance() { return instance; }