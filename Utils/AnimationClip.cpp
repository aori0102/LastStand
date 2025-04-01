/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Animation.h>

#include <GameCore.h>
#include <Texture.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

AnimationClip::AnimationClip(Sprite* initAnimationSpriteSheet, Layer initLayer) : GameObject("Animation", initLayer) {

	if (!initAnimationSpriteSheet)
		throw std::exception("Animation extracting from null sprite sheet");

	isPlaying = false;
	loop = false;
	ended = false;
	startTick = 0.0f;
	currentFrameStartTick = 0.0f;
	animationLength = 0.0f;
	animationTimeline = {};
	currentFrame = animationTimeline.begin();
	animationSpriteSheet = initAnimationSpriteSheet;

}

void AnimationClip::Play() {

	if (isPlaying)
		return;

	startTick = GameCore::Time();
	currentFrameStartTick = startTick;

	isPlaying = true;
	ended = false;

}

void AnimationClip::Stop() {

	if (!isPlaying)
		return;

	isPlaying = false;

}

void AnimationClip::EndAndReset() {

	currentFrame = animationTimeline.begin();

	isPlaying = false;
	ended = true;

}

void AnimationClip::AddAnimationFrame(AnimationFrame* animationFrame) {

	if (!animationFrame)
		throw std::exception("Trying to add a NULL frame to an AnimationClip");

	animationTimeline.push_back(animationFrame);

	animationLength += animationFrame->duration;

	currentFrame = animationTimeline.begin();

}

void AnimationClip::RenderCurrent(Vector2 position, Vector2 scale, float angle) {

	if (currentFrame == animationTimeline.end())
		return;

	GameCore::RenderCopy(animationSpriteSheet, position, scale * (*currentFrame)->scale, false, GetLayer(), &((*currentFrame)->clip), angle);

}

void AnimationClip::Update() {

	if (!isPlaying)
		return;

	if (GameCore::Time() >= currentFrameStartTick + (*currentFrame)->duration) {

		currentFrame++;

		currentFrameStartTick = GameCore::Time();

		if (currentFrame == animationTimeline.end())
			EndAndReset();

	}

}

void AnimationClip::OnDestroy() {

	animationSpriteSheet = nullptr;

	for (auto it = animationTimeline.begin(); it != animationTimeline.end(); it++)
		delete (*it);

	animationTimeline.clear();

}

float AnimationClip::GetAnimationLength() const { return animationLength; }

bool AnimationClip::IsPlaying() const { return isPlaying; }