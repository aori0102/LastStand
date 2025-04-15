#include <SkillList.h>

#include <exception>

#include <DataManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <PlayerStatistic.h>
#include <Shop.h>
#include <Texture.h>

const float SkillList::SKILL_NODE_OFFSET = 87.0f;
const float SkillList::SKILL_LIST_OFFSET = 104.0f;

int SkillList::GetCurrentSkillCost() const { return selectedNode ? selectedNode->info.skillPoint : INT_MAX; }

void SkillList::AddSkill(SkillInfo info) {

	SkillNodeUI* skillNodeUI = new SkillNodeUI;
	SkillNode* skillNode = new SkillNode;

	skillNode->skillNodeUI = skillNodeUI;
	skillNodeUI->nodeConnector = nullptr;
	skillNode->info = info;
	skillNode->next = nullptr;

	skillNode->available = false;

	if (tempProgressMap.at(info.listIndex) == skillProgressMap.at(info.listIndex))
		skillNode->available = true;
	else if (tempProgressMap.at(info.listIndex) < skillProgressMap.at(info.listIndex))
		skillNode->acquired = true;

	tempProgressMap.at(info.listIndex)++;

	skillNodeUI->skillNodeBackground = GameObject::Instantiate("Skill Node Background", Layer::Menu);
	Image* skillNodeBackground_image = skillNodeUI->skillNodeBackground->AddComponent<Image>();
	skillNodeBackground_image->showOnScreen = true;
	skillNodeBackground_image->LinkSprite(
		MediaManager::Instance()->GetUISprite(skillNode->acquired ? MediaUI::Shop_SkillNode_Acquired : MediaUI::Shop_SkillNode),
		true
	);
	skillNodeBackground_image->transform->position.x += SKILL_NODE_OFFSET;
	Button* skillNodeVisual_button = skillNodeUI->skillNodeBackground->AddComponent<Button>();
	skillNodeVisual_button->backgroundColor = Color::TRANSPARENT;
	skillNodeVisual_button->OnClick = [this, skillNode]() {
		if (!IsActive())
			return false;
		SelectNode(skillNode);
		return true;
		};
	skillNodeUI->skillNodeBackground->Render = [this, skillNodeBackground_image]() {
		if (IsActive())
			skillNodeBackground_image->Render();
		};

	skillNodeUI->skillNodeVisual = GameObject::Instantiate("Skill Node Visual", Layer::Menu);
	Image* skillNodeVisual_image = skillNodeUI->skillNodeVisual->AddComponent<Image>();
	skillNodeVisual_image->showOnScreen = true;
	skillNodeVisual_image->LinkSprite(MediaManager::Instance()->GetUISprite(info.skillVisualIndex), true);
	skillNodeVisual_image->transform->position = skillNodeUI->skillNodeBackground->transform->position;
	skillNodeUI->skillNodeVisual->Render = [this, skillNodeVisual_image]() {
		if (IsActive())
			skillNodeVisual_image->Render();
		};

	if (!headNodeMap.at(info.listIndex)) {
		// This is the first node

		headNodeMap.at(info.listIndex) = skillNode;
		currentNodeMap.at(info.listIndex) = skillNode;
		tailNodeMap.at(info.listIndex) = skillNode;
		return;

	}

	// Add connection to the previous node
	SkillNode* tailNode = tailNodeMap.at(info.listIndex);
	tailNode->skillNodeUI->nodeConnector = GameObject::Instantiate("Node Connector", Layer::Menu);
	Image* nodeConnector_image = tailNode->skillNodeUI->nodeConnector->AddComponent<Image>();
	nodeConnector_image->showOnScreen = true;
	nodeConnector_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillConnector), true);
	nodeConnector_image->transform->position =
		(skillNode->skillNodeUI->skillNodeBackground->transform->position + tailNode->skillNodeUI->skillNodeBackground->transform->position) / 2.0f;
	Align::MiddleVertically(nodeConnector_image->transform, tailNode->skillNodeUI->skillNodeBackground->transform);
	tailNode->skillNodeUI->nodeConnector->Render = [this, nodeConnector_image, tailNode]() {
		if (IsActive() && tailNode->acquired)
			nodeConnector_image->Render();
		};

	tailNode->next = skillNode;
	tailNodeMap.at(info.listIndex) = skillNode;

}

