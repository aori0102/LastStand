/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>
#include <string>
#include <vector>

#include <GameObject.h>
#include <SDL.h>
#include <Utils.h>

class Sprite;

struct AnimationFrame {

	float scale = 1.0f;
	float duration = 0.0f;
	SDL_Rect clip = { 0, 0, 0, 0 };

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
	void Play();
	void Stop();
	void EndAndReset();
	void AddAnimationFrame(AnimationFrame* animationFrame);
	void RenderCurrent(Vector2 position, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetSprite(Sprite* initAnimationSpriteSheet);
	void Update() override;
	bool IsPlaying() const;
	float GetAnimationLength() const;

public:

	AnimationClip();
	~AnimationClip();

};