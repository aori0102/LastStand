#include <Physics.h>
#include <GameComponent.h>
#include <Type.h>
#include <Game.h>

// This value is used to set a small margin between objects. To prevent
// object going through each other due to small calculation difference
const float MOVEMENT_PERCENTAGE = 0.99f;

unordered_set<BoxCollider*> Physics::boxColliderSet = {};

void Physics::RegisterBoxCollider(BoxCollider* boxCollider) {

	boxColliderSet.insert(boxCollider);

}

void Physics::UnregisterBoxCollider(BoxCollider* boxCollider) {

	cout << "Deleting " << boxCollider << endl;
	boxColliderSet.erase(boxCollider);

}

bool Physics::BoxCast(BoxCollider* collider, Vector2 movementVector, HitInfo* hitInfo) {

	if (movementVector == Vector2::zero)
		return false;

	// Get this collider's bound
	Bound thisBound = collider->GetBound();

	// Get starting and ending point
	Vector2 start = thisBound.center;
	Vector2 end = start + movementVector;

	// The slope of the line containing movement vector
	float slope = (movementVector.x != 0.0f) ? movementVector.y / movementVector.x : FLT_MAX;

	// Output
	float distanceToCollision = movementVector.Magnitude();
	bool isCollided = false;
	BoxCollider* finalCollider = nullptr;

	for (BoxCollider* otherCollier : boxColliderSet) {

		if (otherCollier == collider)
			continue;

		// Get other bound
		Bound otherBound = otherCollier->GetBound();

		// Calculate the area of possible collision
		// These values are the bounds of the other collider
		// added with the extents of the original collider, hence
		// the result is the center of the original collider
		// where a collision can happen
		float minX = otherBound.Left() - thisBound.extents.x;
		float maxX = otherBound.Right() + thisBound.extents.x;
		float minY = otherBound.Top() - thisBound.extents.y;
		float maxY = otherBound.Bottom() + thisBound.extents.y;

		// Variable for collision calculation
		Vector2 contactPoint;
		float collisionTime;
		float distance;

		// ---------------------------------------
		// Check collision on left side (min x)
		// ---------------------------------------
		// If the movement vector is vertical and the center is
		// on the same line as minX, no collision is possible
		if (slope == FLT_MAX && minX == thisBound.center.x)
			continue;

		// The intersection of minX and movement line is the center
		// of the original collider when there is a collision
		// Calculate collision x
		contactPoint.x = minX;

		// Validate collision (Broad)
		collisionTime = (start - contactPoint).x / (start - end).x;
		if (collisionTime >= 0.0f && collisionTime <= 1.0f && movementVector.x > 0.0f) {

			// Calculate collision y
			contactPoint.y = slope * (minX - thisBound.center.x) + thisBound.center.y;

			// Construct the bound for this collision
			Bound onCollisionBound;
			onCollisionBound.center = contactPoint;
			onCollisionBound.extents = thisBound.extents;

			// Validate collision (Final)
			if (onCollisionBound.Top() <= otherBound.Bottom() && onCollisionBound.Bottom() >= otherBound.Top()) {

				// There is a collision
				isCollided = true;

				Game::SetRenderDrawColor(Color::GREEN);
				SDL_RenderDrawLineF(Game::gRenderer, 0.0f, contactPoint.y, 2000.0f, contactPoint.y);
				SDL_RenderDrawLineF(Game::gRenderer, contactPoint.x, 0.0f, contactPoint.x, 2000.0f);

				distance = (contactPoint - start).Magnitude();

				// Check if this collision comes first
				if (distance < distanceToCollision) {

					distanceToCollision = distance;
					if (hitInfo) {

						hitInfo->otherCollider = otherCollier;
						finalCollider = otherCollier;
						hitInfo->contactPoint = contactPoint;

					}

				}

			}

		}

		// ---------------------------------------
		// Check collision on right side (max x)
		// ---------------------------------------
		// If the movement vector is vertical and the center is
		// on the same line as maxX, no collision is possible
		if (slope == FLT_MAX && maxX == thisBound.center.x)
			continue;

		// The intersection of maxX and movement line is the center
		// of the original collider when there is a collision
		// Calculate collision x
		contactPoint.x = maxX;

		// Validate collision (Broad)
		collisionTime = (start - contactPoint).x / (start - end).x;
		if (collisionTime >= 0.0f && collisionTime <= 1.0f && movementVector.x < 0.0f) {

			// Calculate collision y
			contactPoint.y = slope * (maxX - thisBound.center.x) + thisBound.center.y;

			// Construct the bound for this collision
			Bound onCollisionBound;
			onCollisionBound.center = contactPoint;
			onCollisionBound.extents = thisBound.extents;

			// Validate collision (Final)
			if (onCollisionBound.Top() <= otherBound.Bottom() && onCollisionBound.Bottom() >= otherBound.Top()) {

				// There is a collision
				isCollided = true;

				Game::SetRenderDrawColor(Color::GREEN);
				SDL_RenderDrawLineF(Game::gRenderer, 0.0f, contactPoint.y, 2000.0f, contactPoint.y);
				SDL_RenderDrawLineF(Game::gRenderer, contactPoint.x, 0.0f, contactPoint.x, 2000.0f);

				distance = (contactPoint - start).Magnitude();

				// Check if this collision comes first
				if (distance < distanceToCollision) {

					distanceToCollision = distance;
					if (hitInfo) {

						hitInfo->otherCollider = otherCollier;
						finalCollider = otherCollier;
						hitInfo->contactPoint = contactPoint;

					}

				}

			}

		}

		// ---------------------------------------
		// Check collision on top side (min y)
		// ---------------------------------------
		// If the movement vector is horizontal and the center is
		// on the same line as minY, no collision is possible
		if (slope == 0 && minY== thisBound.center.y)
			continue;

		// The intersection of minY and movement line is the center
		// of the original collider when there is a collision
		// Calculate collision y
		contactPoint.y = minY;

		// Validate collision (Broad)
		collisionTime = (start - contactPoint).y / (start - end).y;
		if (collisionTime >= 0.0f && collisionTime <= 1.0f && movementVector.y >0.0f) {

			// Calculate collision x
			contactPoint.x = (minY - thisBound.center.y) / slope + thisBound.center.x;

			// Construct the bound for this collision
			Bound onCollisionBound;
			onCollisionBound.center = contactPoint;
			onCollisionBound.extents = thisBound.extents;

			// Validate collision (Final)
			if (onCollisionBound.Left()<=otherBound.Right()&&onCollisionBound.Right() >=otherBound.Left()) {

				// There is a collision
				isCollided = true;

				Game::SetRenderDrawColor(Color::GREEN);
				SDL_RenderDrawLineF(Game::gRenderer, 0.0f, contactPoint.y, 2000.0f, contactPoint.y);
				SDL_RenderDrawLineF(Game::gRenderer, contactPoint.x, 0.0f, contactPoint.x, 2000.0f);

				distance = (contactPoint - start).Magnitude();

				// Check if this collision comes first
				if (distance < distanceToCollision) {

					distanceToCollision = distance;
					if (hitInfo) {

						hitInfo->otherCollider = otherCollier;
						finalCollider = otherCollier;
						hitInfo->contactPoint = contactPoint;

					}

				}

			}

		}

		// ---------------------------------------
		// Check collision on bottom side (max y)
		// ---------------------------------------
		// If the movement vector is horizontal and the center is
		// on the same line as maxY, no collision is possible
		if (slope == 0 && maxY == thisBound.center.y)
			continue;

		// The intersection of maxY and movement line is the center
		// of the original collider when there is a collision
		// Calculate collision y
		contactPoint.y = maxY;

		// Validate collision (Broad)
		collisionTime = (start - contactPoint).y / (start - end).y;
		if (collisionTime >= 0.0f && collisionTime <= 1.0f && movementVector.y < 0.0f) {

			// Calculate collision x
			contactPoint.x = (maxY - thisBound.center.y) / slope + thisBound.center.x;

			// Construct the bound for this collision
			Bound onCollisionBound;
			onCollisionBound.center = contactPoint;
			onCollisionBound.extents = thisBound.extents;

			// Validate collision (Final)
			if (onCollisionBound.Left() <= otherBound.Right() && onCollisionBound.Right() >= otherBound.Left()) {

				// There is a collision
				isCollided = true;

				Game::SetRenderDrawColor(Color::GREEN);
				SDL_RenderDrawLineF(Game::gRenderer, 0.0f, contactPoint.y, 2000.0f, contactPoint.y);
				SDL_RenderDrawLineF(Game::gRenderer, contactPoint.x, 0.0f, contactPoint.x, 2000.0f);

				distance = (contactPoint - start).Magnitude();

				// Check if this collision comes first
				if (distance < distanceToCollision) {

					distanceToCollision = distance;
					if (hitInfo) {

						hitInfo->otherCollider = otherCollier;
						finalCollider = otherCollier;
						hitInfo->contactPoint = contactPoint;

					}

				}

			}

		}

	}

	// Call colliders upon collision
	if (finalCollider) {

		finalCollider->GetOwner()->OnCollisionEnter(collider);
		collider->GetOwner()->OnCollisionEnter(finalCollider);

	}

	return isCollided;

}

