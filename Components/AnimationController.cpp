/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameComponent.h>

#include <algorithm>

#include <Animation.h>
#include <AnimationManager.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void AnimationController::OnComponentDestroyed() {

	for (auto it_node = animationNodeMap.begin(); it_node != animationNodeMap.end(); it_node++) {

		for (auto it_transition = it_node->second->transitionList.begin(); it_transition != it_node->second->transitionList.end(); it_transition++) {

			delete (*it_transition);
			*it_transition = nullptr;

		}

		delete it_node->second;
		it_node->second = nullptr;

	}

	animationNodeMap.clear();

	delete defaultAnimationNode;
	defaultAnimationNode = nullptr;

	delete currentAnimationNode;
	currentAnimationNode = nullptr;

}

void AnimationController::OnComponentUpdate() {

	if (!currentAnimationNode || !currentAnimationNode->IsEnded())
		return;

	for (AnimationTransition* transition : currentAnimationNode->transitionList) {

		if (transition->condition()) {

			currentAnimationNode->StopNode();
			currentAnimationNode = transition->to->PlayNode();
			return;

		}

	}

	if (currentAnimationNode->IsLoop())
		currentAnimationNode->PlayNode();

}

AnimationController::AnimationController(GameObject* initOwner) : GameComponent(initOwner) {

	defaultAnimationNode = nullptr;
	currentAnimationNode = nullptr;

	animationNodeMap = {};

}

void AnimationController::AddAnimationClip(AnimationIndex animationIndex, bool isStateMachine) {

	auto it_to = animationNodeMap.find(animationIndex);
	if (it_to != animationNodeMap.end())
		return;

	AnimationClip* animClip = nullptr;
	if (!isStateMachine)
		animClip = AnimationManager::Instance()->GetAnimationClip(animationIndex);

	animationNodeMap[animationIndex] = new AnimationNode(animClip, isStateMachine);

}

void AnimationController::AddTransition(AnimationIndex from, AnimationIndex to, std::function<bool()> condition) {

	try {

		auto it_from = animationNodeMap.find(from);
		if (it_from == animationNodeMap.end())
			throw std::exception("Animation controller cannot handle linking from an unassigned animation clip");

		auto it_to = animationNodeMap.find(to);
		if (it_to == animationNodeMap.end())
			throw std::exception("Animation controller cannot handle linking to an unassigned animation clip");

		auto it_transition = std::find_if(
			it_from->second->transitionList.begin(),
			it_from->second->transitionList.end(),
			[it_to](AnimationTransition* animTrans) { return it_to->second == animTrans->to; }
		);
		if (it_transition == it_from->second->transitionList.end())
			it_from->second->transitionList.push_back(new AnimationTransition{
				.to = it_to->second,
				.condition = condition
				});

	} catch (...) {

		std::cout << "Fatal! Unresolved error trying to add transition! Possibly forgoting to add the animation node?" << std::endl;

	}

}

void AnimationController::MakeDefault(AnimationIndex animationIndex) {

	auto it = animationNodeMap.find(animationIndex);
	if (it == animationNodeMap.end())
		throw std::exception("Animation clip is not linked");

	defaultAnimationNode = it->second;
	currentAnimationNode = defaultAnimationNode;

	currentAnimationNode->PlayNode();

}

void AnimationController::RenderCurrent(Vector2 position, Vector2 scale, float angle) {

	if (!currentAnimationNode)
		return;

	currentAnimationNode->RenderCurrent(position, angle);

}