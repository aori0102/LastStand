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
	Player_MedKit,
	Player_Item_Transition,

	Total,

};

class AnimationManager {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<AnimationIndex, AnimationClip*> animationClipMap;

	static AnimationManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeAnimation();

public:

	AnimationManager();
	~AnimationManager();
	AnimationClip* GetAnimationClip(AnimationIndex animationIndex);

	static AnimationManager* Instance();

};