bool Physics::RayCast(Vector2 origin, Vector2 end, HitInfo* hitInfo) {

	// Output clipped line
	Vector2* newStart = new Vector2();
	Vector2* newEnd = new Vector2();

	// Flag
	bool collided = false;

	// The destination to the collision. Use
	// to determine which collision comes first
	float distanceToCollision = (end - origin).Magnitude();

	// The contact point
	Vector2 contactPoint;

	for (BoxCollider* collider : boxColliderSet) {

		// Get bound
		Bound bound = collider->GetBound();

		// Cast the ray to the rectangle
		if (ClipLineRectangle(origin, end, bound, newStart, newEnd)) {

			// Set flag to true
			collided = true;

			// Determine contact point
			if (*newStart != origin)
				contactPoint = *newStart;
			else
				contactPoint = *newEnd;

			// Calculate distance and determine if this collision is accepted
			float distance = (contactPoint - origin).Magnitude();
			if (distance >= distanceToCollision)
				continue;

			// Finalize collision
			if (hitInfo) {

				hitInfo->thisCollider = nullptr;
				hitInfo->otherCollider = collider;
				hitInfo->contactPoint = contactPoint;

			}

		}

	}

	// Clean up
	delete newStart;
	newStart = nullptr;
	delete newEnd;
	newEnd = nullptr;

	return collided;

}

