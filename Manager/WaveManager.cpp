#include <WaveManager.h>
#include <exception>
#include <GameCore.h>
#include <string>
#include <cmath>
#include <Zombie.h>
#include <GameManager.h>
#include <MediaManager.h>
#include <Texture.h>

WaveHandler* WaveHandler::instance = nullptr;
WaveInfoUI* WaveInfoUI::instance = nullptr;

WaveHandler::WaveHandler() {

	if (instance)
		throw std::exception("Wave handler should only have one instance!");

	instance = this;

	new WaveInfoUI;

	currentWave = 0;
	totalZombie = 0;
	zombieLeft = 0;
	zombieToSpawn = 0;
	zombieKilled = 0;

	currentProgress = 0.0f;
	lastSpawnTick = 0.0f;

	difficulty = 1.0f;

	waveInProgress = false;

}

void WaveHandler::Update() {

	if (waveInProgress && zombieToSpawn > 0 && GameCore::Time() >= lastSpawnTick + SPAWN_DELAY) {

		int spawnAmount = Random::Int(std::min(zombieToSpawn, MIN_HORDE), std::min(zombieToSpawn, MAX_HORDE));
		zombieToSpawn -= spawnAmount;
		zombieLeft += spawnAmount;

		lastSpawnTick = GameCore::Time();

		GameManager::Instance()->SpawnZombie(spawnAmount, 
			Random::Int(0, 10) & 1 ? ZombieIndex::Normal : ZombieIndex::Lurker);

	}

}

void WaveHandler::RemoveZombie() {

	zombieLeft--;
	zombieKilled++;

	currentProgress = zombieKilled * 1.0f / totalZombie;

	if (zombieLeft == 0 && zombieToSpawn == 0) {

		std::cout << "Wave cleared!" << std::endl;
		waveInProgress = false;

	}

}

void WaveHandler::InitiateWave() {

	if (waveInProgress)
		return;

	waveInProgress = true;

	currentWave++;

	zombieKilled = 0;
	zombieLeft = 0;

	currentProgress = 0.0f;

	zombieToSpawn = static_cast<int>(BASE_SPAWN * std::powf(SPAWN_MULTIPLIER, currentWave));
	totalZombie = zombieToSpawn;

}

WaveInfoUI::WaveInfoUI() {

	if (instance)
		throw std::exception("Wave info UI should only have one instance!");

	instance = this;

	uiElementMap = {};

	previousProgress = 0;
	previousWave = 0;

	InitializeUI();

}

