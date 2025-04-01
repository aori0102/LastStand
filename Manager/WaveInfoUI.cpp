/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <WaveManager.h>

#include <GameComponent.h>
#include <GameCore.h>
#include <MediaManager.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

WaveInfoUI* WaveInfoUI::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void WaveInfoUI::InitializeUI() {

	// --- PROGRESS LABEL ---
	GameObject* progressLabel = new GameObject("Progress Label", Layer::GUI);
	Text* progressLabel_text = progressLabel->AddComponent<Text>();
	progressLabel_text->LoadText(
		UI_TEXT_MAP.at(WaveInfoIndex::ProgressLabel),
		Color::WHITE,
		UI_TEXT_SIZE_MAP.at(WaveInfoIndex::ProgressLabel)
	);
	progressLabel_text->showOnScreen = true;
	progressLabel_text->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(WaveInfoIndex::ProgressLabel), progressLabel_text->transform->scale
	);
	progressLabel_text->transform->position.x = 0.0f;
	progressLabel->Render = [progressLabel_text]() {
		if (!WaveManager::Instance()->WaveInProgress())
			return;
		progressLabel_text->Render();
		};
	uiElementMap[WaveInfoIndex::ProgressLabel] = progressLabel;

	// --- PROGRESS BAR BACKGROUND
	GameObject* progressBarBackground = new GameObject("Progress Bar Background", Layer::GUI);
	Image* progressBarBackground_image = progressBarBackground->AddComponent<Image>();
	progressBarBackground_image->LinkSprite(
		MediaManager::Instance()->GetUISprite(MediaUI::WaveInfo_ProgressBarBackground), true
	);
	progressBarBackground_image->showOnScreen = true;
	progressBarBackground_image->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(WaveInfoIndex::ProgressBarBackground), progressBarBackground_image->transform->scale
	);
	progressBarBackground_image->transform->position.x = 0.0f;
	progressBarBackground->Render = [progressBarBackground_image]() {
		if (!WaveManager::Instance()->WaveInProgress())
			return;
		progressBarBackground_image->Render();
		};
	uiElementMap[WaveInfoIndex::ProgressBarBackground] = progressBarBackground;

	// --- PROGRESS BAR
	GameObject* progressBar = new GameObject("Progress Bar", Layer::GUI);
	Image* progressBar_image = progressBar->AddComponent<Image>();
	progressBar_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::WaveInfo_ProgressBar), true);
	progressBar_image->imageFill = ImageFill::Horizontal;
	progressBar_image->showOnScreen = true;
	progressBar_image->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(WaveInfoIndex::ProgressBar), progressBar_image->transform->scale
	);
	progressBar_image->transform->position.x = 0.0f;
	progressBar->Render = [progressBar_image]() {
		if (!WaveManager::Instance()->WaveInProgress())
			return;
		progressBar_image->fillAmount = WaveManager::Instance()->GetCurrentProgress();
		progressBar_image->Render();
		};
	uiElementMap[WaveInfoIndex::ProgressBar] = progressBar;

	// --- PROGRESS ---
	GameObject* progressBarLabel = new GameObject("Progress Bar Label", Layer::GUI);
	Text* progressBarLabel_text = progressLabel->AddComponent<Text>();
	progressBarLabel_text->LoadText(
		std::to_string(previousProgress) + UI_TEXT_MAP.at(WaveInfoIndex::ProgressBarLabel),
		Color::WHITE,
		UI_TEXT_SIZE_MAP.at(WaveInfoIndex::ProgressBarLabel)
	);
	progressBarLabel_text->showOnScreen = true;
	progressBarLabel_text->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(WaveInfoIndex::ProgressBarLabel), progressBarLabel_text->transform->scale
	);
	progressBarLabel_text->transform->position.x = 0.0f;
	progressLabel->Render = [this, progressBarLabel_text]() {
		if (!WaveManager::Instance()->WaveInProgress())
			return;
		int progress = WaveManager::Instance()->GetCurrentProgress() * 100.0f;
		if (progress != previousProgress) {
			previousProgress = progress;
			progressBarLabel_text->LoadText(
				std::to_string(previousProgress) + UI_TEXT_MAP.at(WaveInfoIndex::ProgressBarLabel),
				Color::WHITE,
				UI_TEXT_SIZE_MAP.at(WaveInfoIndex::ProgressBarLabel)
			);
		}
		progressBarLabel_text->Render();
		};
	uiElementMap[WaveInfoIndex::ProgressBarLabel] = progressLabel;

	// --- WAVE ---
	GameObject* waveLabel = new GameObject("Wave Label", Layer::GUI);
	Text* waveLabel_text = waveLabel->AddComponent<Text>();
	waveLabel_text->LoadText(
		UI_TEXT_MAP.at(WaveInfoIndex::WaveLabel) + std::to_string(previousWave),
		Color::WHITE,
		UI_TEXT_SIZE_MAP.at(WaveInfoIndex::WaveLabel)
	);
	waveLabel_text->showOnScreen = true;
	waveLabel_text->transform->position = (GameCore::WindowResolution() - waveLabel_text->transform->scale) / 2.0f;
	waveLabel->Render = [this, waveLabel_text]() {
		int currentWave = WaveManager::Instance()->GetCurrentWave();
		if (currentWave != previousWave) {
			previousWave = currentWave;
			waveLabel_text->LoadText(
				UI_TEXT_MAP.at(WaveInfoIndex::WaveLabel) + std::to_string(previousWave),
				Color::WHITE, 
				UI_TEXT_SIZE_MAP.at(WaveInfoIndex::WaveLabel)
			);
		}
		waveLabel_text->Render();
		};
	uiElementMap[WaveInfoIndex::WaveLabel] = waveLabel;

	// --- NEXT WAVE BUTTON ---
	GameObject* nextWaveButton = new GameObject("Next Wave Button", Layer::GUI);
	Image* nextWave_image = nextWaveButton->AddComponent<Image>();
	nextWave_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::WaveInfo_NextWaveButton), true);
	nextWave_image->showOnScreen = true;
	Button* nextWave_button = nextWaveButton->AddComponent<Button>();
	nextWave_button->backgroundColor = Color::TRANSPARENT;
	nextWave_button->OnClick = []() {
		WaveManager::Instance()->InitiateWave();
		return true;
		};
	nextWave_button->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(WaveInfoIndex::NextWaveButton), nextWave_button->transform->scale
	);
	nextWaveButton->Render = [nextWave_image]() {
		if (WaveManager::Instance()->WaveInProgress())
			return;
		nextWave_image->Render();
		};
	uiElementMap[WaveInfoIndex::NextWaveButton] = nextWaveButton;

	// --- NEXT WAVE LABEL ---
	GameObject* nextWaveLabel = new GameObject("Next Wave Label", Layer::GUI);
	Text* nextWaveLabel_text = nextWaveLabel->AddComponent<Text>();
	nextWaveLabel_text->LoadText(
		UI_TEXT_MAP.at(WaveInfoIndex::NextWaveLabel), Color::WHITE, UI_TEXT_SIZE_MAP.at(WaveInfoIndex::NextWaveLabel)
	);
	nextWaveLabel_text->showOnScreen = true;
	nextWaveLabel_text->transform->position = nextWave_button->transform->position;
	nextWaveLabel->Render = [nextWaveLabel_text]() {
		if (WaveManager::Instance()->WaveInProgress())
			return;
		nextWaveLabel_text->Render();
		};
	uiElementMap[WaveInfoIndex::NextWaveLabel] = nextWaveLabel;

}

WaveInfoUI::WaveInfoUI() {

	if (instance)
		throw std::exception("Wave info UI should only have one instance!");

	previousProgress = 0;
	previousWave = 0;
	uiElementMap = {};

	instance = this;

	InitializeUI();

}

WaveInfoUI::~WaveInfoUI() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	uiElementMap.clear();

	instance = nullptr;

}

WaveInfoUI* WaveInfoUI::Instance() { return instance; }