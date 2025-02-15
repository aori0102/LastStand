#pragma once

#include <GameComponent.h>

class Enemy : public GameObject {

private:

	void Render();

	GameObject* healthBar;

public:

	Enemy();

	void Update() override;

};