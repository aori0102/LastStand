/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <DeathMessage.h>

#include <GameManager.h>
#include <MediaManager.h>
#include <PlayerStatistic.h>
#include <Texture.h>
#include <WaveManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

DeathMessage* DeathMessage::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void DeathMessage::InitializeUI() {

	/// ------------------
	/// FRAME
	/// ------------------
	GameObject* frame = GameObject::Instantiate("Death Message Frame", Layer::Menu);
	Image* frame_image = frame->AddComponent<Image>();
	frame_image->showOnScreen = true;
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_DeathMessageFrame), true);
	frame->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::Frame), frame->transform->scale
	);
	frame->Render = [frame_image]() {
		frame_image->Render();
		};
	uiElementMap[UIElementIndex::Frame] = frame;

	/// ------------------
	/// WAVE SURVIVED MESSAGE VALUE
	/// ------------------
	GameObject* waveSurvivedValue = GameObject::Instantiate("Wave Survived Value", Layer::Menu);
	Text* waveSurvivedValue_text = waveSurvivedValue->AddComponent<Text>();
	waveSurvivedValue_text->showOnScreen = true;
	waveSurvivedValue_text->LoadText("", Color::WHITE, STAT_LABEL_FONT_SIZE);
	waveSurvivedValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::WaveSurvivedValue), waveSurvivedValue->transform->scale
	);
	waveSurvivedValue->Render = [waveSurvivedValue_text]() {
		waveSurvivedValue_text->Render();
		};
	uiElementMap[UIElementIndex::WaveSurvivedValue] = waveSurvivedValue;

	/// ------------------
	/// WAVE SURVIVED MESSAGE LABEL
	/// ------------------
	GameObject* waveSurvivedLabel = GameObject::Instantiate("Wave Survived Label", Layer::Menu);
	Text* waveSurvivedLabel_text = waveSurvivedLabel->AddComponent<Text>();
	waveSurvivedLabel_text->showOnScreen = true;
	waveSurvivedLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::WaveSurvivedLabel), Color::WHITE, STAT_LABEL_FONT_SIZE);
	Align::Left(waveSurvivedLabel->transform, waveSurvivedValue->transform);
	Align::MiddleVertically(waveSurvivedLabel->transform, waveSurvivedValue->transform);
	waveSurvivedLabel->transform->position -= waveSurvivedLabel->transform->scale;
	waveSurvivedLabel->transform->position.x -= STAT_LABEL_OFFSET;
	waveSurvivedLabel->Render = [waveSurvivedLabel_text]() {
		waveSurvivedLabel_text->Render();
		};
	uiElementMap[UIElementIndex::WaveSurvivedLabel] = waveSurvivedLabel;

	/// ------------------
	/// ZOMBIE KILLED MESSAGE VALUE
	/// ------------------
	GameObject* zombieKilledValue = GameObject::Instantiate("Zombie Killed Value", Layer::Menu);
	Text* zombieKilledValue_text = zombieKilledValue->AddComponent<Text>();
	zombieKilledValue_text->showOnScreen = true;
	zombieKilledValue_text->LoadText("", Color::WHITE, STAT_LABEL_FONT_SIZE);
	zombieKilledValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ZombieKilledValue), zombieKilledValue->transform->scale
	);
	zombieKilledValue->Render = [zombieKilledValue_text]() {
		zombieKilledValue_text->Render();
		};
	uiElementMap[UIElementIndex::ZombieKilledValue] = zombieKilledValue;

	/// ------------------
	/// ZOMBIE KILLED MESSAGE LABEL
	/// ------------------
	GameObject* zombieKilledLabel = GameObject::Instantiate("Zombie Killed Label", Layer::Menu);
	Text* zombieKilledLabel_text = zombieKilledLabel->AddComponent<Text>();
	zombieKilledLabel_text->showOnScreen = true;
	zombieKilledLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::ZombieKilledLabel), Color::WHITE, STAT_LABEL_FONT_SIZE);
	Align::Left(zombieKilledLabel->transform, zombieKilledValue->transform);
	Align::MiddleVertically(zombieKilledLabel->transform, zombieKilledValue->transform);
	zombieKilledLabel->transform->position -= zombieKilledLabel->transform->scale;
	zombieKilledLabel->transform->position.x -= STAT_LABEL_OFFSET;
	zombieKilledLabel->Render = [zombieKilledLabel_text]() {
		zombieKilledLabel_text->Render();
		};
	uiElementMap[UIElementIndex::ZombieKilledLabel] = zombieKilledLabel;

	/// ------------------
	/// POINTS MESSAGE VALUE
	/// ------------------
	GameObject* pointsValue = GameObject::Instantiate("Points Value", Layer::Menu);
	Text* pointsValue_text = pointsValue->AddComponent<Text>();
	pointsValue_text->showOnScreen = true;
	pointsValue_text->LoadText("", Color::WHITE, STAT_LABEL_FONT_SIZE);
	pointsValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::PointsValue), pointsValue->transform->scale
	);
	pointsValue->Render = [pointsValue_text]() {
		pointsValue_text->Render();
		};
	uiElementMap[UIElementIndex::PointsValue] = pointsValue;

	/// ------------------
	/// POINTS MESSAGE LABEL
	/// ------------------
	GameObject* pointsLabel = GameObject::Instantiate("Points Label", Layer::Menu);
	Text* pointsLabel_text = pointsLabel->AddComponent<Text>();
	pointsLabel_text->showOnScreen = true;
	pointsLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::PointsLabel), Color::WHITE, STAT_LABEL_FONT_SIZE);
	Align::Left(pointsLabel->transform, pointsValue->transform);
	Align::MiddleVertically(pointsLabel->transform, pointsValue->transform);
	pointsLabel->transform->position -= pointsLabel->transform->scale;
	pointsLabel->transform->position.x -= STAT_LABEL_OFFSET;
	pointsLabel->Render = [pointsLabel_text]() {
		pointsLabel_text->Render();
		};
	uiElementMap[UIElementIndex::PointsLabel] = pointsLabel;

	/// ------------------
	/// DAMAGE DEALT MESSAGE VALUE
	/// ------------------
	GameObject* damageDealtValue = GameObject::Instantiate("Damage Dealt Value", Layer::Menu);
	Text* damageDealtValue_text = damageDealtValue->AddComponent<Text>();
	damageDealtValue_text->showOnScreen = true;
	damageDealtValue_text->LoadText("", Color::WHITE, STAT_LABEL_FONT_SIZE);
	damageDealtValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::DamageDealtValue), damageDealtValue->transform->scale
	);
	damageDealtValue->Render = [damageDealtValue_text]() {
		damageDealtValue_text->Render();
		};
	uiElementMap[UIElementIndex::DamageDealtValue] = damageDealtValue;

	/// ------------------
	/// DAMAGE DEALT MESSAGE LABEL
	/// ------------------
	GameObject* damageDealtLabel = GameObject::Instantiate("Damage Dealt Label", Layer::Menu);
	Text* damageDealtLabel_text = damageDealtLabel->AddComponent<Text>();
	damageDealtLabel_text->showOnScreen = true;
	damageDealtLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::DamageDealtLabel), Color::WHITE, STAT_LABEL_FONT_SIZE);
	Align::Left(damageDealtLabel->transform, damageDealtValue->transform);
	Align::MiddleVertically(damageDealtLabel->transform, damageDealtValue->transform);
	damageDealtLabel->transform->position -= damageDealtLabel->transform->scale;
	damageDealtLabel->transform->position.x -= STAT_LABEL_OFFSET;
	damageDealtLabel->Render = [damageDealtLabel_text]() {
		damageDealtLabel_text->Render();
		};
	uiElementMap[UIElementIndex::DamageDealtLabel] = damageDealtLabel;

	/// ------------------
	/// MAIN MENU BUTTON
	/// ------------------
	GameObject* mainMenuButton = GameObject::Instantiate("Death Message Main Menu Button", Layer::Menu);
	Image* mainMenuButton_image = mainMenuButton->AddComponent<Image>();
	mainMenuButton_image->showOnScreen = true;
	mainMenuButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_DeathMessageButton), true);
	Button* mainMenuButton_button = mainMenuButton->AddComponent<Button>();
	mainMenuButton_button->backgroundColor = Color::TRANSPARENT;
	mainMenuButton_button->OnClick = []() {
		GameManager::Instance()->SwitchScene(SceneIndex::MainMenu);
		GameManager::Instance()->FreezeGame();
		return true;
		};
	mainMenuButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::MainMenuButton), mainMenuButton->transform->scale
	);
	mainMenuButton->Render = [mainMenuButton_image]() {
		mainMenuButton_image->Render();
		};
	uiElementMap[UIElementIndex::MainMenuButton] = mainMenuButton;

	/// ------------------
	/// RETRY BUTTON
	/// ------------------
	GameObject* retryButton = GameObject::Instantiate("Death Message Retry Button", Layer::Menu);
	Image* retryButton_image = retryButton->AddComponent<Image>();
	retryButton_image->showOnScreen = true;
	retryButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_DeathMessageButton), true);
	Button* retryButton_button = retryButton->AddComponent<Button>();
	retryButton_button->backgroundColor = Color::TRANSPARENT;
	retryButton_button->OnClick = []() {
		GameManager::Instance()->SwitchScene(SceneIndex::InGame);
		GameManager::Instance()->UnfreezeGame();
		return true;
		};
	retryButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::RetryButton), retryButton->transform->scale
	);
	retryButton->Render = [retryButton_image]() {
		retryButton_image->Render();
		};
	uiElementMap[UIElementIndex::RetryButton] = retryButton;

	/// ------------------
	/// MAIN MENU BUTTON LABEL
	/// ------------------
	GameObject* mainMenuButtonLabel = GameObject::Instantiate("Main Menu Button Label", Layer::Menu);
	Text* mainMenuButtonLabel_text = mainMenuButtonLabel->AddComponent<Text>();
	mainMenuButtonLabel_text->showOnScreen = true;
	mainMenuButtonLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::MainMenuLabel), Color::WHITE, STAT_LABEL_FONT_SIZE);
	mainMenuButtonLabel->transform->position = mainMenuButton->transform->position;
	mainMenuButtonLabel->Render = [mainMenuButtonLabel_text]() {
		mainMenuButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::MainMenuLabel] = mainMenuButtonLabel;

	/// ------------------
	/// RETRY BUTTON LABEL
	/// ------------------
	GameObject* retryButtonLabel = GameObject::Instantiate("Retry Button Label", Layer::Menu);
	Text* retryButtonLabel_text = retryButtonLabel->AddComponent<Text>();
	retryButtonLabel_text->showOnScreen = true;
	retryButtonLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::RetryLabel), Color::WHITE, STAT_LABEL_FONT_SIZE);
	retryButtonLabel->transform->position = retryButton->transform->position;
	retryButtonLabel->Render = [retryButtonLabel_text]() {
		retryButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::RetryLabel] = retryButtonLabel;

}