void WaveInfoUI::InitializeUI() {

	// --- PROGRESS LABEL ---
	uiElementMap[WaveInfoIndex::ProgressLabel] = new GameObject(UI_LABEL_MAP.at(WaveInfoIndex::ProgressLabel), Layer::GUI);
	Text* progressLabel_text = uiElementMap.at(WaveInfoIndex::ProgressLabel)->AddComponent<Text>();
	progressLabel_text->LoadText(UI_TEXT_MAP.at(WaveInfoIndex::ProgressLabel), Color::WHITE, UI_TEXT_SIZE_MAP.at(WaveInfoIndex::ProgressLabel));
	progressLabel_text->showOnScreen = true;
	progressLabel_text->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(WaveInfoIndex::ProgressLabel), progressLabel_text->transform->scale);
	progressLabel_text->transform->position.x = 0.0f;
	uiElementMap.at(WaveInfoIndex::ProgressLabel)->Render = [progressLabel_text]() {
		if (!WaveHandler::Instance()->WaveInProgress())
			return;
		progressLabel_text->Render();
		};

	// --- PROGRESS BAR BACKGROUND
	uiElementMap[WaveInfoIndex::ProgressBarBackground] = new GameObject(UI_LABEL_MAP.at(WaveInfoIndex::ProgressBarBackground), Layer::GUI);
	Image* progressBarBackground_image = uiElementMap.at(WaveInfoIndex::ProgressBarBackground)->AddComponent<Image>();
	progressBarBackground_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::WaveInfo_ProgressBarBackground),true);
	progressBarBackground_image->showOnScreen = true;
	progressBarBackground_image->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(WaveInfoIndex::ProgressBarBackground), progressBarBackground_image->transform->scale);
	progressBarBackground_image->transform->position.x = 0.0f;
	uiElementMap.at(WaveInfoIndex::ProgressBarBackground)->Render = [progressBarBackground_image]() {
		if (!WaveHandler::Instance()->WaveInProgress())
			return;
		progressBarBackground_image->Render();
		};

	// --- PROGRESS BAR
	uiElementMap[WaveInfoIndex::ProgressBar] = new GameObject(UI_LABEL_MAP.at(WaveInfoIndex::ProgressBar), Layer::GUI);
	Image* progressBar_image = uiElementMap.at(WaveInfoIndex::ProgressBar)->AddComponent<Image>();
	progressBar_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::WaveInfo_ProgressBar),true);
	progressBar_image->imageFill = ImageFill::Horizontal;
	progressBar_image->showOnScreen = true;
	progressBar_image->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(WaveInfoIndex::ProgressBar), progressBar_image->transform->scale);
	progressBar_image->transform->position.x = 0.0f;
	uiElementMap.at(WaveInfoIndex::ProgressBar)->Render = [progressBar_image]() {
		if (!WaveHandler::Instance()->WaveInProgress())
			return;
		progressBar_image->fillAmount = WaveHandler::Instance()->GetCurrentProgress();
		progressBar_image->Render();
		};

	// --- PROGRESS ---
	uiElementMap[WaveInfoIndex::Progress] = new GameObject(UI_LABEL_MAP.at(WaveInfoIndex::Progress), Layer::GUI);
	Text* progress_text = uiElementMap.at(WaveInfoIndex::Progress)->AddComponent<Text>();
	progress_text->LoadText(std::to_string(previousProgress) + UI_TEXT_MAP.at(WaveInfoIndex::Progress), Color::WHITE, UI_TEXT_SIZE_MAP.at(WaveInfoIndex::Progress));
	progress_text->showOnScreen = true;
	progress_text->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(WaveInfoIndex::Progress), progress_text->transform->scale);
	progress_text->transform->position.x = 0.0f;
	uiElementMap.at(WaveInfoIndex::Progress)->Render = [this, progress_text]() {
		if (!WaveHandler::Instance()->WaveInProgress())
			return;
		int progress = WaveHandler::Instance()->GetCurrentProgress() * 100.0f;
		if (progress != previousProgress) {
			previousProgress = progress;
			progress_text->LoadText(std::to_string(previousProgress) + UI_TEXT_MAP.at(WaveInfoIndex::Progress), Color::WHITE, UI_TEXT_SIZE_MAP.at(WaveInfoIndex::Progress));
		}
		progress_text->Render();
		};

	// --- WAVE ---
	uiElementMap[WaveInfoIndex::Wave] = new GameObject(UI_LABEL_MAP.at(WaveInfoIndex::Wave), Layer::GUI);
	Text* wave_text = uiElementMap.at(WaveInfoIndex::Wave)->AddComponent<Text>();
	wave_text->LoadText(UI_TEXT_MAP.at(WaveInfoIndex::Wave) + std::to_string(previousWave), Color::WHITE, UI_TEXT_SIZE_MAP.at(WaveInfoIndex::Wave));
	wave_text->showOnScreen = true;
	wave_text->transform->position = (GameCore::WindowResolution() - wave_text->transform->scale) / 2.0f;
	uiElementMap.at(WaveInfoIndex::Wave)->Render = [this, wave_text]() {
		int currentWave = WaveHandler::Instance()->GetCurrentWave();
		if (currentWave != previousWave) {
			previousWave = currentWave;
			wave_text->LoadText(UI_TEXT_MAP.at(WaveInfoIndex::Wave) + std::to_string(previousWave), Color::WHITE, UI_TEXT_SIZE_MAP.at(WaveInfoIndex::Wave));
		}
		wave_text->Render();
		};

	// --- NEXT WAVE BUTTON ---
	uiElementMap[WaveInfoIndex::NextWaveButton] = new GameObject(UI_LABEL_MAP.at(WaveInfoIndex::NextWaveButton), Layer::GUI);
	Image* nextWave_image = uiElementMap.at(WaveInfoIndex::NextWaveButton)->AddComponent<Image>();
	nextWave_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::WaveInfo_NextWaveButton),true);
	nextWave_image->showOnScreen = true;
	Button* nextWave_button = uiElementMap.at(WaveInfoIndex::NextWaveButton)->AddComponent<Button>();
	nextWave_button->backgroundColor = Color::TRANSPARENT;
	nextWave_button->OnClick = []() {
		WaveHandler::Instance()->InitiateWave();
		};
	nextWave_button->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(WaveInfoIndex::NextWaveButton), nextWave_button->transform->scale);
	uiElementMap.at(WaveInfoIndex::NextWaveButton)->Render = [nextWave_image]() {
		if (WaveHandler::Instance()->WaveInProgress())
			return;
		nextWave_image->Render();
		};

	// --- NEXT WAVE LABEL ---
	uiElementMap[WaveInfoIndex::NextWaveLabel] = new GameObject(UI_LABEL_MAP.at(WaveInfoIndex::NextWaveLabel), Layer::GUI);
	Text* nextWave_text = uiElementMap.at(WaveInfoIndex::NextWaveLabel)->AddComponent<Text>();
	nextWave_text->LoadText(UI_TEXT_MAP.at(WaveInfoIndex::NextWaveLabel), Color::WHITE, UI_TEXT_SIZE_MAP.at(WaveInfoIndex::NextWaveLabel));
	nextWave_text->showOnScreen = true;
	nextWave_text->transform->position = nextWave_button->transform->position;
	uiElementMap.at(WaveInfoIndex::NextWaveLabel)->Render = [nextWave_text]() {
		if (WaveHandler::Instance()->WaveInProgress())
			return;
		nextWave_text->Render();
		};

}