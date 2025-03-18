/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

class AnimationClip;

enum class AnimationIndex {

	Player_Idle,
	Player_Pistol_Idle,
	Player_Pistol_Shoot,
	Player_Shotgun_Idle,
	Player_Shotgun_Shoot,

	Total,

};

class AnimationManager {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	static AnimationManager* instance;

	std::unordered_map<AnimationIndex, AnimationClip*> animationClipMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeAnimation();

public:

	AnimationManager();

	static AnimationManager* Instance();

	AnimationClip* GetAnimationClip(AnimationIndex animationIndex);

};