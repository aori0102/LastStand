#include <Animation.h>

AnimationNode::AnimationNode(AnimationClip* initAnimationClip, bool initIsStateMachine) {

	animationClip = initAnimationClip;
	isStateMachine = initIsStateMachine;

	transitionList = {};

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

void AnimationNode::StopNode() {

	// If this is a state machine, it should not be playable at first
	if (!isStateMachine)
		animationClip->Stop();

}

bool AnimationNode::IsLoop() {

	return !isStateMachine && animationClip->loop;

}

bool AnimationNode::IsEnded() {

	return isStateMachine || animationClip->ended;

}

bool AnimationNode::IsStateMachine() const { return isStateMachine; }

void AnimationNode::RenderCurrent(Vector2 position, Vector2 scale, float angle) {

	if (isStateMachine) // This should not happen
		throw std::exception("Unexpected! this is a state machine!");

	animationClip->RenderCurrent(position, scale, angle);

}