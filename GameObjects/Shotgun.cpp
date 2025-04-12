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

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int Shotgun::PELLET = 8;
const float Shotgun::PELLET_SPAN_DEGREE = 12.0f;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Shotgun::SetFirearmItemID(ItemIndex initItemIndex) {

	auto it_baseFirearmInfo = BASE_FIREARM_INFO_MAP.find(initItemIndex);
	if (it_baseFirearmInfo == BASE_FIREARM_INFO_MAP.end())
		throw std::exception("Firearm: Firearm data does not exist");

	switch (initItemIndex) {

	case ItemIndex::Shotgun_Beretta1301:
		break;

	default:
		throw std::exception("Invalid ID for a shotgun!");

	}

	reloadType = BASE_FIREARM_INFO_MAP.at(initItemIndex).reloadType;

	SetIndex(initItemIndex);

}

bool Shotgun::TryUse() {

	if (!CanShoot())
		return false;

	OnShoot();
	float baseDamage = firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::Damage);;
	float damage;
	bool isCrit;
	Vector2 direction = Player::Instance()->GetAimingDirection();

	AudioManager::Instance()->PlayOneShot(MediaSFX::ShotgunShot);

	for (int i = 0; i < PELLET; i++) {

		isCrit = IsCrit();

		if (isCrit)
			damage = baseDamage * (1.0f + firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::CriticalDamage));
		else
			damage = baseDamage;

		float angle = Math::DegToRad(Random::Float(-PELLET_SPAN_DEGREE, PELLET_SPAN_DEGREE));

		// Won't cause memory leak because of self destruction
		Bullet* bullet = GameObject::Instantiate<Bullet>("Bullet", Layer::Bullet);
		bullet->SetUpBullet(Player::Instance()->transform->position, Player::Instance()->GetAimingDirection(), damage, isCrit);

	}

	return true;

}