bool Physics::ClipLineRectangle(Vector2 start, Vector2 end, Bound bound, Vector2* newStart, Vector2* newEnd) {

	// Define parameters
	float minX = bound.Left();
	float minY = bound.Top();
	float maxX = bound.Right();
	float maxY = bound.Bottom();
	float t0 = 0.0f, t1 = 1.0f;
	float dx = (end - start).x;
	float dy = (end - start).y;
	float p[] = { -dx, dx, -dy, dy };
	float q[] = { start.x - minX, maxX - start.x, start.y - minY, maxY - start.y };

	for (int i = 0; i < 4; i++) {

		// Parallel and outside
		if (p[i] == 0 && q[i] < 0.0f)
			return false;

		float t = q[i] / p[i];
		if (p[i] < 0.0f)
			t0 = max(t0, t);
		else if (p[i] > 0.0f)
			t1 = min(t1, t);

		// Fully outside
		if (t0 > t1)
			return false;

	}

	// Clip line
	if (newStart)
		*newStart = start + (end - start) * t0;

	if (newEnd)
		*newEnd = start + (end - start) * t1;

	return t0 != 0.0f || t1 != 1.0f;

}

void Physics::CheckForCollision(GameObject* gameObject, Vector2& movementVector) {
	// AABB PRINCIPLE

	if (movementVector == Vector2::zero)
		return;

	// Get component
	Transform* transform = gameObject->GetComponent<Transform>();
	BoxCollider* collider = gameObject->GetComponent<BoxCollider>();

	if (!collider)
		return;

	// Get the first collider's bound
	Bound startBound = collider->GetBound();
	Bound destinationBound = startBound;
	destinationBound.center += movementVector;

	// Get movement magnitude. This value will be used to
	// compare whether a collision should happen before another
	float magnitude = movementVector.Magnitude();

	// Origin and destination based on actual transform position
	Vector2 origin = transform->position;
	Vector2 destination = origin + movementVector;

	// The offset from the bound's center to the actual transform position
	Vector2 offset = origin - startBound.center;

	// Iterate through colliders
	for (BoxCollider* otherCollider : boxColliderSet) {

		// Skip if the same
		if (collider == otherCollider)
			continue;

		if (!otherCollider)
			throw new exception("Box collider set handled wrongly. Accessed NULL collider");

		// Get the other bound
		Bound otherBound = otherCollider->GetBound();

		// Pre-check (followed AABB rule)
		if (destinationBound.Left() > otherBound.Right() ||
			destinationBound.Right() < otherBound.Left() ||
			destinationBound.Top() > otherBound.Bottom() ||
			destinationBound.Bottom() < otherBound.Top())
			continue;

		// ----------------------------
		// Check for collision
		// ----------------------------
		cout << "Checking for collision...\n";
		// Use for determining which collision comes first
		float finalCollisionTime = FLT_MAX;
		float tempCollisionTime;		// Use for calculation
		// Whether a collision happened
		bool isCollided = false;
		// The point at which the collision happens. Use to pre-determine contact
		// point for further calculation
		Vector2 collisionPoint = Vector2::zero;
		// Final reset
		Vector2 finalContactPoint = Vector2::zero;

		// ----------------------------------------------------------
		// This collider's TOP side hit the other's BOTTOM side
		// ----------------------------------------------------------
		// Determine collision point (revert to the actual transform of this collider)
		collisionPoint.y = (otherBound.center + otherBound.extents + startBound.extents).y;	// Center
		collisionPoint.y += offset.y;		// To actual transform

		// Calculate collision time
		tempCollisionTime = (origin - collisionPoint).y / (origin - destination).y;

		// Validate collision time
		if (tempCollisionTime >= 0.0f && tempCollisionTime <= 1.0f && tempCollisionTime < finalCollisionTime) {

			// Complete contact point calculation
			collisionPoint = origin * (1.0f - tempCollisionTime) + destination * tempCollisionTime;

			// Check if it actually collided
			if (collisionPoint.x <= otherBound.Right() || collisionPoint.x + startBound.extents.x * 2.0f >= otherBound.Left()) {

				// A collision has happened
				isCollided = true;

				// Update contact point
				finalContactPoint = collisionPoint;

			}

		}

		// Finalize movement
		if (isCollided) {

			movementVector = finalContactPoint - origin;
			movementVector *= MOVEMENT_PERCENTAGE;

		}

	}

}