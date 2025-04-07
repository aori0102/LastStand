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

void AnimationClip::RenderCurrent(Vector2 position, float angle) {

	if (currentFrame == animationTimeline.end())
		return;

	AnimationFrame* frame = *currentFrame;

	std::cout << frame << std::endl;
	std::cout << animationSpriteSheet << std::endl;

	Vector2 scale(frame->clip.w, frame->clip.h);

	GameCore::RenderCopy(animationSpriteSheet, position, scale * frame->scale, false, GetLayer(), &(frame->clip), angle);

}

void AnimationClip::SetSprite(Sprite* initAnimationSpriteSheet) {

	animationSpriteSheet = initAnimationSpriteSheet;

}

void AnimationClip::Update() {

	if (!isPlaying)
		return;

	if (!animationSpriteSheet)
		throw std::exception("AnimationClip was not initialized with a sprite sheet!");

	if (GameCore::Time() >= currentFrameStartTick + (*currentFrame)->duration) {

		currentFrame++;

		currentFrameStartTick = GameCore::Time();

		if (currentFrame == animationTimeline.end())
			EndAndReset();

	}

}

float AnimationClip::GetAnimationLength() const { return animationLength; }

bool AnimationClip::IsPlaying() const { return isPlaying; }

AnimationClip::AnimationClip() {

	isPlaying = false;
	loop = false;
	ended = false;
	startTick = 0.0f;
	currentFrameStartTick = 0.0f;
	animationLength = 0.0f;
	animationTimeline = {};
	currentFrame = animationTimeline.begin();
	animationSpriteSheet = nullptr;

}

AnimationClip::~AnimationClip() {

	animationSpriteSheet = nullptr;

	for (auto it = animationTimeline.begin(); it != animationTimeline.end(); it++)
		delete (*it);

	animationTimeline.clear();

}