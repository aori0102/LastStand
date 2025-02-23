#pragma once

#include <GameComponent.h>
#include <RenderManager.h>

class Zombie : public GameObject {

private:

	void Render();

	GameObject* healthBar;
	GameObject* target;

	float movementSpeed;

public:

	Zombie(GameObject* initTarget);

	void Update() override;
	void OnDestroy() override;

};