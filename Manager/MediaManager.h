#pragma once

#include <unordered_map>
#include <string>
#include <SDL_ttf.h>

enum class MediaObject {

	Entity_Zombie,
	Entity_Player,
	Gun_M1911,
	Gun_Beretta1301,
	Misc_Bullet,
	Misc_Background,
	Misc_HealthBar,
	Misc_ItemIcon,

};

enum class MediaUI {

	Icon_MoneyIcon,
	Icon_SkillPointIcon,
	Firearm_AmmoFrame,
	Firearm_AmmoIcon,
	Status_BarBackground,
	Status_Frame,
	Status_HealthBar,
	Status_HealthSymbol,
	Status_LevelFrame,
	Status_StaminaBar,
	Status_StaminaSymbol,
	WaveInfo_NextWaveButton,
	WaveInfo_ProgressBar,
	WaveInfo_ProgressBarBackground,
	Shop_FirearmAttributeFrame,
	Shop_Background,
	Shop_FirearmViewport,
	Shop_FirearmSelectionSlot,
	Shop_FirearmSelectionSlotHovered,
	Shop_NavigationButtonSelected,
	Shop_NavigationButtonUnselected,
	Shop_FirearmUpgradeSlot,
	Shop_FirearmUpgradeSlotHovered,
	Shop_UtilityBuyButton,
	Shop_UtilityInfoBoard,
	Shop_UtilityItemBar,
	Shop_UtilityItemCell,
	Shop_UtilityItemViewport,
	Shop_SkillNode,
	Shop_SkillNode_Selected,
	Shop_SkillNode_Acquired,
	Shop_SkillConnector,
	Shop_SkillInfoBoard,
	Shop_SkillInfoBoardUnselected,
	Shop_SkillIconFrame,
	Shop_SkillBuyButton,
	HotBar_Selection,
	HotBar_Slot,

};

enum class MediaAudio {



};

enum class MediaFont {

	RimouskiSb_Regular,

};

class Sprite;

class MediaManager {

private:

	static MediaManager* instance;

	const std::string ASSET_FOLDER_PATH = ".\\Asset\\";
	const std::string SPRITE_EXTENSION = ".png";
	const std::string FONT_EXTENSION = ".ttf";

	// --- UI SPRITE ---

