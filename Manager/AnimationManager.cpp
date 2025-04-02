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
	animationClipMap.at(AnimationIndex::Player_Idle)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 16, 16, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Idle)->loop = true;

	// --- PLAYER PISTOL IDLE ---
	animationClipMap[AnimationIndex::Player_Pistol_Idle] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Pistol_Idle)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 304, 16, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Pistol_Idle)->loop = true;

	// --- PLAYER PISTOL SHOOT ---
	animationClipMap[AnimationIndex::Player_Pistol_Shoot] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Pistol_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.05f,
		.clip = { 16, 304, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Pistol_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 304, 304, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Pistol_Shoot)->loop = false;

	// --- PLAYER SHOTGUN IDLE ---
	animationClipMap[AnimationIndex::Player_Shotgun_Idle] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Shotgun_Idle)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 592, 16, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Shotgun_Idle)->loop = true;

	// --- PLAYER SHOTGUN SHOOT ---
	animationClipMap[AnimationIndex::Player_Shotgun_Shoot] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.035f,
		.clip = { 16, 592, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.04f,
		.clip = { 304, 592, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.07f,
		.clip = { 592, 592, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.08f,
		.clip = { 880, 592, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 1168, 592, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_Shotgun_Shoot)->loop = false;

	// --- PLAYER MED KIT ---
	animationClipMap[AnimationIndex::Player_MedKit] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_MedKit)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 880, 16, 256, 256 },
		});
	animationClipMap.at(AnimationIndex::Player_MedKit)->loop = true;

	// --- PLAYER RIFLE IDLE ---
	animationClipMap[AnimationIndex::Player_Rifle_Idle] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Rifle_Idle)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 1168, 16, 320, 320 },
		});
	animationClipMap.at(AnimationIndex::Player_Rifle_Idle)->loop = true;

	// --- PLAYER RIFLE SHOOT ---
	animationClipMap[AnimationIndex::Player_Rifle_Shoot] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), Layer::Player);
	animationClipMap.at(AnimationIndex::Player_Rifle_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 16, 880, 320, 320 },
		});
	animationClipMap.at(AnimationIndex::Player_Rifle_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.008f,
		.clip = { 368, 880, 320, 320 },
		});
	animationClipMap.at(AnimationIndex::Player_Rifle_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.01f,
		.clip = { 720, 880, 320, 320 },
		});
	animationClipMap.at(AnimationIndex::Player_Rifle_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.015f,
		.clip = { 1072, 880, 320, 320 },
		});
	animationClipMap.at(AnimationIndex::Player_Rifle_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.02f,
		.clip = { 1424, 880, 320, 320 },
		});
	animationClipMap.at(AnimationIndex::Player_Rifle_Shoot)->AddAnimationFrame(new AnimationFrame{
		.scale = PLAYER_SPRITE_SCALE,
		.duration = 0.0f,
		.clip = { 1776, 880, 320, 320 },
		});
}

AnimationManager::AnimationManager() {

	if (instance)
		throw std::exception("Animation Manager can only have one instance");

	instance = this;

	InitializeAnimation();

}

AnimationManager::~AnimationManager() {

	for (auto it = animationClipMap.begin(); it != animationClipMap.end(); it++)
		GameObject::Destroy(it->second);	// AnimationClip is a GameObject

	animationClipMap.clear();

	instance = nullptr;

}

AnimationClip* AnimationManager::GetAnimationClip(AnimationIndex animationIndex) {

	return animationClipMap.at(animationIndex);

}

AnimationManager* AnimationManager::Instance() { return instance; }