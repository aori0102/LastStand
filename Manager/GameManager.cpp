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
#include <DeathMessage.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <HotBar.h>
#include <HotBarUI.h>
#include <Inventory.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Menu.h>
#include <PauseMenu.h>
#include <PhysicsManager.h>
#include <Player.h>
#include <PlayerStatistic.h>
#include <RenderManager.h>
#include <SettingsUI.h>
#include <Shop.h>
#include <StatusBar.h>
#include <Texture.h>
#include <Tutorial.h>
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

	std::cout << "[GameManager] Initializing Game Objects..." << std::endl;

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

	GameObject::Instantiate<Menu>("Game Menu");
	
	GameObject::Instantiate<Player>("Player", Layer::Player);
	Player::Instance()->Disable();
	GameCore::LetCameraFocus(Player::Instance());

	GameObject::Instantiate<Shop>("Shop", Layer::GUI);
	Shop::Instance()->Disable();

	GameObject::Instantiate<HotBar>("Hot Bar");

	GameObject::Instantiate<Inventory>("Inventory");

	GameObject::Instantiate<PlayerStatistic>("Player Statistic");

	GameObject::Instantiate<StatusBar>("Status Bar", Layer::GUI);
	StatusBar::Instance()->Disable();

	GameObject::Instantiate<SettingsUI>("Settings UI", Layer::Menu);
	SettingsUI::Instance()->Disable();

	GameObject::Instantiate<PauseMenu>("Pause menu", Layer::Menu);
	PauseMenu::Instance()->Disable();

	GameObject::Instantiate<DeathMessage>("Death Message", Layer::Menu);
	DeathMessage::Instance()->Disable();

	GameObject::Instantiate<Tutorial>("Tutorial", Layer::Menu);
	Tutorial::Instance()->Disable();

	std::cout << "[GameManager] Game Objects Initialized!" << std::endl;

}

void GameManager::EnableSceneObject() {

	switch (currentScene) {

	case SceneIndex::InGame:

		waveManager->Enable();

		Player::Instance()->Enable();
		StatusBar::Instance()->Enable();
		background->Enable();
		northBorder->Enable();
		southBorder->Enable();
		westBorder->Enable();
		eastBorder->Enable();
		HotBarUI::Instance()->Enable();

		break;

	case SceneIndex::InGamePaused:

		waveManager->Enable();

		Player::Instance()->Enable();
		StatusBar::Instance()->Enable();
		background->Enable();
		northBorder->Enable();
		southBorder->Enable();
		westBorder->Enable();
		eastBorder->Enable();

		PauseMenu::Instance()->Enable();

		break;

	case SceneIndex::MainMenu:

		Menu::Instance()->Enable();

		break;

	case SceneIndex::Settings:

		SettingsUI::Instance()->Enable();

		break;

	case SceneIndex::GameOver:

		background->Enable();
		DeathMessage::Instance()->Enable();

		break;

	case SceneIndex::Tutorial:

		Tutorial::Instance()->Enable();

		break;

	}

}

void GameManager::DisableSceneObject() {

	switch (currentScene) {

	case SceneIndex::InGame:

		waveManager->Disable();

		Player::Instance()->Disable();
		StatusBar::Instance()->Disable();
		background->Disable();
		northBorder->Disable();
		southBorder->Disable();
		westBorder->Disable();
		eastBorder->Disable();
		Shop::Instance()->Disable();
		HotBarUI::Instance()->Disable();

		break;

	case SceneIndex::InGamePaused:

		waveManager->Disable();

		Player::Instance()->Disable();
		StatusBar::Instance()->Disable();
		background->Disable();
		northBorder->Disable();
		southBorder->Disable();
		westBorder->Disable();
		eastBorder->Disable();

		PauseMenu::Instance()->Disable();

		break;

	case SceneIndex::MainMenu:

		Menu::Instance()->Disable();

		break;

	case SceneIndex::Settings:

		SettingsUI::Instance()->Disable();

		break;

	case SceneIndex::GameOver:

		background->Disable();
		DeathMessage::Instance()->Disable();

		break;

	case SceneIndex::Tutorial:

		Tutorial::Instance()->Disable();

		break;

	}

}

void GameManager::SaveGame() {

	GameCore::SaveConfig();
	PlayerStatistic::Instance()->SaveData();
	Inventory::Instance()->SaveInventory();
	Player::Instance()->SaveData();

}

