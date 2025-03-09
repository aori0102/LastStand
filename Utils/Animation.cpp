#include <Animation.h>
#include <Texture.h>
#include <GameCore.h>

AnimationClip::AnimationClip(Sprite* initAnimationSpriteSheet) {

	if (!initAnimationSpriteSheet)
		throw new std::exception("Animation extracting from null sprite sheet");

	animationSpriteSheet = initAnimationSpriteSheet;

	startTick = 0.0f;
	isPlaying = false;
	animationLength = 0.0f;

	animationTimeline = std::set<AnimationFrame*, decltype(&AnimationFrame::Compare)>(&AnimationFrame::Compare);
	currentFrame = animationTimeline.begin();

}

void AnimationClip::Start() {

	startTick = GameCore::Time();

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

	if (GameCore::Time() - startTick >= (*currentFrame)->timePoint && currentFrame != animationTimeline.end())
		currentFrame++;

}

void AnimationClip::AddAnimationFrame(AnimationFrame* animationFrame) {

	if (!animationFrame)
		throw new std::exception("Adding null frame to animation");

	animationTimeline.insert(animationFrame);

	animationLength = std::max(animationLength, animationFrame->timePoint);

	currentFrame = animationTimeline.begin();

}

void AnimationClip::RenderCurrent(Vector2 position, Vector2 scale, float angle) {

	if (currentFrame == animationTimeline.end())
		return;

	GameCore::RenderCopy(animationSpriteSheet, position, scale * (*currentFrame)->scale, false, &((*currentFrame)->clip), angle);

}

float AnimationClip::GetAnimationLength() const { return animationLength; }