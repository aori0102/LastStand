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