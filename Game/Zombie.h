#pragma once

#include <GameComponent.h>
#include <RenderManager.h>

class Zombie : public GameObject {

private:

	GameObject* healthBar;
	GameObject* target;

	float movementSpeed;

public:

	Zombie(GameObject* initTarget);

	void Update() override;
	void OnDestroy() override;

};