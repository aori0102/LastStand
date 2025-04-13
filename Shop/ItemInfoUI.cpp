#include <ItemInfoUI.h>

#include <AudioManager.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <PlayerStatistic.h>
#include <Shop.h>
#include <Texture.h>

void ItemInfoUI::InitializeUI() {

	/// >>>
	/// --- UTILITY INFO BOARD ---
	/// >>>
	GameObject* infoBoard = GameObject::Instantiate("Item Info Board", Layer::Menu);
	Image* infoBoard_image = infoBoard->AddComponent<Image>();
	infoBoard_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityInfoBoard), true);
	infoBoard_image->showOnScreen = true;
	infoBoard->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::InfoBoard),
		infoBoard->transform->scale
	);
	infoBoard->Render = [infoBoard_image]() {
		infoBoard_image->Render();
		};
	uiElementMap[UIElementIndex::InfoBoard] = infoBoard;

	/// >>>
	/// --- UTILITY ITEM VIEWPORT ---
	/// >>>
	GameObject* itemViewport = GameObject::Instantiate("Item Info Viewport", Layer::Menu);
	Image* itemViewport_image = itemViewport->AddComponent<Image>();
	itemViewport_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityItemViewport), true);
	itemViewport_image->showOnScreen = true;
	itemViewport->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ItemViewport),
		itemViewport->transform->scale
	);
	itemViewport->Render = [itemViewport_image]() {
		itemViewport_image->Render();
		};
	uiElementMap[UIElementIndex::ItemViewport] = itemViewport;

	/// >>>
	/// --- UTILITY ITEM STACK LABEL ---
	/// >>>
	GameObject* itemStackLabel = GameObject::Instantiate("Item Info Stack Label", Layer::Menu);
	Text* itemStackLabel_text = itemStackLabel->AddComponent<Text>();
	itemStackLabel_text->LoadText("", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::ItemStackLabel));
	itemStackLabel_text->showOnScreen = true;
	Align::Right(itemStackLabel->transform, itemViewport->transform);
	Align::Bottom(itemStackLabel->transform, itemViewport->transform);
	itemStackLabel->transform->position += UI_POSITION_MAP.at(UIElementIndex::ItemStackLabel);
	itemStackLabel->Render = [itemStackLabel_text]() {
		itemStackLabel_text->Render();
		};
	uiElementMap[UIElementIndex::ItemStackLabel] = itemStackLabel;

	/// >>>
	/// --- UTILITY BUY BUTTON ---
	/// >>>
	GameObject* buyButton = GameObject::Instantiate("Item Info Buy Button", Layer::Menu);
	Image* buyButton_image = buyButton->AddComponent<Image>();
	buyButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityBuyButton), true);
	buyButton_image->showOnScreen = true;
	Button* infoBoard_button = buyButton->AddComponent<Button>();
	infoBoard_button->backgroundColor = Color::TRANSPARENT;
	infoBoard_button->OnClick = [this,infoBoard_button]() {
		BuyCurrent();
		return true;
		};
	buyButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::BuyButton),
		buyButton->transform->scale
	);
	buyButton->Render = [buyButton_image]() {
		buyButton_image->Render();
		};
	uiElementMap[UIElementIndex::BuyButton] = buyButton;

	/// >>>
	/// --- MONEY ICON ---
	/// >>>
	GameObject* moneyIcon = GameObject::Instantiate("Item Info Buy Button Money Icon", Layer::Menu);
	Image* moneyIcon_image = moneyIcon->AddComponent<Image>();
	moneyIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_MoneyIcon), true);
	moneyIcon_image->showOnScreen = true;
	moneyIcon->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::MoneyIcon),
		moneyIcon->transform->scale
	);
	moneyIcon->Render = [moneyIcon_image]() {
		moneyIcon_image->Render();
		};
	uiElementMap[UIElementIndex::MoneyIcon] = moneyIcon;

	/// >>>
	/// --- MONEY LABEL ---
	/// >>>
	GameObject* moneyLabel = GameObject::Instantiate("Item Info Buy Button Money Label", Layer::Menu);
	Text* moneyLabel_text = moneyLabel->AddComponent<Text>();
	moneyLabel_text->LoadText("12,000", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::MoneyLabel));
	moneyLabel_text->showOnScreen = true;
	Align::Left(moneyLabel->transform, uiElementMap.at(UIElementIndex::BuyButton)->transform);
	Align::MiddleVertically(moneyLabel->transform, uiElementMap.at(UIElementIndex::BuyButton)->transform);
	moneyLabel->transform->position += UI_POSITION_MAP.at(UIElementIndex::MoneyLabel);
	moneyLabel->Render = [moneyLabel_text]() {
		moneyLabel_text->Render();
		};
	uiElementMap[UIElementIndex::MoneyLabel] = moneyLabel;

	/// >>>
	/// --- ITEM VISUAL ---
	/// >>>
	GameObject* itemVisual = GameObject::Instantiate("Item Info Visual", Layer::Menu);
	Image* itemVisual_image = itemVisual->AddComponent<Image>();
	itemVisual_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_MoneyIcon), true);
	itemVisual_image->showOnScreen = true;
	itemVisual->transform->position = itemViewport->transform->position;
	itemVisual->Render = [itemVisual_image]() {
		itemVisual_image->Render();
		};
	uiElementMap[UIElementIndex::ItemVisual] = itemVisual;

	/// >>>
	/// --- ITEM LABEL ---
	/// >>>
	GameObject* itemLabel = GameObject::Instantiate("Item Info Label", Layer::Menu);
	Text* itemLabel_text = itemLabel->AddComponent<Text>();
	itemLabel_text->LoadText("<Item Name>", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::ItemLabel));
	itemLabel_text->showOnScreen = true;
	Align::Bottom(itemLabel->transform, uiElementMap.at(UIElementIndex::ItemViewport)->transform);
	Align::MiddleHorizontally(itemLabel->transform, uiElementMap.at(UIElementIndex::ItemViewport)->transform);
	itemLabel->transform->position += UI_POSITION_MAP.at(UIElementIndex::ItemLabel);
	itemLabel->Render = [itemLabel_text]() {
		itemLabel_text->Render();
		};
	uiElementMap[UIElementIndex::ItemLabel] = itemLabel;

}

