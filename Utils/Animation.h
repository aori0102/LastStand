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

class Image;
class Sprite;

class AnimationFrame {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	float scale;
	float duration;
	SDL_Rect clip;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	AnimationFrame(SDL_Rect initClip, float initDuration, float initScale)
		: clip(initClip), duration(initDuration), scale(initScale) {}

};

class AnimationClip : public GameObject {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	friend class AnimationController;
	friend class AnimationManager;

	float startTick;		// When the animation is played
	float currentFrameStartTick;
	float animationLength;
	bool isPlaying;
	bool loop;
	bool ended;
	std::vector<AnimationFrame*> animationTimeline;
	std::vector<AnimationFrame*>::iterator currentFrame;
	Sprite* animationSpriteSheet;

public:

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------
	
private:

	AnimationClip(Sprite* initAnimationSpriteSheet, Layer initLayer);

	void Play();
	void Stop();
	void EndAndReset();

	void Update() override;

	void AddAnimationFrame(AnimationFrame* animationFrame);

	void RenderCurrent(Vector2 position, Vector2 scale, float angle = 0.0f);
	bool IsPlaying() const;

	float GetAnimationLength() const;

};