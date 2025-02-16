#pragma once

#include <GameComponent.h>

class Firearm;

class ReloadUI : public GameObject {

private:

	Firearm* linkedFirearm;

public:

	ReloadUI(Firearm* initFirearm);

	void Update() override;

};

class FirearmUI : public GameObject {

private:

	Firearm* linkedFirearm;

	int previousAmmo;

public:

	FirearmUI(Firearm* initFirearm);

	void Update() override;

};