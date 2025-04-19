/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <SkillList.h>

#include <Player.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

SkillNode::SkillNode() {

	acquired = false;
	available = false;
	next = nullptr;
	skillNodeUI = nullptr;

	info = SkillInfo();

}

SkillNode::~SkillNode() {

	if (skillNodeUI) {

		GameObject::Destroy(skillNodeUI->nodeConnector);
		skillNodeUI->nodeConnector = nullptr;

		GameObject::Destroy(skillNodeUI->skillNodeVisual);
		skillNodeUI->skillNodeVisual = nullptr;

		GameObject::Destroy(skillNodeUI->skillNodeBackground);
		skillNodeUI->skillNodeBackground = nullptr;

		delete skillNodeUI;

	}

	next = nullptr;

}