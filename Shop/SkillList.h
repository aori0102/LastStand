#pragma once

#include <string>
#include <unordered_map>

#include <GameObject.h>
#include <Utils.h>

enum class MediaUI;
enum class PlayerAttribute;

enum class SkillListIndex {

	First,
	Second,
	Third,

	Total,
	None,

};

struct SkillNodeUI {

	GameObject* skillNodeBackground;
	GameObject* skillNodeVisual;
	GameObject* nodeConnector;

};

struct SkillInfo {

	int skillPoint;
	float value;
	std::string name;
	std::string description;
	PlayerAttribute playerAttribute;
	SkillListIndex listIndex;
	MediaUI skillVisualIndex;

};

class SkillNode {

private:

	friend class SkillList;

	bool acquired;
	bool available;
	SkillNode* next;
	SkillNodeUI* skillNodeUI;
	SkillInfo info;

public:

	SkillNode();
	~SkillNode();

};

class SkillList : public GameObject {

private:

	static const float SKILL_NODE_OFFSET;
	static const float SKILL_LIST_OFFSET;

	friend class Shop;

	std::unordered_map<SkillListIndex, SkillNode*> headNodeMap;
	std::unordered_map<SkillListIndex, SkillNode*> tailNodeMap;
	std::unordered_map<SkillListIndex, SkillNode*> currentNodeMap;
	std::unordered_map<SkillListIndex, int> skillProgressMap;
	std::unordered_map<SkillListIndex, int> tempProgressMap;	// To check if the skill is acquired
	
	SkillNode* selectedNode;

	int GetCurrentSkillCost() const;
	void AddSkill(SkillInfo info);
	void SetPosition(Vector2 position);
	void SelectNode(SkillNode* skillNode);
	SkillNode* UpgradeSelected();

public:

	SkillList();
	~SkillList();

};