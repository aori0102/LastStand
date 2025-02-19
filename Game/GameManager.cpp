#include <GameManager.h>
#include <Enemy.h>
#include <Player.h>
#include <string>
#include <Game.h>
#include <Texture.h>
#include <GameComponent.h>
#include <Shop.h>

Player* GameManager::player = nullptr;
Shop* GameManager::shop = nullptr;
unordered_set<Enemy*> GameManager::enemySet = {};
int GameManager::money = 0;
int GameManager::experience = 0;
int GameManager::expToNextLvl = GameManager::BASE_EXP;
int GameManager::level = 0;
const int GameManager::BASE_EXP = 10;
const float GameManager::EXP_MULTIPLIER = 1.65f;
GameObject* GameManager::moneyLabel = nullptr;
GameObject* GameManager::moneyText = nullptr;
GameObject* GameManager::infoBackground = nullptr;
GameObject* GameManager::experienceBackground = nullptr;
GameObject* GameManager::experienceBar = nullptr;
GameObject* GameManager::levelLabel = nullptr;
GameObject* GameManager::expLabel = nullptr;

// UI settings
const Vector2 INFO_BOARD_SCALE = Vector2(300.0f, 225.0f);
const string MONEY_LABEL_TEXT = "Money: ";
const int MONEY_LABEL_SIZE = 20;
const int LEVEL_LABEL_SIZE = 18;
const int EXP_LABEL_SIZE = 18;
const string EXP_SLASH = " | ";
const string LEVEL_PREFIX = "Level: ";
const Vector2 EXPERIENCE_BAR_SCALE = Vector2(100.0f, 7.0f);