void SkillList::SetPosition(Vector2 position) {

	Vector2 currentPosition = position;

	for (int i = 0; i <= static_cast<int>(SkillListIndex::Third); i++) {

		SkillListIndex skillListIndex = static_cast<SkillListIndex>(i);

		SkillNode* temp = headNodeMap.at(skillListIndex);
		SkillNode* prev = nullptr;
		SkillNodeUI* tempNodeUI = nullptr;

		while (temp) {

			tempNodeUI = temp->skillNodeUI;

			tempNodeUI->skillNodeBackground->transform->position = Math::SDLToC00(
				currentPosition, tempNodeUI->skillNodeBackground->transform->scale
			);
			tempNodeUI->skillNodeVisual->transform->position = tempNodeUI->skillNodeBackground->transform->position;

			if (prev) {

				prev->skillNodeUI->nodeConnector->transform->position =
					(prev->skillNodeUI->skillNodeBackground->transform->position + tempNodeUI->skillNodeBackground->transform->position) / 2.0f;
				Align::MiddleVertically(prev->skillNodeUI->nodeConnector->transform, tempNodeUI->skillNodeVisual->transform);
			}

			currentPosition.x += SKILL_NODE_OFFSET;
			prev = temp;
			temp = temp->next;

		}

		currentPosition.x = position.x;
		currentPosition.y += SKILL_LIST_OFFSET;

	}

}

void SkillList::SelectNode(SkillNode* skillNode) {

	if (!skillNode || skillNode == selectedNode)
		return;

	if (!skillNode->acquired)
		skillNode->skillNodeUI->skillNodeBackground->GetComponent<Image>()->LinkSprite(
			MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillNode_Selected), true
		);

	if (selectedNode && !selectedNode->acquired)
		selectedNode->skillNodeUI->skillNodeBackground->GetComponent<Image>()->LinkSprite(
			MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillNode), true
		);

	selectedNode = skillNode;

	Shop::Instance()->SelectSkillNode(selectedNode->info);

}

void SkillList::Show() {

	for (auto it = headNodeMap.begin(); it != headNodeMap.end(); it++) {

		auto node = it->second;
		while (node && node->skillNodeUI) {

			if (node->skillNodeUI->nodeConnector)
				node->skillNodeUI->nodeConnector->Enable();
			node->skillNodeUI->skillNodeBackground->Enable();
			node->skillNodeUI->skillNodeVisual->Enable();

			node = node->next;

		}

	}

}

void SkillList::Hide() {

	for (auto it = headNodeMap.begin(); it != headNodeMap.end(); it++) {

		auto node = it->second;
		while (node && node->skillNodeUI) {

			if (node->skillNodeUI->nodeConnector)
				node->skillNodeUI->nodeConnector->Disable();
			node->skillNodeUI->skillNodeBackground->Disable();
			node->skillNodeUI->skillNodeVisual->Disable();

			node = node->next;

		}

	}

}

SkillNode* SkillList::UpgradeSelected() {

	if (!selectedNode || !selectedNode->available || selectedNode->acquired)
		return nullptr;

	if (!PlayerStatistic::Instance()->TryConsumeSkillPoint(selectedNode->info.skillPoint))
		return nullptr;

	selectedNode->skillNodeUI->skillNodeBackground->GetComponent<Image>()->LinkSprite(
		MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillNode_Acquired), true
	);

	// Modify attribute after upgrade
	Player::Instance()->SetAttribute(selectedNode->info.playerAttribute, selectedNode->info.value);

	selectedNode->acquired = true;
	selectedNode->available = false;
	if (selectedNode->next)
		selectedNode->next->available = true;
	skillProgressMap.at(selectedNode->info.listIndex)++;

	return selectedNode;

}

SkillList::SkillList() {

	for (int i = 0; i < static_cast<int>(SkillListIndex::Total); i++) {

		headNodeMap[static_cast<SkillListIndex>(i)] = nullptr;
		tailNodeMap[static_cast<SkillListIndex>(i)] = nullptr;
		currentNodeMap[static_cast<SkillListIndex>(i)] = nullptr;
		tempProgressMap[static_cast<SkillListIndex>(i)] = 0;
		skillProgressMap = DataManager::Instance()->playerSaveData->skillProgress;

	}

	selectedNode = nullptr;

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

SkillList::~SkillList() {

	// Save progress
	PlayerSaveData* saveData = DataManager::Instance()->playerSaveData;

	for (auto it = skillProgressMap.begin(); it != skillProgressMap.end(); it++)
		saveData->skillProgress[it->first] = it->second;

	for (auto it = headNodeMap.begin(); it != headNodeMap.end(); it++) {

		SkillNode* temp = it->second;
		while (temp) {

			SkillNode* next = temp->next;
			delete temp;
			temp = next;

		}

	}

}

void SkillList::Reset() {

	headNodeMap.clear();
	tailNodeMap.clear();
	currentNodeMap.clear();
	skillProgressMap.clear();

	for (int i = 0; i < static_cast<int>(SkillListIndex::Total); i++) {

		headNodeMap[static_cast<SkillListIndex>(i)] = nullptr;
		tailNodeMap[static_cast<SkillListIndex>(i)] = nullptr;
		currentNodeMap[static_cast<SkillListIndex>(i)] = nullptr;
		skillProgressMap[static_cast<SkillListIndex>(i)] = 0;

	}

	for (auto it = headNodeMap.begin(); it != headNodeMap.end(); it++) {

		SkillNode* temp = it->second;
		while (temp) {

			SkillNode* next = temp->next;
			delete temp;
			temp = next;

		}

	}

	selectedNode = nullptr;

}