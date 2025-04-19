/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <string>
#include <unordered_map>

#include <GameComponent.h>
#include <Utils.h>

class PlayerStatistic;

class StatusBar : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class UIElementIndex {

		Frame,
		LevelFrame,
		LevelLabel,
		EXPLabel,
		HealthLabel,
		HealthBar,
		HealthBarBackground,
		HealthSymbol,
		StaminaLabel,
		StaminaBar,
		StaminaBarBackground,
		StaminaSymbol,
		MoneyIcon,
		MoneyLabel,

	};

	const std::string GROUP_LABEL_PREFIX = "Status_";
	const std::string FOLDER_PATH = "./Asset/Status/";
	const std::string FILE_EXTENSION = ".png";
	const std::unordered_map<UIElementIndex, std::string> UI_ELEMENT_LABEL_MAP = {

		{ UIElementIndex::Frame, "Frame" },
		{ UIElementIndex::LevelFrame, "LevelFrame" },
		{ UIElementIndex::LevelLabel, "Level" },
		{ UIElementIndex::EXPLabel, "XP" },
		{ UIElementIndex::HealthLabel, "Health" },
		{ UIElementIndex::HealthBar, "HealthBar" },
		{ UIElementIndex::HealthBarBackground, "BarBackground" },
		{ UIElementIndex::HealthSymbol, "HealthSymbol" },
		{ UIElementIndex::StaminaLabel, "Stamina" },
		{ UIElementIndex::StaminaBar, "StaminaBar" },
		{ UIElementIndex::StaminaBarBackground, "BarBackground" },
		{ UIElementIndex::StaminaSymbol, "StaminaSymbol" },
		{ UIElementIndex::MoneyIcon, "MoneyIcon" },
		{ UIElementIndex::MoneyLabel, "MoneyLabel" },

	};
	const std::unordered_map<UIElementIndex, int> UI_LABEL_FONT_SIZE_MAP = {
		{ UIElementIndex::EXPLabel, 12 },
		{ UIElementIndex::LevelLabel, 48 },
		{ UIElementIndex::StaminaLabel, 12 },
		{ UIElementIndex::HealthLabel, 12 },
		{ UIElementIndex::MoneyLabel, 16 },
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_ELEMENT_POSITION_MAP = {

		{ UIElementIndex::Frame, Vector2(20.0f, 500.0f) },
		{ UIElementIndex::LevelFrame, Vector2(44.0f, 538.0f) },
		{ UIElementIndex::LevelLabel, Vector2(80.0f, 571.0f) },
		{ UIElementIndex::EXPLabel, Vector2(0.0f, 671.0f) },
		{ UIElementIndex::HealthBar, Vector2(215.0f, 568.0f) },
		{ UIElementIndex::HealthBarBackground, Vector2(215.0f, 568.0f) },
		{ UIElementIndex::HealthSymbol, Vector2(180.0f, 567.0f) },
		{ UIElementIndex::StaminaBar, Vector2(215.0f, 608.0f) },
		{ UIElementIndex::StaminaBarBackground, Vector2(215.0f, 608.0f) },
		{ UIElementIndex::StaminaSymbol, Vector2(181.0f, 604.0f) },
		{ UIElementIndex::MoneyIcon, Vector2(184.0f, 648.0f) },
		{ UIElementIndex::MoneyLabel, Vector2(221.0f, 656.0f) },

	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	// Variable to check for statistic changes
	int previousPlayerLevel;
	int previousPlayerEXP;
	int previousPlayerMoney;
	int previousPlayerEXPNeeded;
	float previousPlayerHealth;
	float previousPlayerMaxHealth;
	float previousPlayerStamina;
	float previousPlayerMaxStamina;
	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;

	static StatusBar* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeUI();
	void Show();
	void Hide();

public:

	StatusBar();
	~StatusBar();
	
	static StatusBar* Instance();

};