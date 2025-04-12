#pragma once

#include <string>
#include <unordered_map>

#include <GameComponent.h>

class Firearm;
enum class FirearmAttributeIndex;

class FirearmAttributeUIGroup : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	struct SingleAttributeGroup {

		GameObject* format;
		GameObject* label;
		GameObject* amount;

	};

	static const int ATTRIBUTE_FONT_SIZE;
	static const float ATTRIBUTE_MARGIN;
	static const Vector2 SINGLE_ATTRIBUTE_SCALE;
	static const std::unordered_map<FirearmAttributeIndex, std::string> ATTRIBUTE_LABEL_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	Vector2 position;
	std::unordered_map<FirearmAttributeIndex, SingleAttributeGroup*> attributeUIMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void UpdateVisual();
	void Show();
	void Hide();

public:

	FirearmAttributeUIGroup();

	void SetAttribute(Firearm* firearm, int decimalPlace);
	void SetPosition(Vector2 positionInSDL);

};