void GameManager::LoadGame() {

	GameCore::LoadConfig();
	PlayerStatistic::Instance()->LoadData();
	Inventory::Instance()->LoadInventory();
	Player::Instance()->LoadData();

}

GameManager::GameManager() {

	if (instance)
		throw std::exception("Only one GameManager is allowed");

	instance = this;

	gameRunning = true;

	currentScene = SceneIndex::MainMenu;
	previousScene = SceneIndex::MainMenu;

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

	LoadGame();

}

GameManager::~GameManager() {
	
	SaveGame();

	background = nullptr;
	northBorder = nullptr;
	southBorder = nullptr;
	westBorder = nullptr;
	eastBorder = nullptr;

	std::cout << "Flushing game objects...\n";
	GameObject::DropNuke();

	std::cout << "[GameManager] Unloading Datamanager..." << std::endl;
	delete dataManager;
	dataManager = nullptr;

	std::cout << "[GameManager] Unloading UIEventManager..." << std::endl;
	delete uiEventManager;
	uiEventManager = nullptr;

	std::cout << "[GameManager] Unloading MediaManager..." << std::endl;
	delete mediaManager;
	mediaManager = nullptr;

	std::cout << "[GameManager] Unloading AudioManager..." << std::endl;
	delete audioManager;
	audioManager = nullptr;

	std::cout << "[GameManager] Unloading RenderManager..." << std::endl;
	delete renderManager;
	renderManager = nullptr;

	std::cout << "[GameManager] Unloading PhysicsManager..." << std::endl;
	delete physicsManager;
	physicsManager = nullptr;

	std::cout << "[GameManager] Unloading AnimationManager..." << std::endl;
	delete animationManager;
	animationManager = nullptr;

	std::cout << "[GameManager] Unloading ItemManager..." << std::endl;
	delete itemManager;
	itemManager = nullptr;

	std::cout << "[GameManager] Unloading WaveManager..." << std::endl;
	delete waveManager;
	waveManager = nullptr;

	instance = nullptr;

}

void GameManager::ReportDead(GameObject* gameObject) {

	if (gameObject->IsA<Player>()) {

		DeathMessage::Instance()->UpdateMessage();

		ResetGameData();

		FreezeGame();
		SwitchScene(SceneIndex::GameOver);

	} else if (gameObject->IsA<Zombie>()) {

		Zombie* zombie = gameObject->As<Zombie>();

		// Point, xp, money, etc
		PlayerStatistic::Instance()->AddMoney(10);
		PlayerStatistic::Instance()->AddEXP(zombie->GetExp());

		WaveManager::Instance()->RemoveZombie(zombie);

	}

}

void GameManager::Update() {

	if (GameCore::GetKeyState(SDLK_t).started)
		SwitchScene(SceneIndex::Tutorial);
		
	// Freeze game
	if (GameCore::GetKeyState(SDLK_ESCAPE).started
		&& (currentScene == SceneIndex::InGamePaused || currentScene == SceneIndex::InGame)) {

		gameRunning = !gameRunning;
		if (gameRunning)
			SwitchScene(SceneIndex::InGame);
		else
			SwitchScene(SceneIndex::InGamePaused);

	}

	// Update game object

	GameObject::CleanUpDeleted();

	GameObject::StartAll();
	GameObject::UpdateAll();

	WaveManager::Instance()->Update();

}

void GameManager::SwitchScene(SceneIndex targetScene) {

	if (currentScene == targetScene)
		return;

	DisableSceneObject();

	previousScene = currentScene;
	currentScene = targetScene;

	EnableSceneObject();

}

void GameManager::SwitchToPreviousScene() {

	SwitchScene(previousScene);

}

void GameManager::FreezeGame() {

	gameRunning = false;

}

void GameManager::UnfreezeGame() {

	gameRunning = true;

}

void GameManager::ResetGameData() {

	Firearm::ResetAttribute();
	waveManager->ResetStat();
	Shop::Instance()->ResetData();
	DataManager::Instance()->ResetPlayerData();
	Player::Instance()->Reset();
	PlayerStatistic::Instance()->ResetStat();
	HotBar::Instance()->Reset();
	Inventory::Instance()->ResetInventory();

}

bool GameManager::GameRunning() const { return gameRunning; }

GameManager* GameManager::Instance() { return instance; }