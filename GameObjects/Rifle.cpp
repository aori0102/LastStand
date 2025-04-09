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

void Rifle::SetFirearmItemID(ItemIndex initItemIndex) {

	auto it_baseFirearmInfo = BASE_FIREARM_INFO_MAP.find(initItemIndex);
	if (it_baseFirearmInfo == BASE_FIREARM_INFO_MAP.end())
		throw std::exception("Firearm: Firearm data does not exist");

	switch (initItemIndex) {

	case ItemIndex::Rifle_M4:
		break;

	default:
		throw std::exception("Invalid ID for a rifle!");

	}

	attributeMap = BASE_FIREARM_INFO_MAP.at(initItemIndex).attributeMap;
	reloadType = BASE_FIREARM_INFO_MAP.at(initItemIndex).reloadType;

	SetIndex(initItemIndex);

}

bool Rifle::TryUse(Player* player) {
	
	if (!CanShoot())
		return false;

	OnShoot();
	float damage = attributeMap.at(FirearmAttributeIndex::Damage);
	bool isCrit = IsCrit();
	if (isCrit)
		damage *= (1.0f + attributeMap.at(FirearmAttributeIndex::CriticalDamage));

	AudioManager::Instance()->PlayOneShot(MediaSFX::RifleShot);

	// Won't cause memory leak because of self destruction
	Bullet* bullet = GameObject::Instantiate<Bullet>("Bullet", Layer::Bullet);
	bullet->SetUpBullet(player->transform->position, player->GetAimingDirection(), damage, isCrit);

	return true;

}