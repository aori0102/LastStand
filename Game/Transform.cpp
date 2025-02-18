#include <GameComponent.h>
#include <Physics.h>

Transform::Transform(GameObject* initOwner) : GameComponent(initOwner) {

	position = Vector2::zero;
	scale = Vector2(1.0f, 1.0f);

}

void Transform::Translate(Vector2 movementVector, bool tryNavigate) {

	HitInfo hitInfo;
	BoxCollider* collider = Owner()->GetComponent<BoxCollider>();

	// Only check for collision if there is a collider
	if (collider && Physics::BoxCast(collider, movementVector, &hitInfo)) {

		// The remaining distance that hasn't been covered
		float remainingDistance = (movementVector - (hitInfo.contactPoint - position)).Magnitude();

		// Assign new position for next check
		position = hitInfo.contactPoint;

		if (!tryNavigate)
			return;

		// Try navigate alongside the box
		// Try movement on x axis
		Vector2 movementAlongX = Vector2(movementVector.x, 0.0f).Normalize() * remainingDistance;
		if (Physics::BoxCast(collider, movementAlongX, &hitInfo)) {

			// Try movement on y axis
			Vector2 movementAlongY = Vector2(0.0f, movementVector.y).Normalize() * remainingDistance;
			if (!Physics::BoxCast(collider, movementAlongY, &hitInfo))
				position += movementAlongY;

		} else
			position += movementAlongX;

	} else
		position += movementVector;

}