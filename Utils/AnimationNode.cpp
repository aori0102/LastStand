/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Animation.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

AnimationNode::AnimationNode(AnimationClip* initAnimationClip, bool initIsStateMachine) {

	isStateMachine = initIsStateMachine;
	transitionList = {};
	animationClip = initAnimationClip;

}

AnimationNode::~AnimationNode() {

	for (auto it = transitionList.begin(); it != transitionList.end(); it++)
		delete (*it);

	transitionList.clear();

}

void AnimationNode::StopNode() {

	// If this is a state machine, it should not be playable at first
	if (!isStateMachine)
		animationClip->Stop();

}

AnimationNode* AnimationNode::PlayNode() {

	// This is a state machine
	if (isStateMachine) {

		for (AnimationTransition* transition : transitionList) {

			if (transition->condition()) {

				transition->to->PlayNode();
				return transition->to;

			}

		}

		// This state machine doesn't have an exit (no transition to a suitable
		// animation node). Throw exception since a state machine cannot be played
		throw std::exception("State machine doesn't have escape route! (Missing state)");

	}

	animationClip->Play();
	return this;

}

bool AnimationNode::IsLoop() {

	return !isStateMachine && animationClip->loop;

}

bool AnimationNode::IsEnded() {

	return isStateMachine || animationClip->ended;

}

bool AnimationNode::IsStateMachine() const { return isStateMachine; }

void AnimationNode::RenderCurrent(Vector2 position, float angle) {

	if (isStateMachine) // This should not happen
		throw std::exception("Unexpected! this is a state machine!");

	animationClip->RenderCurrent(position, angle);

}