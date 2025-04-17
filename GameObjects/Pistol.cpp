/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <exception>

#include <AudioManager.h>
#include <Bullet.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <Transform.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Pistol::SetIndex(ItemIndex initItemIndex) {

	if (!ItemManager::Instance()->IsIndexOfType<Pistol>(initItemIndex))
		throw std::exception("Invalid index for type Pistol.");

	itemIndex = initItemIndex;

}

bool Pistol::TryUse() {

	if (!CanShoot())
		return false;

	OnShoot();
	float damage = firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::Damage);
	bool isCrit = IsCrit();
	if (isCrit)
		damage *= (1.0f + firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::CriticalDamage));

	AudioManager::Instance()->PlayOneShot(MediaSFX::PistolShot);

	// Won't cause memory leak because of self destruction
	Bullet* bullet = GameObject::Instantiate<Bullet>("Bullet", Layer::Bullet);
	bullet->SetUpBullet(Player::Instance()->transform->position, Player::Instance()->GetAimingDirection(), damage, isCrit);

	return true;

}