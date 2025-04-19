/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameObject.h>

enum class ItemIndex;

class ItemInfoUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class UIElementIndex {
		InfoBoard,
		ItemViewport,
		BuyButton,
		ItemVisual,
		MoneyIcon,
		MoneyLabel,
		ItemLabel,
		ItemStackLabel,
		ItemDescription,
	};

	const std::unordered_map<UIElementIndex, Vector2> UI_POSITION_MAP = {
		{ UIElementIndex::InfoBoard, Vector2(757.0f, 205.0f) },
		{ UIElementIndex::BuyButton, Vector2(853.0f, 583.0f) },
		{ UIElementIndex::ItemViewport, Vector2(770.0f, 220.0f) },
		{ UIElementIndex::MoneyIcon, Vector2(865.0f, 590.0f) },
		{ UIElementIndex::MoneyLabel, Vector2(82.0f, 0.0f) },
		{ UIElementIndex::ItemLabel, Vector2(0.0f, -38.0f) },
		{ UIElementIndex::ItemStackLabel, Vector2(-13.0f, 12.0f) },
	};
	const std::unordered_map<UIElementIndex, int> UI_FONT_SIZE_MAP = {
		{ UIElementIndex::MoneyLabel, 24 },
		{ UIElementIndex::ItemLabel, 24 },
		{ UIElementIndex::ItemStackLabel, 20 },
	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	int previousPlayerMoney;
	bool canBuyItem;
	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;
	ItemIndex currentItem;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeUI();
	void Show();
	void Hide();
	void HideItemInfo();
	void UpdateItemCostLabel();
	void BuyCurrent();

public:

	ItemInfoUI();
	~ItemInfoUI();
	void UpdateInfoBoard(ItemIndex itemIndex);
	void Update() override;

};