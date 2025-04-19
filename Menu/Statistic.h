#pragma once

#include <string>
#include <unordered_map>

#include <GameObject.h>
#include <Utils.h>

class Statistic : public GameObject {

private:

	enum class UIElementIndex {
		ZombieKilledLabel,
		ZombieKilledAmount,
		WaveSurvivedLabel,
		WaveSurvivedAmount,
		DamageDealtLabel,
		DamageDealtAmount,
		ReturnButton,
		ReturnLabel,
		Title,
	};
	
	const int TITLE_FONT_SIZE = 48;
	const int STAT_FONT_SIZE = 24;
	const int RETURN_LABEL_FONT_SIZE = 24;
	const int STAT_DECIMAL = 2;
	const std::unordered_map<UIElementIndex, std::string> UI_LABEL_MAP = {
		{ UIElementIndex::ZombieKilledLabel, "Most Zombie Killed:" },
		{ UIElementIndex::WaveSurvivedLabel, "Most Wave Survived:" },
		{ UIElementIndex::DamageDealtLabel, "Most Damage Dealt:" },
		{ UIElementIndex::ReturnLabel, "Return" },
		{ UIElementIndex::Title, "Player Statistics" },
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_POSITION_MAP = {
		{ UIElementIndex::ZombieKilledLabel, Vector2(413.0f, 188.0f) },
		{ UIElementIndex::ZombieKilledAmount, Vector2(738.0f, 188.0f) },
		{ UIElementIndex::WaveSurvivedLabel, Vector2(413.0f, 269.0f) },
		{ UIElementIndex::WaveSurvivedAmount, Vector2(738.0f, 269.0f) },
		{ UIElementIndex::DamageDealtLabel, Vector2(413.0f, 350.0f) },
		{ UIElementIndex::DamageDealtAmount, Vector2(738.0f, 350.0f) },
		{ UIElementIndex::ReturnButton, Vector2(540.0f, 654.0f) },
		{ UIElementIndex::Title, Vector2(0.0f, -50.0f) },
	};

private:

	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;

	static Statistic* instance;

private:

	void InitializeUI();
	void Show();
	void Hide();

public:

	Statistic();
	~Statistic();
	void UpdateZombie(int amount);
	void UpdateDamage(float amount);
	void UpdateWave(int amount);
	void Start() override;

	static Statistic* Instance();

};