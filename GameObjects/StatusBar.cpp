/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <StatusBar.h>

#include <string>

#include <MediaManager.h>
#include <PlayerStatistic.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

StatusBar* StatusBar::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void StatusBar::InitializeUI() {

	// --- FRAME ---
	GameObject* frame = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::Frame), Layer::Menu);
	Image* frame_image = frame->AddComponent<Image>();
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_Frame), true);
	frame_image->showOnScreen = true;
	frame->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Frame),
		frame->transform->scale
	);
	frame->Render = [frame_image]() {
		frame_image->Render();
		};
	uiElementMap[UIElementIndex::Frame] = frame;

	// --- LEVEL FRAME ---
	GameObject* levelFrame = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::LevelFrame), Layer::Menu);
	Image* levelFrame_image = levelFrame->AddComponent<Image>();
	levelFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_LevelFrame), true);
	levelFrame_image->showOnScreen = true;
	levelFrame->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::LevelFrame),
		levelFrame->transform->scale
	);
	levelFrame->Render = [levelFrame_image]() {
		levelFrame_image->Render();
		};
	uiElementMap[UIElementIndex::LevelFrame] = levelFrame;

	// --- HEALTH BAR BACKGROUND ---
	GameObject* healthBarBackground = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::HealthBarBackground), Layer::Menu);
	Image* healthBarBackground_image = healthBarBackground->AddComponent<Image>();
	healthBarBackground_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_BarBackground), true);
	healthBarBackground_image->showOnScreen = true;
	healthBarBackground->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::HealthBarBackground),
		healthBarBackground->transform->scale
	);
	healthBarBackground->Render = [healthBarBackground_image]() {
		healthBarBackground_image->Render();
		};
	uiElementMap[UIElementIndex::HealthBarBackground] = healthBarBackground;

	// --- STAMINA BAR BACKGROUND ---
	GameObject* staminaBarBackground = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::StaminaBarBackground), Layer::Menu);
	Image* staminaBarBackground_image = staminaBarBackground->AddComponent<Image>();
	staminaBarBackground_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_BarBackground), true);
	staminaBarBackground_image->showOnScreen = true;
	staminaBarBackground->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::StaminaBarBackground),
		staminaBarBackground->transform->scale
	);
	staminaBarBackground->Render = [staminaBarBackground_image]() {
		staminaBarBackground_image->Render();
		};
	uiElementMap[UIElementIndex::StaminaBarBackground] = staminaBarBackground;

	// --- HEALTH BAR ---
	GameObject* healthBar = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::HealthBar), Layer::Menu);
	Image* healthBar_image = healthBar->AddComponent<Image>();
	healthBar_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_HealthBar), true);
	healthBar_image->showOnScreen = true;
	healthBar_image->imageFill = ImageFill::Horizontal;
	healthBar->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::HealthBar),
		healthBar->transform->scale
	);
	healthBar->Render = [this, healthBar_image]() {
		healthBar_image->fillAmount = PlayerStatistic::Instance()->GetHealth() / PlayerStatistic::Instance()->GetMaxHealth();
		healthBar_image->Render();
		};
	uiElementMap[UIElementIndex::HealthBar] = healthBar;

	// --- STAMINA BAR ---
	GameObject* staminaBar = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::StaminaBar), Layer::Menu);
	Image* staminaBar_image = staminaBar->AddComponent<Image>();
	staminaBar_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_StaminaBar), true);
	staminaBar_image->showOnScreen = true;
	staminaBar_image->imageFill = ImageFill::Horizontal;
	staminaBar->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::StaminaBar),
		staminaBar->transform->scale
	);
	staminaBar->Render = [this, staminaBar_image]() {
		staminaBar_image->fillAmount = PlayerStatistic::Instance()->GetStamina() / PlayerStatistic::Instance()->GetMaxStamina();
		staminaBar_image->Render();
		};
	uiElementMap[UIElementIndex::StaminaBar] = staminaBar;

	// --- HEALTH SYMBOL ---
	GameObject* healthSymbol = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::HealthSymbol), Layer::Menu);
	Image* healthSymbol_image = healthSymbol->AddComponent<Image>();
	healthSymbol_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_HealthSymbol), true);
	healthSymbol_image->showOnScreen = true;
	healthSymbol->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::HealthSymbol),
		healthSymbol->transform->scale
	);
	healthSymbol->Render = [healthSymbol_image]() {
		healthSymbol_image->Render();
		};
	uiElementMap[UIElementIndex::HealthSymbol] = healthSymbol;

	// --- STAMINA SYMBOL ---
	GameObject* staminaSymbol = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::StaminaSymbol), Layer::Menu);
	Image* staminaSymbol_image = staminaSymbol->AddComponent<Image>();
	staminaSymbol_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_StaminaSymbol), true);
	staminaSymbol_image->showOnScreen = true;
	staminaSymbol->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::StaminaSymbol),
		staminaSymbol->transform->scale
	);
	staminaSymbol->Render = [staminaSymbol_image]() {
		staminaSymbol_image->Render();
		};
	uiElementMap[UIElementIndex::StaminaSymbol] = staminaSymbol;

	// --- EXP LABEL ---
	GameObject* expLabel = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::EXPLabel), Layer::Menu);
	Text* expLabel_text = expLabel->AddComponent<Text>();
	expLabel_text->LoadText(std::to_string(previousPlayerEXP) + " / " + std::to_string(previousPlayerEXPNeeded), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::EXPLabel));
	expLabel_text->showOnScreen = true;
	expLabel_text->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::EXPLabel),
		expLabel_text->transform->scale
	);
	expLabel_text->transform->position.x = uiElementMap.at(UIElementIndex::LevelFrame)->transform->position.x;
	expLabel->Render = [this, expLabel_text]() {
		int exp = PlayerStatistic::Instance()->GetEXP();
		int expNeeded = PlayerStatistic::Instance()->GetEXPNeeded();
		if (exp != previousPlayerEXP || expNeeded != previousPlayerEXPNeeded) {
			expLabel_text->LoadText(std::to_string(exp) + " / " + std::to_string(expNeeded), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::EXPLabel));
			previousPlayerEXP = exp;
			previousPlayerEXPNeeded = expNeeded;
		}
		expLabel_text->Render();
		};
	uiElementMap[UIElementIndex::EXPLabel] = expLabel;

	// --- LEVEL ---
	GameObject* levelLabel = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::LevelLabel), Layer::Menu);
	Text* levelLabel_text = levelLabel->AddComponent<Text>();
	levelLabel_text->LoadText(std::to_string(previousPlayerLevel), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::LevelLabel));
	levelLabel_text->showOnScreen = true;
	levelLabel_text->transform->position = uiElementMap.at(UIElementIndex::LevelFrame)->transform->position;
	levelLabel->Render = [this, levelLabel_text]() {
		int playerLevel = PlayerStatistic::Instance()->GetLevel();
		if (playerLevel != previousPlayerLevel) {
			levelLabel_text->LoadText(std::to_string(playerLevel), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::LevelLabel));
			previousPlayerLevel = playerLevel;
		}
		levelLabel_text->Render();
		};
	uiElementMap[UIElementIndex::LevelLabel] = levelLabel;

	// --- HEALTH ---
	GameObject* healthLabel = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::HealthLabel), Layer::Menu);
	Text* healthLabel_text = healthLabel->AddComponent<Text>();
	healthLabel_text->LoadText(std::to_string(previousPlayerHealth) + " / " + std::to_string(previousPlayerMaxHealth), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::HealthLabel));
	healthLabel_text->showOnScreen = true;
	healthLabel_text->transform->position = uiElementMap.at(UIElementIndex::HealthBar)->transform->position;
	healthLabel->Render = [this, healthLabel_text]() {
		int playerHealth = PlayerStatistic::Instance()->GetHealth();
		int playerMaxHealth = PlayerStatistic::Instance()->GetMaxHealth();
		if (playerHealth != previousPlayerLevel || playerMaxHealth != previousPlayerMaxHealth) {
			healthLabel_text->LoadText(std::to_string(playerHealth) + " / " + std::to_string(playerMaxHealth), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::HealthLabel));
			playerHealth = playerHealth;
			playerMaxHealth = playerMaxHealth;
		}
		healthLabel_text->Render();
		};
	uiElementMap[UIElementIndex::HealthLabel] = healthLabel;

	// --- STAMINA ---
	GameObject* staminaLabel = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::StaminaLabel), Layer::Menu);
	Text* staminaLabel_text = staminaLabel->AddComponent<Text>();
	staminaLabel_text->LoadText(std::to_string(previousPlayerStamina) + " / " + std::to_string(previousPlayerMaxStamina), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::StaminaLabel));
	staminaLabel_text->showOnScreen = true;
	staminaLabel_text->transform->position = uiElementMap.at(UIElementIndex::StaminaBar)->transform->position;
	staminaLabel->Render = [this, staminaLabel_text]() {
		int playerStamina = PlayerStatistic::Instance()->GetStamina();
		int playerMaxStamina = PlayerStatistic::Instance()->GetMaxStamina();
		if (playerStamina != previousPlayerLevel || playerMaxStamina != previousPlayerMaxStamina) {
			staminaLabel_text->LoadText(std::to_string(playerStamina) + " / " + std::to_string(playerMaxStamina), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::StaminaLabel));
			playerStamina = playerStamina;
			playerMaxStamina = playerMaxStamina;
		}
		staminaLabel_text->Render();
		};
	uiElementMap[UIElementIndex::StaminaLabel] = staminaLabel;

	// --- MONEY ICON ---
	GameObject* moneyIcon = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::MoneyIcon), Layer::Menu);
	Image* moneyIcon_image = moneyIcon->AddComponent<Image>();
	moneyIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_MoneyIcon), true);
	moneyIcon_image->showOnScreen = true;
	moneyIcon->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::MoneyIcon),
		moneyIcon_image->transform->scale
	);
	moneyIcon->Render = [moneyIcon_image]() {
		moneyIcon_image->Render();
		};
	uiElementMap[UIElementIndex::MoneyIcon] = moneyIcon;

	// --- MONEY LABEL ---
	GameObject* moneyLabel = GameObject::Instantiate(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::MoneyLabel), Layer::Menu);
	Text* moneyLabel_text = moneyLabel->AddComponent<Text>();
	moneyLabel_text->LoadText(std::to_string(previousPlayerMoney), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::MoneyLabel));
	moneyLabel_text->showOnScreen = true;
	moneyLabel_text->transform->position = Math::SDLToC00(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::MoneyLabel), moneyLabel_text->transform->scale);
	moneyLabel->Render = [this, moneyLabel_text]() {
		if (PlayerStatistic::Instance()->GetMoney() != previousPlayerMoney) {
			previousPlayerMoney = PlayerStatistic::Instance()->GetMoney();
			moneyLabel_text->LoadText(std::to_string(previousPlayerMoney), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::MoneyLabel));
			moneyLabel_text->transform->position = Math::SDLToC00(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::MoneyLabel), moneyLabel_text->transform->scale);
		}
		moneyLabel_text->Render();
		};
	uiElementMap[UIElementIndex::MoneyLabel] = moneyLabel;

}

StatusBar::StatusBar() {

	if (instance)
		throw std::exception("Status bar can only have one instance");

	instance = this;

	previousPlayerLevel = 0;
	previousPlayerEXP = 0;
	previousPlayerMoney = 0;
	previousPlayerEXPNeeded = 0;
	previousPlayerHealth = 0.0f;
	previousPlayerMaxHealth = 0.0f;
	previousPlayerStamina = 0.0f;
	previousPlayerMaxStamina = 0.0f;

	InitializeUI();

}

StatusBar::~StatusBar() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	uiElementMap.clear();

	instance = nullptr;

}

void StatusBar::Update() {



}

StatusBar* StatusBar::Instance() { return instance; }