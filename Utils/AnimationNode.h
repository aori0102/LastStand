/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>
#include <vector>

#include <Utils.h>

class AnimationClip;
class AnimationNode;

struct AnimationTransition {

	AnimationNode* to = nullptr;
	std::function<bool()> condition = []() { return true; };

};

class AnimationNode {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool isStateMachine;
	std::vector<AnimationTransition*> transitionList;
	AnimationClip* animationClip;

	friend class AnimationController;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	AnimationNode(AnimationClip* initAnimationClip, bool initIsStateMachine);
	~AnimationNode();
	void StopNode();
	AnimationNode* PlayNode();

public:

	bool IsLoop();
	bool IsEnded();
	bool IsStateMachine() const;
	void RenderCurrent(Vector2 position, float angle, SDL_RendererFlip flip = SDL_FLIP_NONE);

};