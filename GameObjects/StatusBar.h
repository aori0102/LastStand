#pragma once

#include <GameComponent.h>
#include <string>
#include <unordered_map>
#include <Type.h>

class PlayerStatistic;

class StatusBar : public GameObject {

private:

	enum class UIElementIndex {

		Frame,
		LevelFrame,
		Level,
		EXP,
		Health,
		HealthBar,
		HealthBarBackground,
		HealthSymbol,
		Stamina,
		StaminaBar,
		StaminaBarBackground,
		StaminaSymbol,
		MoneyIcon,
		MoneyLabel,

	};

	const std::unordered_map<UIElementIndex, std::string> UI_ELEMENT_LABEL_MAP = {

		{ UIElementIndex::Frame, "Frame" },
		{ UIElementIndex::LevelFrame, "LevelFrame" },
		{ UIElementIndex::Level, "Level" },
		{ UIElementIndex::EXP, "XP" },
		{ UIElementIndex::Health, "Health" },
		{ UIElementIndex::HealthBar, "HealthBar" },
		{ UIElementIndex::HealthBarBackground, "BarBackground" },
		{ UIElementIndex::HealthSymbol, "HealthSymbol" },
		{ UIElementIndex::Stamina, "Stamina" },
		{ UIElementIndex::StaminaBar, "StaminaBar" },
		{ UIElementIndex::StaminaBarBackground, "BarBackground" },
		{ UIElementIndex::StaminaSymbol, "StaminaSymbol" },
		{ UIElementIndex::MoneyIcon, "MoneyIcon" },
		{ UIElementIndex::MoneyLabel, "MoneyLabel" },

	};

	const std::unordered_map<UIElementIndex, int> UI_LABEL_FONT_SIZE_MAP = {
		{ UIElementIndex::EXP, 12 },
		{ UIElementIndex::Level, 48 },
		{ UIElementIndex::Stamina, 12 },
		{ UIElementIndex::Health, 12 },
		{ UIElementIndex::MoneyLabel, 16 },
	};

	const std::string GROUP_LABEL_PREFIX = "Status_";
	const std::string FOLDER_PATH = "./Asset/Status/";
	const std::string FILE_EXTENSION = ".png";

	const std::unordered_map<UIElementIndex, Vector2> UI_ELEMENT_POSITION_MAP = {

		{ UIElementIndex::Frame, Vector2(20.0f, 500.0f) },
		{ UIElementIndex::LevelFrame, Vector2(44.0f, 538.0f) },
		{ UIElementIndex::Level, Vector2(80.0f, 571.0f) },
		{ UIElementIndex::EXP, Vector2(0.0f, 671.0f) },
		{ UIElementIndex::HealthBar, Vector2(215.0f, 568.0f) },
		{ UIElementIndex::HealthBarBackground, Vector2(215.0f, 568.0f) },
		{ UIElementIndex::HealthSymbol, Vector2(180.0f, 567.0f) },
		{ UIElementIndex::StaminaBar, Vector2(215.0f, 608.0f) },
		{ UIElementIndex::StaminaBarBackground, Vector2(215.0f, 608.0f) },
		{ UIElementIndex::StaminaSymbol, Vector2(181.0f, 604.0f) },
		{ UIElementIndex::MoneyIcon, Vector2(184.0f, 648.0f) },
		{ UIElementIndex::MoneyLabel, Vector2(221.0f, 656.0f) },

	};

private:

	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;

	// Variable to check for statistic changes
	int previousPlayerLevel;
	int previousPlayerEXP;
	int previousPlayerMoney;
	int previousPlayerEXPNeeded;
	float previousPlayerHealth;
	float previousPlayerMaxHealth;
	float previousPlayerStamina;
	float previousPlayerMaxStamina;

	static StatusBar* instance;

private:

	void InitializeUI();

public:

	StatusBar();

	void Update() override;
	
	static StatusBar* Instance();

};