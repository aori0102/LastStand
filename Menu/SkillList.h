#pragma once

#include <string>
#include <unordered_map>

#include <GameComponent.h>
#include <Utils.h>

enum class PlayerAttribute;

enum class SkillListIndex {

	First,
	Second,
	Third,

};

struct SkillNodeUI {

	GameObject* skillNodeBackground;
	GameObject* skillNodeVisual;
	GameObject* nodeConnector;

	~SkillNodeUI() {
		delete skillNodeBackground;
		delete skillNodeVisual;
		delete nodeConnector;
	}

};

struct SkillNode {

	int skillPoint;

	bool acquired;
	bool available;

	float value;

	std::string name;
	std::string description;

	PlayerAttribute playerAttribute;

	SkillNode* next;

	SkillNodeUI* skillNodeUI;

};

class SkillList : public GameObject {

private:

	static const float SKILL_NODE_OFFSET;
	static const float SKILL_LIST_OFFSET;

	friend class Shop;

	std::unordered_map<SkillListIndex, SkillNode*> headNodeMap;
	std::unordered_map<SkillListIndex, SkillNode*> tailNodeMap;
	std::unordered_map<SkillListIndex, SkillNode*> currentNodeMap;
	
	SkillNode* selectedNode;

	SkillList();
	int GetCurrentSkillCost() const;
	void AddSkill(SkillListIndex skillListIndex, SkillNode* skillNode);
	void SetPosition(Vector2 position);
	void SelectNode(SkillNode* skillNode);
	SkillNode* UpgradeSelected();

};