void GameManager::InitializeObject() {

	// UI components
	// Info background
	infoBackground = new GameObject;
	Image* infoBackground_image = infoBackground->AddComponent<Image>();
	Transform* infoBackground_transform = infoBackground->GetComponent<Transform>();
	infoBackground_image->backgroundColor = Color(0, 0, 0, 125);
	infoBackground_image->showOnScreen = true;
	infoBackground_transform->position = Vector2::zero;
	infoBackground_transform->scale = INFO_BOARD_SCALE;

	// Money label
	moneyLabel = new GameObject;
	Text* moneyLabel_text = moneyLabel->AddComponent<Text>();
	Transform* moneyLabel_transform = moneyLabel->GetComponent<Transform>();
	moneyLabel_text->LoadText(MONEY_LABEL_TEXT, Color::WHITE, MONEY_LABEL_SIZE);
	moneyLabel_text->showOnScreen = true;
	moneyLabel_transform->position = Vector2::zero;

	// Money text
	moneyText = new GameObject;
	Text* moneyText_text = moneyText->AddComponent<Text>();
	moneyText_text->LoadText(to_string(money), Color::WHITE, MONEY_LABEL_SIZE);
	moneyText_text->showOnScreen = true;
	moneyText->GetComponent<Transform>()->position = Vector2(
		moneyLabel_transform->position.x + moneyLabel_transform->scale.x,
		0.0f
	);

	// Experience background
	experienceBackground = new GameObject;
	Image* experienceBackground_image = experienceBackground->AddComponent<Image>();
	Transform* experienceBackground_transform = experienceBackground->GetComponent<Transform>();
	experienceBackground_image->backgroundColor = Color(0, 0, 0, 125);
	experienceBackground_image->showOnScreen = true;
	experienceBackground_transform->position = Vector2(Game::WindowResolution().x / 2.0f, 5.0f);
	experienceBackground_transform->scale = EXPERIENCE_BAR_SCALE;

	// Experience bar
	experienceBar = new GameObject;
	Image* experienceBar_image = experienceBar->AddComponent<Image>();
	Transform* experienceBar_transform = experienceBar->GetComponent<Transform>();
	experienceBar_image->backgroundColor = Color::YELLOW;
	experienceBar_image->showOnScreen = true;
	experienceBar_image->imageFill = ImageFill::Horizontal;
	experienceBar_image->fillAmount = 0.0f;
	experienceBar_transform->position = Vector2(Game::WindowResolution().x / 2.0f, 5.0f);
	experienceBar_transform->scale = EXPERIENCE_BAR_SCALE;

	// Level label
	levelLabel = new GameObject;
	Text* levelLabel_text = levelLabel->AddComponent<Text>();
	Transform* levelLabel_transform = levelLabel->GetComponent<Transform>();
	string levelText = LEVEL_PREFIX + to_string(level);
	levelLabel_text->LoadText(levelText, Color::WHITE, LEVEL_LABEL_SIZE);
	levelLabel_text->showOnScreen = true;
	levelLabel_transform->position = Vector2(
		Game::WindowResolution().x - levelLabel_transform->scale.x,
		0.0f
	);

	// Level label
	expLabel = new GameObject;
	Text* expLabel_text = expLabel->AddComponent<Text>();
	string expText = to_string(experience) + EXP_SLASH + to_string(expToNextLvl);
	expLabel_text->LoadText(expText, Color::WHITE, EXP_LABEL_SIZE);
	expLabel_text->showOnScreen = true;
	expLabel->GetComponent<Transform>()->position = Vector2(
		Game::WindowResolution().x / 2.0f,
		50.0f
	);

	// Player
	player = new Player;
	player->name = "Player";
	Game::LetCameraFocus(player);

	// Shop
	shop = new Shop(player);

	// Enemy
	Enemy* enemy1 = new Enemy(player);
	enemy1->GetComponent<Transform>()->position = Vector2(100.0f, 200.0f);
	Enemy* enemy2 = new Enemy(player);
	enemy2->GetComponent<Transform>()->position = Vector2(1000.0f, 200.0f);
	Enemy* enemy5 = new Enemy(player);
	enemy5->GetComponent<Transform>()->position = Vector2(1000.0f, 200.0f);
	Enemy* enemy6 = new Enemy(player);
	enemy6->GetComponent<Transform>()->position = Vector2(1000.0f, 200.0f);
	Enemy* enemy7 = new Enemy(player);
	enemy7->GetComponent<Transform>()->position = Vector2(1000.0f, 200.0f);
	Enemy* enemy3 = new Enemy(player);
	enemy3->GetComponent<Transform>()->position = Vector2(100.0f, 2000.0f);
	Enemy* enemy4 = new Enemy(player);
	enemy4->GetComponent<Transform>()->position = Vector2(725.0f, 415.0f);

}

void GameManager::ReportDead(GameObject* gameObject) {

	if (gameObject->IsA<Player>()) {

		// Game over

	} else if (gameObject->IsA<Enemy>()) {

		// Point, xp, money, etc
		money += 10;
		moneyText->GetComponent<Text>()->LoadText(to_string(money), Color::WHITE, MONEY_LABEL_SIZE);

		experience += 7;
		while (experience >= expToNextLvl) {

			experience -= expToNextLvl;
			level++;
			expToNextLvl = BASE_EXP * powf(EXP_MULTIPLIER, level);

		}
		experienceBar->GetComponent<Image>()->fillAmount = (float)experience / (float)expToNextLvl;
		string expText = to_string(experience) + EXP_SLASH + to_string(expToNextLvl);
		expLabel->GetComponent<Text>()->LoadText(expText, Color::WHITE, EXP_LABEL_SIZE);

	}

}

void GameManager::Update() {

	infoBackground->GetComponent<Image>()->Render();

	moneyLabel->GetComponent<Text>()->Render();

	Transform* moneyText_transform = moneyText->GetComponent<Transform>();
	moneyText_transform->position = Vector2(
		moneyLabel->GetComponent<Transform>()->scale.x,
		0.0f
	);
	moneyText->GetComponent<Text>()->Render();

	experienceBackground->GetComponent<Image>()->Render();

	experienceBar->GetComponent<Image>()->Render();

	levelLabel->GetComponent<Text>()->Render();

	expLabel->GetComponent<Text>()->Render();

}