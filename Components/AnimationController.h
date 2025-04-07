/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>

#include <GameComponent.h>

class AnimationNode;
class GameObject;
enum class AnimationIndex;

class AnimationController : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<AnimationIndex, AnimationNode*> animationNodeMap;
	AnimationNode* defaultAnimationNode;
	AnimationNode* currentAnimationNode;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void OnComponentDestroyed() override;
	void OnComponentUpdate() override;

public:

	AnimationController(GameObject* initOwner);
	void AddAnimationClip(AnimationIndex animationIndex, bool isStateMachine = false);
	void AddTransition(AnimationIndex from, AnimationIndex to, std::function<bool()> condition = []() { return true; });
	void MakeDefault(AnimationIndex animationIndex);
	void RenderCurrent(Vector2 position, Vector2 scale, float angle);

};