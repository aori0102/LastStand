#include <SkillList.h>

#include <exception>

#include <MediaManager.h>
#include <Player.h>
#include <Shop.h>
#include <Texture.h>

const float SkillList::SKILL_NODE_OFFSET = 87.0f;
const float SkillList::SKILL_LIST_OFFSET = 104.0f;

int SkillList::GetCurrentSkillCost() const { return selectedNode ? selectedNode->skillPoint : INT_MAX; }

void SkillList::AddSkill(SkillListIndex skillListIndex, SkillNode* skillNode) {

	SkillNodeUI* skillNodeUI = new SkillNodeUI;

	skillNode->skillNodeUI = skillNodeUI;
	skillNode->next = nullptr;
	skillNode->acquired = false;
	skillNode->available = false;

	skillNodeUI->skillNodeBackground = GameObject::Instantiate("Skill Node Background", Layer::Menu);
	Image* skillNodeBackground_image = skillNodeUI->skillNodeBackground->AddComponent<Image>();
	skillNodeBackground_image->showOnScreen = true;
	skillNodeBackground_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillNode), true);
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
	skillNodeVisual_image->transform->position = skillNodeUI->skillNodeBackground->transform->position;
	skillNodeUI->skillNodeVisual->Render = [this, skillNodeVisual_image]() {
		if (IsActive())
			skillNodeVisual_image->Render();
		};

	if (!headNodeMap.at(skillListIndex)) {
		// This is the first node

		headNodeMap.at(skillListIndex) = skillNode;
		currentNodeMap.at(skillListIndex) = skillNode;
		tailNodeMap.at(skillListIndex) = skillNode;
		skillNode->available = true;
		return;

	}

	// Add connection to the previous node
	SkillNode* tailNode = tailNodeMap.at(skillListIndex);
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
	tailNodeMap.at(skillListIndex) = skillNode;

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

	Shop::Instance()->SelectSkillNode(skillNode);

}

SkillNode* SkillList::UpgradeSelected() {

	if (!selectedNode || !selectedNode->available || selectedNode->acquired)
		return nullptr;

	selectedNode->skillNodeUI->skillNodeBackground->GetComponent<Image>()->LinkSprite(
		MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillNode_Acquired), true
	);

	// Modify attribute after upgrade
	Player::Instance()->SetAttribute(selectedNode->playerAttribute, selectedNode->value);

	selectedNode->acquired = true;
	if (selectedNode->next)
		selectedNode->next->available = true;

	return selectedNode;

}

SkillList::SkillList() {

	headNodeMap = {
		{ SkillListIndex::First, nullptr },
		{ SkillListIndex::Second, nullptr },
		{ SkillListIndex::Third, nullptr },
	};
	tailNodeMap = {
		{ SkillListIndex::First, nullptr },
		{ SkillListIndex::Second, nullptr },
		{ SkillListIndex::Third, nullptr },
	};
	currentNodeMap = {
		{ SkillListIndex::First, nullptr },
		{ SkillListIndex::Second, nullptr },
		{ SkillListIndex::Third, nullptr },
	};
	selectedNode = nullptr;

}