/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <MediaManager.h>

#include <exception>
#include <iostream>

#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

MediaManager* MediaManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void MediaManager::InitializeMediaUI() {

	std::cout << "[MediaManager] Loading UI Media..." << std::endl;

	int completed = 0;
	int total = MEDIA_UI_PATH_MAP.size();

	for (auto it = MEDIA_UI_PATH_MAP.begin(); it != MEDIA_UI_PATH_MAP.end(); it++) {

		uiSpriteMap[it->first] = new Sprite;
		if (!uiSpriteMap.at(it->first)->LoadImage(ASSET_FOLDER_PATH + it->second + SPRITE_EXTENSION))
			throw std::exception(("Loading media UI failed at item " + it->second).c_str());

		completed++;
		std::cout << "[MediaManager] Progress: " << completed << " / " << total << std::endl;

	}

}

void MediaManager::InitializeMediaObject() {

	std::cout << "[MediaManager] Loading Object Media..." << std::endl;

	int completed = 0;
	int total = MEDIA_OBJECT_PATH_MAP.size();

	for (auto it = MEDIA_OBJECT_PATH_MAP.begin(); it != MEDIA_OBJECT_PATH_MAP.end(); it++) {

		objectSpriteMap[it->first] = new Sprite;
		if (!objectSpriteMap.at(it->first)->LoadImage(ASSET_FOLDER_PATH + it->second + SPRITE_EXTENSION))
			throw std::exception(("Loading media object failed at item " + it->second).c_str());

		completed++;
		std::cout << "[MediaManager] Progress: " << completed << " / " << total << std::endl;

	}

}

void MediaManager::InitializeMediaFont() {

	std::cout << "[MediaManager] Loading Font Media..." << std::endl;

	int completed = 0;
	int total = FONT_PATH_MAP.size();

	for (auto it = FONT_PATH_MAP.begin(); it != FONT_PATH_MAP.end(); it++) {

		fontMap[it->first] = TTF_OpenFont((ASSET_FOLDER_PATH + FONT_SUBFOLDER + it->second + FONT_EXTENSION).c_str(), DEFAULT_FONT_SIZE);
		if (!fontMap.at(it->first))
			throw std::exception(("Font " + it->second + " failed to load. Error: " + TTF_GetError()).c_str());

		completed++;
		std::cout << "[MediaManager] Progress: " << completed << " / " << total << std::endl;

	}

}

MediaManager::MediaManager() {

	std::cout << "[MediaManager] Initializing..." << std::endl;

	if (instance)
		throw std::exception("Media Manager can only have one instance!");

	instance = this;

	InitializeMediaUI();
	InitializeMediaObject();
	InitializeMediaFont();

	std::cout << "[MediaManager] Initialization complete!" << std::endl;

}

MediaManager::~MediaManager() {

	for (auto it_ui = uiSpriteMap.begin(); it_ui != uiSpriteMap.end(); it_ui++)
		delete (it_ui->second);

	uiSpriteMap.clear();

	for (auto it_object = objectSpriteMap.begin(); it_object != objectSpriteMap.end(); it_object++)
		delete (it_object->second);

	objectSpriteMap.clear();

	for (auto it_font = fontMap.begin(); it_font != fontMap.end(); it_font++)
		delete (it_font->second);

	fontMap.clear();

	instance = nullptr;

}

Sprite* MediaManager::GetUISprite(MediaUI mediaUI) {

	if (uiSpriteMap.contains(mediaUI))
		return uiSpriteMap.at(mediaUI);

	return nullptr;

}

Sprite* MediaManager::GetObjectSprite(MediaObject mediaObject) {

	if (objectSpriteMap.contains(mediaObject))
		return objectSpriteMap.at(mediaObject);

	return nullptr;

}

TTF_Font* MediaManager::GetFont(MediaFont mediaFont) {

	if (fontMap.contains(mediaFont))
		return fontMap.at(mediaFont);

	return nullptr;

}

MediaManager* MediaManager::Instance() { return instance; }