void ItemInfoUI::Show() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

	if (currentItem == ItemIndex::None)
		HideItemInfo();

}

void ItemInfoUI::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

void ItemInfoUI::HideItemInfo() {

	uiElementMap.at(UIElementIndex::ItemVisual)->Disable();
	uiElementMap.at(UIElementIndex::ItemStackLabel)->Disable();
	uiElementMap.at(UIElementIndex::MoneyLabel)->Disable();
	uiElementMap.at(UIElementIndex::ItemLabel)->Disable();
	uiElementMap.at(UIElementIndex::BuyButton)->Disable();
	uiElementMap.at(UIElementIndex::MoneyIcon)->Disable();

}

void ItemInfoUI::UpdateItemCostLabel() {

	if (currentItem == ItemIndex::None) {

		canBuyItem = false;
		return;

	}

	int price = ItemManager::Instance()->GetItemPrice(currentItem);
	canBuyItem = PlayerStatistic::Instance()->IsMoneySufficient(price);

	GameObject* moneyLabel = uiElementMap.at(UIElementIndex::MoneyLabel);
	moneyLabel->GetComponent<Text>()->LoadText(
		std::to_string(price),
		canBuyItem ? Color::WHITE : Color::RED,
		UI_FONT_SIZE_MAP.at(UIElementIndex::MoneyLabel)
	);
	Align::Left(moneyLabel->transform, uiElementMap.at(UIElementIndex::BuyButton)->transform);
	moneyLabel->transform->position += UI_POSITION_MAP.at(UIElementIndex::MoneyLabel);

}

void ItemInfoUI::BuyCurrent() {

	if (currentItem == ItemIndex::None || !canBuyItem) {

		AudioManager::Instance()->PlayOneShot(MediaSFX::Invalid);
		return;

	}

	AudioManager::Instance()->PlayOneShot(MediaSFX::Coin);
	Shop::Instance()->BuyItem();

}

ItemInfoUI::ItemInfoUI() {

	InitializeUI();

	previousPlayerMoney = 0;
	canBuyItem = false;
	currentItem = ItemIndex::None;

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

ItemInfoUI::~ItemInfoUI() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	uiElementMap.clear();

}

void ItemInfoUI::UpdateInfoBoard(ItemIndex itemIndex) {

	currentItem = itemIndex;

	if (itemIndex == ItemIndex::None) {

		canBuyItem = false;
		HideItemInfo();
		return;

	}

	// Update viewport
	ItemManager::Instance()->LinkItemIcon(
		itemIndex, uiElementMap.at(UIElementIndex::ItemVisual)->GetComponent<Image>()
	);

	// Update label
	uiElementMap.at(UIElementIndex::ItemLabel)->GetComponent<Text>()->LoadText(
		ItemManager::Instance()->GetItemName(itemIndex), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::ItemLabel)
	);

	UpdateItemCostLabel();

	// Update stack label
	GameObject* itemStackLabel = uiElementMap.at(UIElementIndex::ItemStackLabel);
	GameObject* viewport = uiElementMap.at(UIElementIndex::ItemViewport);
	itemStackLabel->GetComponent<Text>()->LoadText(
		std::to_string(ItemManager::Instance()->GetItemShopStack(itemIndex)),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::ItemStackLabel)
	);
	Align::Right(itemStackLabel->transform, viewport->transform);
	Align::Bottom(itemStackLabel->transform, viewport->transform);
	itemStackLabel->transform->position += UI_POSITION_MAP.at(UIElementIndex::ItemStackLabel);

	Show();

}

void ItemInfoUI::Update() {

	if (IsActive() && previousPlayerMoney != PlayerStatistic::Instance()->GetMoney() && currentItem!=ItemIndex::None) {

		UpdateItemCostLabel();
		previousPlayerMoney = PlayerStatistic::Instance()->GetMoney();

	}

}