/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>
#include <string>

#include <SDL_mixer.h>
#include <SDL_ttf.h>

enum class MediaObject {

	Entity_Zombie,
	Entity_Player,
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
	Shop_UtilityItemBar_Selected,
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
	Inventory_Background,
	Inventory_HotBarSlot,
	Inventory_HotBarSlot_Selected,
	Inventory_Slot,
	Inventory_Slot_Selected,
	Menu_Title,
	Menu_Button,
	Menu_Button_Selected,
	MenuSetting_KeyBindingFrame,
	MenuSetting_KeyBindingFrameSelected,
	Menu_ReturnButton,
	MenuSetting_Slider,
	MenuSetting_SliderButton,
	MenuSetting_SliderButtonSelected,
	SkillVisual_Health_I,
	SkillVisual_Health_II,
	SkillVisual_Health_III,
	SkillVisual_Health_IV,
	SkillVisual_QuickHand_I,
	SkillVisual_Accuracy_I,
	SkillVisual_Accuracy_II,
	SkillVisual_Accuracy_III,
	SkillVisual_Accuracy_IV,
	Menu_PauseFrame,
	Menu_PauseMenuButton,
	Menu_DeathMessageFrame,
	Menu_DeathMessageButton,
	Menu_TutorialButton,
	Menu_TutorialButton_Selected,
	Menu_StatisticButton,
	Menu_StatisticButton_Selected,

};

enum class MediaMusic {



};

enum class MediaSFX {

	RifleShot,
	PistolShot,
	ShotgunShot,
	WalkGrass1,
	WalkGrass2,
	WalkGrass3,
	ZombieHurt1,
	ZombieHurt2,
	ZombieHurt3,
	ZombieHurt4,
	ZombieHurt5,
	ZombieHurt6,
	ZombieGroan1,
	ZombieGroan2,
	ZombieGroan3,
	ZombieGroan4,
	Click,
	Clack,
	Coin,
	Invalid,
	PistolReloadStart,
	PistolReloadEnd,
	RifleReloadStart,
	RifleReloadEnd,
	ShotgunReload,

};

enum class MediaFont {

	RimouskiSb_Regular,

};

class Sprite;

class MediaManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	const int DEFAULT_FONT_SIZE = 16;
	const std::string ASSET_FOLDER_PATH = ".\\Asset\\";
	const std::string FONT_SUBFOLDER = "Font\\";
	const std::string AUDIO_SUBFOLDER = "Audio\\";
	const std::string SPRITE_EXTENSION = ".png";
	const std::string FONT_EXTENSION = ".ttf";
	const std::string AUDIO_EXTENSION = ".wav";
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
		{ MediaUI::Shop_UtilityItemBar_Selected, "Shop\\UtilityItemBarSelected" },
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
		{ MediaUI::Inventory_Slot, "Inventory\\Slot" },
		{ MediaUI::Inventory_Slot_Selected, "Inventory\\SlotSelected" },
		{ MediaUI::Inventory_Background, "Inventory\\Background" },
		{ MediaUI::Inventory_HotBarSlot, "Inventory\\HotBarSlot" },
		{ MediaUI::Inventory_HotBarSlot_Selected, "Inventory\\HotBarSlotSelected" },
		{ MediaUI::Menu_Button, "Menu\\Button" },
		{ MediaUI::Menu_Button_Selected, "Menu\\ButtonSelected" },
		{ MediaUI::Menu_Title, "Menu\\Title" },
		{ MediaUI::MenuSetting_KeyBindingFrame, "MenuSetting\\KeyBindingFrame" },
		{ MediaUI::MenuSetting_KeyBindingFrameSelected, "MenuSetting\\KeyBindingFrameSelected" },
		{ MediaUI::Menu_ReturnButton, "MenuSetting\\ReturnButton" },
		{ MediaUI::MenuSetting_Slider, "MenuSetting\\Slider" },
		{ MediaUI::MenuSetting_SliderButton, "MenuSetting\\SliderButton" },
		{ MediaUI::MenuSetting_SliderButtonSelected, "MenuSetting\\SliderButtonSelected" },
		{ MediaUI::SkillVisual_Health_I, "SkillVisual\\Health_I" },
		{ MediaUI::SkillVisual_Health_II, "SkillVisual\\Health_II" },
		{ MediaUI::SkillVisual_Health_III, "SkillVisual\\Health_III" },
		{ MediaUI::SkillVisual_Health_IV, "SkillVisual\\Health_IV" },
		{ MediaUI::SkillVisual_Accuracy_I, "SkillVisual\\Accuracy_I" },
		{ MediaUI::SkillVisual_Accuracy_II, "SkillVisual\\Accuracy_II" },
		{ MediaUI::SkillVisual_Accuracy_III, "SkillVisual\\Accuracy_III" },
		{ MediaUI::SkillVisual_Accuracy_IV, "SkillVisual\\Accuracy_IV" },
		{ MediaUI::SkillVisual_QuickHand_I, "SkillVisual\\QuickHand_I" },
		{ MediaUI::Menu_PauseFrame, "Menu\\PauseFrame" },
		{ MediaUI::Menu_PauseMenuButton, "Menu\\PauseMenuButton" },
		{ MediaUI::Menu_DeathMessageButton, "Menu\\DeathMessageButton" },
		{ MediaUI::Menu_DeathMessageFrame, "Menu\\DeathMessageFrame" },
		{ MediaUI::Menu_TutorialButton, "Menu\\TutorialButton" },
		{ MediaUI::Menu_TutorialButton_Selected, "Menu\\TutorialButtonSelected" },
		{ MediaUI::Menu_StatisticButton, "Menu\\StatisticButton" },
		{ MediaUI::Menu_StatisticButton_Selected, "Menu\\StatisticButtonSelected" },
	};
	const std::unordered_map<MediaObject, std::string> MEDIA_OBJECT_PATH_MAP = {
		{ MediaObject::Entity_Zombie, "Entity\\Zombie" },
		{ MediaObject::Entity_Player, "Entity\\Player" },
		{ MediaObject::Misc_Bullet, "Misc\\Bullet" },
		{ MediaObject::Misc_Background, "Misc\\Background" },
		{ MediaObject::Misc_HealthBar, "Misc\\HealthBar" },
		{ MediaObject::Misc_ItemIcon, "Misc\\ItemIcon" },
	};
	const std::unordered_map<MediaFont, std::string> FONT_PATH_MAP = {
		{ MediaFont::RimouskiSb_Regular, "RimouskiSb_Regular" },
	};
	const std::unordered_map<MediaSFX, std::string> SFX_PATH_MAP = {
		{ MediaSFX::RifleShot, "RifleShot" },
		{ MediaSFX::ShotgunShot, "ShotgunShot" },
		{ MediaSFX::PistolShot, "PistolShot" },
		{ MediaSFX::WalkGrass1, "WalkGrass1" },
		{ MediaSFX::WalkGrass2, "WalkGrass2" },
		{ MediaSFX::WalkGrass3, "WalkGrass3" },
		{ MediaSFX::ZombieGroan1, "ZombieGroan1" },
		{ MediaSFX::ZombieGroan2, "ZombieGroan2" },
		{ MediaSFX::ZombieGroan3, "ZombieGroan3" },
		{ MediaSFX::ZombieGroan4, "ZombieGroan4" },
		{ MediaSFX::ZombieHurt1, "ZombieHurt1" },
		{ MediaSFX::ZombieHurt2, "ZombieHurt2" },
		{ MediaSFX::ZombieHurt3, "ZombieHurt3" },
		{ MediaSFX::ZombieHurt4, "ZombieHurt4" },
		{ MediaSFX::ZombieHurt5, "ZombieHurt5" },
		{ MediaSFX::ZombieHurt6, "ZombieHurt6" },
		{ MediaSFX::Click, "Click" },
		{ MediaSFX::Clack, "Clack" },
		{ MediaSFX::Coin, "Coin" },
		{ MediaSFX::Invalid, "Invalid" },
		{ MediaSFX::PistolReloadEnd, "PistolReloadEnd" },
		{ MediaSFX::PistolReloadStart, "PistolReloadStart" },
		{ MediaSFX::RifleReloadEnd, "RifleReloadEnd" },
		{ MediaSFX::RifleReloadStart, "RifleReloadStart" },
		{ MediaSFX::ShotgunReload, "ShotgunReload" },
	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<MediaUI, Sprite*> uiSpriteMap;
	std::unordered_map<MediaObject, Sprite*> objectSpriteMap;
	std::unordered_map<MediaFont, TTF_Font*> fontMap;
	std::unordered_map<MediaSFX, Mix_Chunk*> sfxMap;

	static MediaManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeMediaUI();
	void InitializeMediaObject();
	void InitializeMediaFont();
	void InitializeMediaSFX();

public:

	MediaManager();
	~MediaManager();
	Sprite* GetUISprite(MediaUI mediaUI);
	Sprite* GetObjectSprite(MediaObject mediaObject);
	TTF_Font* GetFont(MediaFont mediaFont);
	Mix_Chunk* GetSFX(MediaSFX mediaSFX);

	static MediaManager* Instance();

};