#pragma once

#include <set>
#include <GameComponent.h>

class RenderManager {

private:

	static std::set<GameObject*, decltype(&GameObject::CompareByLayer)> renderObjectSet;

public:

	static void UpdateRenderObject(GameObject* gameObject);
	static void RemoveRenderObject(GameObject* gameObject);

	static void RenderAll();

};