	std::unordered_map<MediaUI, Sprite*> uiSpriteMap;
	const std::unordered_map<MediaUI, std::string> MEDIA_UI_PATH_MAP = {
		{ MediaUI::Firearm_AmmoFrame, "Firearm\\AmmoFrame" },
		{ MediaUI::Firearm_AmmoIcon, "Firearm\\AmmoIcon" },
		{ MediaUI::Status_BarBackground, "Status\\BarBackground" },
		{ MediaUI::Status_Frame, "Status\\Frame" },
		{ MediaUI::Status_HealthBar, "Status\\HealthBar" },
		{ MediaUI::Status_HealthSymbol, "Status\\HealthSymbol" },
		{ MediaUI::Status_LevelFrame, "Status\\LevelFrame" },
		{ MediaUI::Icon_MoneyIcon, "Icon\\MoneyIcon" },
		{ MediaUI::Icon_SkillPointIcon, "Icon\\SkillPointIcon" },
		{ MediaUI::Status_StaminaBar, "Status\\StaminaBar" },
		{ MediaUI::Status_StaminaSymbol, "Status\\StaminaSymbol" },
		{ MediaUI::WaveInfo_NextWaveButton, "WaveInfo\\NextWaveButton" },
		{ MediaUI::WaveInfo_ProgressBar, "WaveInfo\\ProgressBar" },
		{ MediaUI::WaveInfo_ProgressBarBackground, "WaveInfo\\ProgressBarBackground" },
		{ MediaUI::Shop_FirearmAttributeFrame, "Shop\\FirearmAttributeFrame" },
		{ MediaUI::Shop_Background, "Shop\\Background" },
		{ MediaUI::Shop_FirearmViewport, "Shop\\FirearmViewport" },
		{ MediaUI::Shop_FirearmSelectionSlot, "Shop\\FirearmSelectionSlot" },
		{ MediaUI::Shop_FirearmSelectionSlotHovered, "Shop\\FirearmSelectionSlotHovered" },
		{ MediaUI::Shop_NavigationButtonSelected, "Shop\\NavigationButtonSelected" },
		{ MediaUI::Shop_NavigationButtonUnselected, "Shop\\NavigationButtonUnselected" },
		{ MediaUI::Shop_FirearmUpgradeSlot, "Shop\\FirearmUpgradeSlot" },
		{ MediaUI::Shop_FirearmUpgradeSlotHovered, "Shop\\FirearmUpgradeSlotHovered" },
		{ MediaUI::Shop_UtilityBuyButton, "Shop\\UtilityBuyButton" },
		{ MediaUI::Shop_UtilityInfoBoard, "Shop\\UtilityInfoBoard" },
		{ MediaUI::Shop_UtilityItemBar, "Shop\\UtilityItemBar" },
		{ MediaUI::Shop_UtilityItemCell, "Shop\\UtilityItemCell" },
		{ MediaUI::Shop_UtilityItemViewport, "Shop\\UtilityItemViewport" },
		{ MediaUI::Shop_SkillNode, "Shop\\SkillNode" },
		{ MediaUI::Shop_SkillNode_Selected, "Shop\\SkillNodeSelected" },
		{ MediaUI::Shop_SkillNode_Acquired, "Shop\\SkillNodeAcquired" },
		{ MediaUI::Shop_SkillConnector, "Shop\\SkillConnector" },
		{ MediaUI::Shop_SkillBuyButton, "Shop\\SkillBuyButton" },
		{ MediaUI::Shop_SkillIconFrame, "Shop\\SkillIconFrame" },
		{ MediaUI::Shop_SkillInfoBoard, "Shop\\SkillInfoBoard" },
		{ MediaUI::Shop_SkillInfoBoardUnselected, "Shop\\SkillInfoBoardUnselected" },
		{ MediaUI::HotBar_Selection, "HotBar\\HotBarSelection" },
		{ MediaUI::HotBar_Slot, "HotBar\\HotBarSlot" },
	};

	// --- OBJECT SPRITE ---

	std::unordered_map<MediaObject, Sprite*> objectSpriteMap;
	const std::unordered_map<MediaObject, std::string> MEDIA_OBJECT_PATH_MAP = {
		{ MediaObject::Entity_Zombie, "Entity\\Zombie" },
		{ MediaObject::Entity_Player, "Entity\\Player" },
		{ MediaObject::Gun_Beretta1301, "Firearm\\Beretta1301" },
		{ MediaObject::Gun_M1911, "Firearm\\M1911" },
		{ MediaObject::Misc_Bullet, "Misc\\Bullet" },
		{ MediaObject::Misc_Background, "Misc\\Background" },
		{ MediaObject::Misc_HealthBar, "Misc\\HealthBar" },
		{ MediaObject::Misc_ItemIcon, "Misc\\ItemIcon" },
	};

	// --- FONT ---
	std::unordered_map<MediaFont, TTF_Font*> fontMap;
	const std::string FONT_SUBFOLDER = "Font\\";
	const int DEFAULT_FONT_SIZE = 16;
	const std::unordered_map<MediaFont, std::string> FONT_PATH_MAP = {
		{ MediaFont::RimouskiSb_Regular, "RimouskiSb_Regular" },
	};

private:

	void InitializeMediaUI();
	void InitializeMediaObject();
	void InitializeMediaFont();

public:

	Sprite* GetUISprite(MediaUI mediaUI);
	Sprite* GetObjectSprite(MediaObject mediaObject);
	TTF_Font* GetFont(MediaFont mediaFont);

	MediaManager();

	static MediaManager* Instance();

};