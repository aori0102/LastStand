/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <FirearmAttributeUIGroup.h>

#include <Firearm.h>
#include <Texture.h>

#include <exception>
#include <iomanip>
#include <sstream>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int FirearmAttributeUIGroup::ATTRIBUTE_FONT_SIZE = 24;
const float FirearmAttributeUIGroup::ATTRIBUTE_MARGIN = 6.0f;
const Vector2 FirearmAttributeUIGroup::SINGLE_ATTRIBUTE_SCALE = Vector2(300.0f, 29.0f);
const std::unordered_map<FirearmAttributeIndex, std::string> FirearmAttributeUIGroup::ATTRIBUTE_LABEL_MAP = {
	{ FirearmAttributeIndex::Damage, "Damage" },
	{ FirearmAttributeIndex::CriticalChance, "Crit chance" },
	{ FirearmAttributeIndex::CriticalDamage, "Crit DMG" },
	{ FirearmAttributeIndex::MagazineCapacity, "Magazine" },
	{ FirearmAttributeIndex::Firerate, "Firerate" },
	{ FirearmAttributeIndex::ReloadTime, "Reload time"},
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void FirearmAttributeUIGroup::UpdateVisual() {

	Vector2 currentGroupPosition = Math::SDLToC00(position,SINGLE_ATTRIBUTE_SCALE);

	for (auto it = attributeUIMap.begin(); it != attributeUIMap.end(); it++) {

		(it->second)->format->transform->position = currentGroupPosition;
		Align::Left((it->second)->label->transform, (it->second)->format->transform);
		Align::MiddleVertically((it->second)->label->transform, (it->second)->format->transform);
		Align::Right((it->second)->amount->transform, (it->second)->format->transform);
		Align::MiddleVertically((it->second)->amount->transform, (it->second)->format->transform);

		currentGroupPosition += Vector2::down * ((it->second)->format->transform->scale.y + ATTRIBUTE_MARGIN);

	}

}

FirearmAttributeUIGroup::FirearmAttributeUIGroup() {

	position = Vector2::zero;

	for (auto it = ATTRIBUTE_LABEL_MAP.begin(); it != ATTRIBUTE_LABEL_MAP.end(); it++) {

		SingleAttributeGroup* singleAttributeGroup = new SingleAttributeGroup;
		singleAttributeGroup->format = GameObject::Instantiate(it->second + " Attribute format", Layer::Menu);
		singleAttributeGroup->format->transform->scale = SINGLE_ATTRIBUTE_SCALE;

		singleAttributeGroup->label = GameObject::Instantiate(it->second + " Attribute label", Layer::Menu);
		Text* label_text = singleAttributeGroup->label->AddComponent<Text>();
		label_text->showOnScreen = true;
		label_text->LoadText(it->second, Color::WHITE, ATTRIBUTE_FONT_SIZE);
		Align::Left(label_text->transform, singleAttributeGroup->format->transform);
		Align::MiddleVertically(label_text->transform, singleAttributeGroup->format->transform);
		singleAttributeGroup->label->Render = [this, label_text]() {
			if (IsActive())
				label_text->Render();
			};

		singleAttributeGroup->amount = GameObject::Instantiate(it->second + " Attribute amount", Layer::Menu);
		Text* amount_text = singleAttributeGroup->amount->AddComponent<Text>();
		amount_text->LoadText(std::to_string(0), Color::WHITE, ATTRIBUTE_FONT_SIZE);
		amount_text->showOnScreen = true;
		Align::Right(amount_text->transform, singleAttributeGroup->format->transform);
		Align::MiddleVertically(amount_text->transform, singleAttributeGroup->format->transform);
		singleAttributeGroup->amount->Render = [this, amount_text]() {
			if (IsActive())
				amount_text->Render();
			};

		attributeUIMap[it->first] = singleAttributeGroup;

	}

	UpdateVisual();

}

void FirearmAttributeUIGroup::SetAttribute(Firearm* firearm, int decimalPlace) {

	std::stringstream ss;
	for (auto it = attributeUIMap.begin(); it != attributeUIMap.end(); it++) {

		ss << std::fixed << std::setprecision(decimalPlace) << firearm->GetAttribute(it->first);

		(it->second)->amount->GetComponent<Text>()->LoadText(ss.str(), Color::WHITE, ATTRIBUTE_FONT_SIZE);
		Align::Right((it->second)->amount->transform, (it->second)->format->transform);
		Align::MiddleVertically((it->second)->amount->transform, (it->second)->format->transform);

		ss.clear();
		ss.str("");

	}

}

void FirearmAttributeUIGroup::SetPosition(Vector2 positionInSDL) {

	position = positionInSDL;

	UpdateVisual();

}