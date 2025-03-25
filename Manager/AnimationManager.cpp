/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <AnimationManager.h>

#include <exception>

#include <Animation.h>
#include <MediaManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

AnimationManager* AnimationManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void AnimationManager::InitializeAnimation() {

	// --- PLAYER IDLE ---
	animationClipMap[AnimationIndex::Player_Idle] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Idle)->AddAnimationFrame(new AnimationFrame(
		{ 16, 16, 256, 256 }, 0.0f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Idle)->loop = true;

	// --- PLAYER PISTOL IDLE ---
	animationClipMap[AnimationIndex::Player_Pistol_Idle] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Pistol_Idle)->AddAnimationFrame(new AnimationFrame(
		{ 304, 16, 256, 256 }, 0.0f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Pistol_Idle)->loop = true;

	// --- PLAYER PISTOL SHOOT ---
	animationClipMap[AnimationIndex::Player_Pistol_Shoot] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Pistol_Shoot)->AddAnimationFrame(new AnimationFrame(
		{ 16, 304, 256, 256 }, 0.05f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Pistol_Shoot)->AddAnimationFrame(new AnimationFrame(
		{ 304, 304, 256, 256 }, 0.0f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Pistol_Shoot)->loop = false;

	// --- PLAYER SHOTGUN IDLE ---
	animationClipMap[AnimationIndex::Player_Shotgun_Idle] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Shotgun_Idle)->AddAnimationFrame(new AnimationFrame(
		{ 592, 16, 256, 256 }, 0.0f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Shotgun_Idle)->loop = true;

	// --- PLAYER SHOTGUN SHOOT ---
	animationClipMap[AnimationIndex::Player_Shotgun_Shoot] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame(
		{ 16, 592, 256, 256 }, 0.035f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame(
		{ 304, 592, 256, 256 }, 0.04f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame(
		{ 592, 592, 256, 256 }, 0.07f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame(
		{ 880, 592, 256, 256 }, 0.08f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame(
		{ 1168, 592, 256, 256 }, 0.0f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->loop = false;

	// --- PLAYER MED KIT ---
	animationClipMap[AnimationIndex::Player_MedKit] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_MedKit)->AddAnimationFrame(new AnimationFrame(
		{ 880, 16, 256, 256 }, 0.0f, 5.0f
	));
	animationClipMap.at(AnimationIndex::Player_MedKit)->loop = true;

}

AnimationManager::AnimationManager() {

	if (instance)
		throw std::exception("Animation Manager can only have one instance");

	instance = this;

	InitializeAnimation();

}

AnimationManager* AnimationManager::Instance() { return instance; }

AnimationClip* AnimationManager::GetAnimationClip(AnimationIndex animationIndex) {

	return animationClipMap.at(animationIndex);

}