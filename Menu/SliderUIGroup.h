#pragma once

#include <string>

#include <GameObject.h>
#include <Utils.h>

class SliderUIGroup : public GameObject {

private:

	static const int LABEL_FONT_SIZE;
	static const int VALUE_FONT_SIZE;
	static const float SLIDER_OFFSET;
	static const float VALUE_OFFSET;
	static const std::string VALUE_SUFFIX;
	static const Vector2 GROUP_SCALE;

private:

	GameObject* emptyFormatFrame;
	GameObject* label;
	GameObject* sliderBar;
	GameObject* sliderNob;
	GameObject* valueLabel;

public:

	bool isSelected;
	std::function<void(float)> OnValueUpdated;

private:

	void InitializeUI();
	void Show();
	void Hide();

public:

	SliderUIGroup();
	~SliderUIGroup();
	void SetPosition(Vector2 positionInSDL);
	void SetSliderLabel(std::string sliderLabel);
	void SetValue(float value);
	void Update() override;

};