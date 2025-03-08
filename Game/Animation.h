#pragma once

#include <SDL.h>
#include <set>
#include <string>
#include <GameComponent.h>

class Image;

class AnimationClip : public GameObject {

public:

	struct AnimationFrame {

		SDL_Rect clip;
		float timePoint;
		float scale;

		AnimationFrame(SDL_Rect initClip, float initTimePoint, float initScale)
			: clip(initClip), timePoint(initTimePoint), scale(initScale) {}

		static bool Compare(const AnimationFrame* a, const AnimationFrame* b) {
			return a->timePoint < b->timePoint;
		}

	};

private:

	Image* animationSpriteSheet;

	std::set<AnimationFrame*, decltype(&AnimationFrame::Compare)> animationTimeline;

	float startTick;		// When the animation is played
	float animationLength;
	std::set<AnimationFrame*, decltype(&AnimationFrame::Compare)>::iterator currentFrame;
	bool isPlaying;

public:

	AnimationClip(Image* initAnimationSpriteSheet);

	void Start();
	void Stop();

	void Update() override;

	void AddAnimationFrame(AnimationFrame* animationFrame);

	void RenderCurrent(Vector2 position, Vector2 scale, float angle = 0.0f);

	float AnimationLength();

};