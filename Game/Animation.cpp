#include <Animation.h>
#include <Texture.h>
#include <Game.h>

AnimationClip::AnimationClip(Image* initAnimationSpriteSheet) {

	if (!initAnimationSpriteSheet)
		throw new exception("Animation extracting from null sprite sheet");

	animationSpriteSheet = initAnimationSpriteSheet;

	startTick = 0.0f;
	isPlaying = false;
	animationLength = 0.0f;

	animationTimeline = set<AnimationFrame*, decltype(&AnimationFrame::Compare)>(&AnimationFrame::Compare);
	currentFrame = animationTimeline.begin();

}

void AnimationClip::Start() {

	startTick = Game::Time();

	startTick = 0.0f;
	currentFrame = animationTimeline.begin();

	isPlaying = true;

}

void AnimationClip::Stop() {

	isPlaying = false;

}

void AnimationClip::Update() {

	if (!isPlaying)
		return;

	if (Game::Time() - startTick >= (*currentFrame)->timePoint && currentFrame != animationTimeline.end())
		currentFrame++;

}

void AnimationClip::AddAnimationFrame(AnimationFrame* animationFrame) {

	if (!animationFrame)
		throw new exception("Adding null frame to animation");

	animationTimeline.insert(animationFrame);

	animationLength = max(animationLength, animationFrame->timePoint);

	currentFrame = animationTimeline.begin();

}

void AnimationClip::RenderCurrent(Vector2 position, Vector2 scale, float angle) {

	if (currentFrame == animationTimeline.end())
		return;

	Game::RenderCopy(animationSpriteSheet, position, scale * (*currentFrame)->scale, false, &(*currentFrame)->clip, angle);

}

float AnimationClip::AnimationLength() { return animationLength; }