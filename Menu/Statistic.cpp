#include <Statistic.h>

#include <iomanip>
#include <sstream>

#include <DataManager.h>
#include <GameManager.h>
#include <MediaManager.h>
#include <Texture.h>

Statistic* Statistic::instance = nullptr;

void Statistic::InitializeUI() {

	/// ------------------
	/// TITLE
	/// ------------------
	GameObject* title = GameObject::Instantiate("Statistic Title", Layer::Menu);
	Text* title_text = title->AddComponent<Text>();
	title_text->showOnScreen = true;
	title_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::Title), Color::WHITE, TITLE_FONT_SIZE);
	Align::Top(title->transform);
	Align::MiddleHorizontally(title->transform);
	title->transform->position += UI_POSITION_MAP.at(UIElementIndex::Title);
	title->Render = [title_text]() {
		title_text->Render();
		};
	uiElementMap[UIElementIndex::Title] = title;

	/// ------------------
	/// RETURN BUTTON
	/// ------------------
	GameObject* returnButton = GameObject::Instantiate("Statistic Return Button", Layer::Menu);
	Image* returnButton_image = returnButton->AddComponent<Image>();
	returnButton_image->showOnScreen = true;
	returnButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_ReturnButton), true);
	Button* returnButton_button = returnButton->AddComponent<Button>();
	returnButton_button->backgroundColor = Color::TRANSPARENT;
	returnButton_button->OnClick = []() {
		GameManager::Instance()->SwitchToPreviousScene();
		return true;
		};
	returnButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ReturnButton), returnButton->transform->scale
	);
	returnButton->Render = [returnButton_image]() {
		returnButton_image->Render();
		};
	uiElementMap[UIElementIndex::ReturnButton] = returnButton;

	/// ------------------
	/// RETURN LABEL
	/// ------------------
	GameObject* returnLabel = GameObject::Instantiate("Statistic Return Button Label", Layer::Menu);
	Text* returnLabel_text = returnLabel->AddComponent<Text>();
	returnLabel_text->showOnScreen = true;
	returnLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::ReturnLabel), Color::WHITE, RETURN_LABEL_FONT_SIZE);
	returnLabel->transform->position = returnButton->transform->position;
	returnLabel->Render = [returnLabel_text]() {
		returnLabel_text->Render();
		};
	uiElementMap[UIElementIndex::ReturnLabel] = returnLabel;

	/// ------------------
	/// ZOMBIE KILLED LABEL
	/// ------------------
	GameObject* zombieKilledLabel = GameObject::Instantiate("Statistic Zombie Killed Label", Layer::Menu);
	Text* zombieKilledLabel_text = zombieKilledLabel->AddComponent<Text>();
	zombieKilledLabel_text->showOnScreen = true;
	zombieKilledLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::ZombieKilledLabel), Color::WHITE, RETURN_LABEL_FONT_SIZE);
	zombieKilledLabel->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ZombieKilledLabel), zombieKilledLabel->transform->scale
	);
	zombieKilledLabel->Render = [zombieKilledLabel_text]() {
		zombieKilledLabel_text->Render();
		};
	uiElementMap[UIElementIndex::ZombieKilledLabel] = zombieKilledLabel;

	/// ------------------
	/// ZOMBIE KILLED AMOUNT
	/// ------------------
	GameObject* zombieKilledAmount = GameObject::Instantiate("Statistic Zombie Killed Amount Label", Layer::Menu);
	Text* zombieKilledAmount_text = zombieKilledAmount->AddComponent<Text>();
	zombieKilledAmount_text->showOnScreen = true;
	zombieKilledAmount_text->LoadText("", Color::WHITE, RETURN_LABEL_FONT_SIZE);
	zombieKilledAmount->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ZombieKilledAmount), zombieKilledAmount->transform->scale
	);
	zombieKilledAmount->Render = [zombieKilledAmount_text]() {
		zombieKilledAmount_text->Render();
		};
	uiElementMap[UIElementIndex::ZombieKilledAmount] = zombieKilledAmount;

	/// ------------------
	/// WAVE SURVIVED LABEL
	/// ------------------
	GameObject* waveSurvivedLabel = GameObject::Instantiate("Statistic Wave Survived Label", Layer::Menu);
	Text* waveSurvivedLabel_text = waveSurvivedLabel->AddComponent<Text>();
	waveSurvivedLabel_text->showOnScreen = true;
	waveSurvivedLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::WaveSurvivedLabel), Color::WHITE, RETURN_LABEL_FONT_SIZE);
	waveSurvivedLabel->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::WaveSurvivedLabel), waveSurvivedLabel->transform->scale
	);
	waveSurvivedLabel->Render = [waveSurvivedLabel_text]() {
		waveSurvivedLabel_text->Render();
		};
	uiElementMap[UIElementIndex::WaveSurvivedLabel] = waveSurvivedLabel;

	/// ------------------
	/// WAVE SURVIVED AMOUNT
	/// ------------------
	GameObject* waveSurvivedAmount = GameObject::Instantiate("Statistic Wave Survived Amount Label", Layer::Menu);
	Text* waveSurvivedAmount_text = waveSurvivedAmount->AddComponent<Text>();
	waveSurvivedAmount_text->showOnScreen = true;
	waveSurvivedAmount_text->LoadText("", Color::WHITE, RETURN_LABEL_FONT_SIZE);
	waveSurvivedAmount->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::WaveSurvivedAmount), waveSurvivedAmount->transform->scale
	);
	waveSurvivedAmount->Render = [waveSurvivedAmount_text]() {
		waveSurvivedAmount_text->Render();
		};
	uiElementMap[UIElementIndex::WaveSurvivedAmount] = waveSurvivedAmount;

	/// ------------------
	/// DAMAGE DEALT LABEL
	/// ------------------
	GameObject* damageDealtLabel = GameObject::Instantiate("Statistic Damage Dealt Label", Layer::Menu);
	Text* damageDealtLabel_text = damageDealtLabel->AddComponent<Text>();
	damageDealtLabel_text->showOnScreen = true;
	damageDealtLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::DamageDealtLabel), Color::WHITE, RETURN_LABEL_FONT_SIZE);
	damageDealtLabel->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::DamageDealtLabel), damageDealtLabel->transform->scale
	);
	damageDealtLabel->Render = [damageDealtLabel_text]() {
		damageDealtLabel_text->Render();
		};
	uiElementMap[UIElementIndex::DamageDealtLabel] = damageDealtLabel;

	/// ------------------
	/// DAMAGE DEALT AMOUNT
	/// ------------------
	GameObject* damageDealtAmount = GameObject::Instantiate("Statistic Damage Dealt Amount Label", Layer::Menu);
	Text* damageDealtAmount_text = damageDealtAmount->AddComponent<Text>();
	damageDealtAmount_text->showOnScreen = true;
	damageDealtAmount_text->LoadText("", Color::WHITE, RETURN_LABEL_FONT_SIZE);
	damageDealtAmount->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::DamageDealtAmount), damageDealtAmount->transform->scale
	);
	damageDealtAmount->Render = [damageDealtAmount_text]() {
		damageDealtAmount_text->Render();
		};
	uiElementMap[UIElementIndex::DamageDealtAmount] = damageDealtAmount;

}

