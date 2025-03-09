#pragma once

#include <unordered_map>
#include <string>
#include <SDL_ttf.h>

enum class MediaObject {

	Entity_Zombie,
	Entity_Player,
	Misc_Bullet,
	Misc_Background,
	Misc_HealthBar,

};

enum class MediaUI {

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
	Shop_AttributeFrame,
	Shop_Background,
	Shop_NavigationButtonSelected,
	Shop_NavigationButtonUnselected,
	Shop_UpgradeSlot,

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

	const std::string ASSET_FOLDER_PATH = "./Asset/";
	const std::string SPRITE_EXTENSION = ".png";
	const std::string FONT_EXTENSION = ".ttf";

	// --- UI SPRITE ---

	std::unordered_map<MediaUI, Sprite*> uiSpriteMap;
	const std::unordered_map<MediaUI, std::string> MEDIA_UI_PATH_MAP = {
		{ MediaUI::Firearm_AmmoFrame, "Firearm/AmmoFrame" },
		{ MediaUI::Firearm_AmmoIcon, "Firearm/AmmoIcon" },
		{ MediaUI::Status_BarBackground, "Status/BarBackground" },
		{ MediaUI::Status_Frame, "Status/Frame" },
		{ MediaUI::Status_HealthBar, "Status/HealthBar" },
		{ MediaUI::Status_HealthSymbol, "Status/HealthSymbol" },
		{ MediaUI::Status_LevelFrame, "Status/LevelFrame" },
		{ MediaUI::Status_StaminaBar, "Status/StaminaBar" },
		{ MediaUI::Status_StaminaSymbol, "Status/StaminaSymbol" },
		{ MediaUI::WaveInfo_NextWaveButton, "WaveInfo/NextWaveButton" },
		{ MediaUI::WaveInfo_ProgressBar, "WaveInfo/ProgressBar" },
		{ MediaUI::WaveInfo_ProgressBarBackground, "WaveInfo/ProgressBarBackground" },
		{ MediaUI::Shop_AttributeFrame, "Shop/AttributeFrame" },
		{ MediaUI::Shop_Background, "Shop/Background" },
		{ MediaUI::Shop_NavigationButtonSelected, "Shop/NavigationButtonSelected" },
		{ MediaUI::Shop_NavigationButtonUnselected, "Shop/NavigationButtonUnselected" },
		{ MediaUI::Shop_UpgradeSlot, "Shop/UpgradeSlot" }
	};

	// --- OBJECT SPRITE ---

	std::unordered_map<MediaObject, Sprite*> objectSpriteMap;
	const std::unordered_map<MediaObject, std::string> MEDIA_OBJECT_PATH_MAP = {
		{ MediaObject::Entity_Zombie, "Entity/Zombie" },
		{ MediaObject::Entity_Player, "Entity/Player" },
		{ MediaObject::Misc_Bullet, "Misc/Bullet" },
		{ MediaObject::Misc_Background, "Misc/Background" },
		{ MediaObject::Misc_HealthBar, "Misc/HealthBar" },
	};

	// --- FONT ---
	std::unordered_map<MediaFont, TTF_Font*> fontMap;
	const std::string FONT_SUBFOLDER = "Font/";
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