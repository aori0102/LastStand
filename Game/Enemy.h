#pragma once

#include <GameComponent.h>

class Enemy : public GameObject {

private:

	void Render();

	GameObject* healthBar;
	GameObject* target;

	float movementSpeed;

public:

	Enemy(GameObject* initTarget);

	void Update() override;
	void OnDestroy() override;

};