void Statistic::Show(){

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

}

void Statistic::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

Statistic::Statistic() {

	if (instance)
		throw std::exception("Statistic can only have one instance!");

	InitializeUI();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

	instance = this;

}

Statistic::~Statistic() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	instance = nullptr;

}

void Statistic::UpdateZombie(int amount) {

	GameObject* zombieAmount = uiElementMap.at(UIElementIndex::ZombieKilledAmount);
	zombieAmount->GetComponent<Text>()->LoadText(
		std::to_string(amount), Color::WHITE, STAT_FONT_SIZE
	);
	zombieAmount->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ZombieKilledAmount), zombieAmount->transform->scale
		);

}

void Statistic::UpdateDamage(float amount) {

	GameObject* damageDealt = uiElementMap.at(UIElementIndex::DamageDealtAmount);
	std::stringstream ss;
	ss << std::fixed << std::setprecision(STAT_DECIMAL) << amount;
	damageDealt->GetComponent<Text>()->LoadText(
		ss.str(), Color::WHITE, STAT_FONT_SIZE
	);
	damageDealt->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::DamageDealtAmount), damageDealt->transform->scale
	);

}

void Statistic::UpdateWave(int amount) {

	GameObject* waveAmount = uiElementMap.at(UIElementIndex::WaveSurvivedAmount);
	waveAmount->GetComponent<Text>()->LoadText(
		std::to_string(amount), Color::WHITE, STAT_FONT_SIZE
	);
	waveAmount->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::WaveSurvivedAmount), waveAmount->transform->scale
	);

}

void Statistic::Start() {

	PlayerSaveData* data = DataManager::Instance()->playerSaveData;

	UpdateZombie(data->mostZombieKilled);
	UpdateWave(data->mostWaveSurvived);
	UpdateDamage(data->mostDamageDealt);

}

Statistic* Statistic::Instance() { return instance; }