void DeathMessage::Show() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

}

void DeathMessage::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

DeathMessage::DeathMessage() {

	if (instance)
		throw std::exception("DeathMessage can only have one instance!");

	instance = this;

	InitializeUI();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

DeathMessage::~DeathMessage() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	uiElementMap.clear();

	instance = nullptr;

}

void DeathMessage::UpdateMessage() {

	// Wave survived
	GameObject* waveSurvivedValue = uiElementMap.at(UIElementIndex::WaveSurvivedValue);
	waveSurvivedValue->GetComponent<Text>()->LoadText(
		std::to_string(WaveManager::Instance()->GetSurvivedWave()), Color::WHITE, STAT_LABEL_FONT_SIZE
	);
	waveSurvivedValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::WaveSurvivedValue), waveSurvivedValue->transform->scale
	);
	Align::MiddleVertically(uiElementMap.at(UIElementIndex::WaveSurvivedLabel)->transform, waveSurvivedValue->transform);

	// Zombie killed
	GameObject* zombieKilledValue = uiElementMap.at(UIElementIndex::ZombieKilledValue);
	zombieKilledValue->GetComponent<Text>()->LoadText(
		std::to_string(WaveManager::Instance()->GetTotalZombieKilled()), Color::WHITE, STAT_LABEL_FONT_SIZE
	);
	zombieKilledValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ZombieKilledValue), zombieKilledValue->transform->scale
	);
	Align::MiddleVertically(uiElementMap.at(UIElementIndex::ZombieKilledLabel)->transform, zombieKilledValue->transform);

	// Damage
	GameObject* damageDealtValue = uiElementMap.at(UIElementIndex::DamageDealtValue);
	damageDealtValue->GetComponent<Text>()->LoadText(
		std::to_string(static_cast<int>(PlayerStatistic::Instance()->GetDamage())), Color::WHITE, STAT_LABEL_FONT_SIZE
	);
	damageDealtValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::DamageDealtValue), damageDealtValue->transform->scale
	);
	Align::MiddleVertically(uiElementMap.at(UIElementIndex::DamageDealtLabel)->transform, damageDealtValue->transform);

	// Point
	GameObject* pointValue = uiElementMap.at(UIElementIndex::PointsValue);
	pointValue->GetComponent<Text>()->LoadText(
		std::to_string(PlayerStatistic::Instance()->GetTotalEXP()), Color::WHITE, STAT_LABEL_FONT_SIZE
	);
	pointValue->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::PointsValue), pointValue->transform->scale
	);
	Align::MiddleVertically(uiElementMap.at(UIElementIndex::PointsLabel)->transform, pointValue->transform);

}

DeathMessage* DeathMessage::Instance() { return instance; }