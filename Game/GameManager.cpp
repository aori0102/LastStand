#include <GameManager.h>
#include <GameComponent.h>
#include <Enemy.h>
#include <Player.h>
#include <string>
#include <Game.h>

Player* GameManager::player = nullptr;
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
	infoBackground_image->backgroundColor = Color(0, 0, 0, 125);
	infoBackground_image->showOnScreen = true;
	Transform* infoBackground_transform = infoBackground->GetComponent<Transform>();
	infoBackground_transform->position = Vector2::zero;
	infoBackground_transform->scale = INFO_BOARD_SCALE;

	// Money label
	moneyLabel = new GameObject;
	Text* moneyLabel_text = moneyLabel->AddComponent<Text>();
	moneyLabel_text->LoadText(MONEY_LABEL_TEXT, Color::WHITE, MONEY_LABEL_SIZE);
	Transform* moneyLabel_transform = moneyLabel->GetComponent<Transform>();
	moneyLabel_transform->position = Vector2::zero;
	moneyLabel_text->showOnScreen = true;

	// Money text
	moneyText = new GameObject;
	Text* moneyText_text = moneyText->AddComponent<Text>();
	moneyText_text->LoadText(to_string(money), Color::WHITE, MONEY_LABEL_SIZE);
	moneyText->GetComponent<Transform>()->position = Vector2(
		moneyLabel_transform->position.x + moneyLabel_transform->scale.x,
		0.0f
	);
	moneyText_text->showOnScreen = true;

	// Experience background
	experienceBackground = new GameObject;
	Image* experienceBackground_image = experienceBackground->AddComponent<Image>();
	experienceBackground_image->backgroundColor = Color(0, 0, 0, 125);
	experienceBackground_image->showOnScreen = true;
	Transform* experienceBackground_transform = experienceBackground->GetComponent<Transform>();
	experienceBackground_transform->position = Vector2(Game::GetResolution().x / 2.0f, 5.0f);
	experienceBackground_transform->scale = EXPERIENCE_BAR_SCALE;

	// Experience bar
	experienceBar = new GameObject;
	Image* experienceBar_image = experienceBar->AddComponent<Image>();
	experienceBar_image->backgroundColor = Color::YELLOW;
	experienceBar_image->showOnScreen = true;
	experienceBar_image->imageFill = ImageFill::Horizontal;
	experienceBar_image->fillAmount = 0.0f;
	Transform* experienceBar_transform = experienceBar->GetComponent<Transform>();
	experienceBar_transform->position = Vector2(Game::GetResolution().x / 2.0f, 5.0f);
	experienceBar_transform->scale = EXPERIENCE_BAR_SCALE;

	// Level label
	levelLabel = new GameObject;
	Text* levelLabel_text = levelLabel->AddComponent<Text>();
	string levelText = LEVEL_PREFIX + to_string(level);
	levelLabel_text->LoadText(levelText, Color::WHITE, LEVEL_LABEL_SIZE);
	levelLabel->GetComponent<Transform>()->position = Vector2(
		Game::GetResolution().x - levelLabel->GetComponent<Transform>()->scale.x,
		0.0f
	);
	levelLabel_text->showOnScreen = true;

	// Level label
	expLabel = new GameObject;
	Text* expLabel_text = expLabel->AddComponent<Text>();
	string expText = to_string(experience) + EXP_SLASH + to_string(expToNextLvl);
	expLabel_text->LoadText(expText, Color::WHITE, EXP_LABEL_SIZE);
	expLabel->GetComponent<Transform>()->position = Vector2(
		Game::GetResolution().x / 2.0f,
		50.0f
	);
	expLabel_text->showOnScreen = true;

}

void GameManager::ReportDead(GameObject* gameObject) {

	cout << "Hello\n";

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
	moneyText->GetComponent<Transform>()->position = Vector2(
		moneyLabel->GetComponent<Transform>()->position.x + moneyLabel->GetComponent<Transform>()->scale.x,
		0.0f
	);
	moneyText->GetComponent<Text>()->Render();
	experienceBackground->GetComponent<Image>()->Render();
	cout << experienceBar->GetComponent<Image>()->fillAmount << endl;
	experienceBar->GetComponent<Image>()->Render();
	levelLabel->GetComponent<Text>()->Render();
	expLabel->GetComponent<Text>()->Render();

}