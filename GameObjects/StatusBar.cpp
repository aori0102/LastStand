#include <StatusBar.h>
#include <Texture.h>
#include <PlayerStatistic.h>
#include <string>
#include <MediaManager.h>

StatusBar::StatusBar(PlayerStatistic* initLinkedPlayerStatistic) {

	std::cout << "Status bar loaded" << std::endl;

	linkedPlayerStatistic = initLinkedPlayerStatistic;

	previousPlayerEXP = 0;
	previousPlayerLevel = 0;

	InitializeUI();

}

void StatusBar::InitializeUI() {

	// --- FRAME ---
	uiElementMap[UIElementIndex::Frame] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::Frame), Layer::Menu);
	Image* frame_image = uiElementMap.at(UIElementIndex::Frame)->AddComponent<Image>();
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_Frame), true);
	frame_image->showOnScreen = true;
	uiElementMap.at(UIElementIndex::Frame)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Frame),
		uiElementMap.at(UIElementIndex::Frame)->transform->scale
	);
	uiElementMap.at(UIElementIndex::Frame)->Render = [frame_image]() {
		frame_image->Render();
		};

	// --- LEVEL FRAME ---
	uiElementMap[UIElementIndex::LevelFrame] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::LevelFrame), Layer::Menu);
	Image* levelFrame_image = uiElementMap.at(UIElementIndex::LevelFrame)->AddComponent<Image>();
	levelFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_LevelFrame), true);
	levelFrame_image->showOnScreen = true;
	uiElementMap.at(UIElementIndex::LevelFrame)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::LevelFrame),
		uiElementMap.at(UIElementIndex::LevelFrame)->transform->scale
	);
	uiElementMap.at(UIElementIndex::LevelFrame)->Render = [levelFrame_image]() {
		levelFrame_image->Render();
		};

	// --- HEALTH BAR BACKGROUND ---
	uiElementMap[UIElementIndex::HealthBarBackground] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::HealthBarBackground), Layer::Menu);
	Image* healthBarBackground_image = uiElementMap.at(UIElementIndex::HealthBarBackground)->AddComponent<Image>();
	healthBarBackground_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_BarBackground), true);
	healthBarBackground_image->showOnScreen = true;
	uiElementMap.at(UIElementIndex::HealthBarBackground)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::HealthBarBackground),
		uiElementMap.at(UIElementIndex::HealthBarBackground)->transform->scale
	);
	uiElementMap.at(UIElementIndex::HealthBarBackground)->Render = [healthBarBackground_image]() {
		healthBarBackground_image->Render();
		};

	// --- STAMINA BAR BACKGROUND ---
	uiElementMap[UIElementIndex::StaminaBarBackground] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::StaminaBarBackground), Layer::Menu);
	Image* staminaBarBackground_image = uiElementMap.at(UIElementIndex::StaminaBarBackground)->AddComponent<Image>();
	staminaBarBackground_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_BarBackground), true);
	staminaBarBackground_image->showOnScreen = true;
	uiElementMap.at(UIElementIndex::StaminaBarBackground)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::StaminaBarBackground),
		uiElementMap.at(UIElementIndex::StaminaBarBackground)->transform->scale
	);
	uiElementMap.at(UIElementIndex::StaminaBarBackground)->Render = [staminaBarBackground_image]() {
		staminaBarBackground_image->Render();
		};

	// --- HEALTH BAR ---
	uiElementMap[UIElementIndex::HealthBar] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::HealthBar), Layer::Menu);
	Image* healthBar_image = uiElementMap.at(UIElementIndex::HealthBar)->AddComponent<Image>();
	healthBar_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_HealthBar), true);
	healthBar_image->showOnScreen = true;
	healthBar_image->imageFill = ImageFill::Horizontal;
	uiElementMap.at(UIElementIndex::HealthBar)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::HealthBar),
		uiElementMap.at(UIElementIndex::HealthBar)->transform->scale
	);
	uiElementMap.at(UIElementIndex::HealthBar)->Render = [this, healthBar_image]() {
		healthBar_image->fillAmount = linkedPlayerStatistic->GetHealth() / linkedPlayerStatistic->GetMaxHealth();
		healthBar_image->Render();
		};

	// --- STAMINA BAR ---
	uiElementMap[UIElementIndex::StaminaBar] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::StaminaBar), Layer::Menu);
	Image* staminaBar_image = uiElementMap.at(UIElementIndex::StaminaBar)->AddComponent<Image>();
	staminaBar_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_StaminaBar), true);
	staminaBar_image->showOnScreen = true;
	staminaBar_image->imageFill = ImageFill::Horizontal;
	uiElementMap.at(UIElementIndex::StaminaBar)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::StaminaBar),
		uiElementMap.at(UIElementIndex::StaminaBar)->transform->scale
	);
	uiElementMap.at(UIElementIndex::StaminaBar)->Render = [this, staminaBar_image]() {
		staminaBar_image->fillAmount = linkedPlayerStatistic->GetStamina() / linkedPlayerStatistic->GetMaxStamina();
		staminaBar_image->Render();
		};

	// --- HEALTH SYMBOL ---
	uiElementMap[UIElementIndex::HealthSymbol] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::HealthSymbol), Layer::Menu);
	Image* healthSymbol_image = uiElementMap.at(UIElementIndex::HealthSymbol)->AddComponent<Image>();
	healthSymbol_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_HealthSymbol), true);
	healthSymbol_image->showOnScreen = true;
	uiElementMap.at(UIElementIndex::HealthSymbol)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::HealthSymbol),
		uiElementMap.at(UIElementIndex::HealthSymbol)->transform->scale
	);
	uiElementMap.at(UIElementIndex::HealthSymbol)->Render = [healthSymbol_image]() {
		healthSymbol_image->Render();
		};

	// --- STAMINA SYMBOL ---
	uiElementMap[UIElementIndex::StaminaSymbol] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::StaminaSymbol), Layer::Menu);
	Image* staminaSymbol_image = uiElementMap.at(UIElementIndex::StaminaSymbol)->AddComponent<Image>();
	staminaSymbol_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Status_StaminaSymbol), true);
	staminaSymbol_image->showOnScreen = true;
	uiElementMap.at(UIElementIndex::StaminaSymbol)->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::StaminaSymbol),
		uiElementMap.at(UIElementIndex::StaminaSymbol)->transform->scale
	);
	uiElementMap.at(UIElementIndex::StaminaSymbol)->Render = [staminaSymbol_image]() {
		staminaSymbol_image->Render();
		};

	// --- EXP LABEL ---
	uiElementMap[UIElementIndex::EXP] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::EXP), Layer::Menu);
	Text* exp_text = uiElementMap.at(UIElementIndex::EXP)->AddComponent<Text>();
	exp_text->LoadText(std::to_string(previousPlayerEXP) + " / " + std::to_string(previousPlayerEXPNeeded), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::EXP));
	exp_text->showOnScreen = true;
	exp_text->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::EXP),
		exp_text->transform->scale
	);
	exp_text->transform->position.x = uiElementMap.at(UIElementIndex::LevelFrame)->transform->position.x;
	uiElementMap.at(UIElementIndex::EXP)->Render = [this, exp_text]() {
		int exp = linkedPlayerStatistic->GetEXP();
		int expNeeded = linkedPlayerStatistic->GetEXPNeeded();
		if (exp != previousPlayerEXP || expNeeded != previousPlayerEXPNeeded) {
			exp_text->LoadText(std::to_string(exp) + " / " + std::to_string(expNeeded), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::EXP));
			previousPlayerEXP = exp;
			previousPlayerEXPNeeded = expNeeded;
		}
		exp_text->Render();
		};

	// --- LEVEL ---
	uiElementMap[UIElementIndex::Level] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::Level), Layer::Menu);
	Text* level_text = uiElementMap.at(UIElementIndex::Level)->AddComponent<Text>();
	level_text->LoadText(std::to_string(previousPlayerLevel), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::Level));
	level_text->showOnScreen = true;
	level_text->transform->position = uiElementMap.at(UIElementIndex::LevelFrame)->transform->position;
	uiElementMap.at(UIElementIndex::Level)->Render = [this, level_text]() {
		int playerLevel = linkedPlayerStatistic->GetLevel();
		if (playerLevel != previousPlayerLevel) {
			level_text->LoadText(std::to_string(playerLevel), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::Level));
			previousPlayerLevel = playerLevel;
		}
		level_text->Render();
		};

	// --- HEALTH ---
	uiElementMap[UIElementIndex::Health] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::Health), Layer::Menu);
	Text* health_text = uiElementMap.at(UIElementIndex::Health)->AddComponent<Text>();
	health_text->LoadText(std::to_string(previousPlayerHealth) + " / " + std::to_string(previousPlayerMaxHealth), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::Health));
	health_text->showOnScreen = true;
	health_text->transform->position = uiElementMap.at(UIElementIndex::HealthBar)->transform->position;
	uiElementMap.at(UIElementIndex::Health)->Render = [this, health_text]() {
		int playerHealth = linkedPlayerStatistic->GetHealth();
		int playerMaxHealth = linkedPlayerStatistic->GetMaxHealth();
		if (playerHealth != previousPlayerLevel || playerMaxHealth != previousPlayerMaxHealth) {
			health_text->LoadText(std::to_string(playerHealth) + " / " + std::to_string(playerMaxHealth), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::Health));
			playerHealth = playerHealth;
			playerMaxHealth = playerMaxHealth;
		}
		health_text->Render();
		};

	// --- STAMINA ---
	uiElementMap[UIElementIndex::Stamina] = new GameObject(UI_ELEMENT_LABEL_MAP.at(UIElementIndex::Stamina), Layer::Menu);
	Text* stamina_text = uiElementMap.at(UIElementIndex::Stamina)->AddComponent<Text>();
	stamina_text->LoadText(std::to_string(previousPlayerStamina) + " / " + std::to_string(previousPlayerMaxStamina), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::Stamina));
	stamina_text->showOnScreen = true;
	stamina_text->transform->position = uiElementMap.at(UIElementIndex::StaminaBar)->transform->position;
	uiElementMap.at(UIElementIndex::Stamina)->Render = [this, stamina_text]() {
		int playerStamina = linkedPlayerStatistic->GetStamina();
		int playerMaxStamina = linkedPlayerStatistic->GetMaxStamina();
		if (playerStamina != previousPlayerLevel || playerMaxStamina != previousPlayerMaxStamina) {
			stamina_text->LoadText(std::to_string(playerStamina) + " / " + std::to_string(playerMaxStamina), Color::WHITE, UI_LABEL_FONT_SIZE_MAP.at(UIElementIndex::Stamina));
			playerStamina = playerStamina;
			playerMaxStamina = playerMaxStamina;
		}
		stamina_text->Render();
		};

}

void StatusBar::Update() {



}