/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>
#include <string>
#include <vector>

#include <GameComponent.h>
#include <SDL.h>

class AnimationClip;
class Image;
class Sprite;

struct AnimationTransition {

	AnimationNode* to = nullptr;
	std::function<bool()> condition = []() { return true; };

};

struct AnimationFrame {

	float scale = 1.0f;
	float duration = 0.0f;
	SDL_Rect clip = { 0, 0, 0, 0 };

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
	void RenderCurrent(Vector2 position, Vector2 scale, float angle);

};

class AnimationClip : public GameObject {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool isPlaying;
	bool loop;
	bool ended;
	float startTick;		// When the animation is played
	float currentFrameStartTick;
	float animationLength;
	std::vector<AnimationFrame*> animationTimeline;
	std::vector<AnimationFrame*>::iterator currentFrame;
	Sprite* animationSpriteSheet;

	friend class AnimationManager;
	friend class AnimationNode;

public:

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------
	
private:

	AnimationClip(Sprite* initAnimationSpriteSheet, Layer initLayer);
	void Play();
	void Stop();
	void EndAndReset();
	void AddAnimationFrame(AnimationFrame* animationFrame);
	void RenderCurrent(Vector2 position, Vector2 scale, float angle = 0.0f);
	void Update() override;
	void OnDestroy() override;
	bool IsPlaying() const;
	float GetAnimationLength() const;

};