#pragma once

#include <set>
#include <unordered_set>
#include <GameComponent.h>

class RenderManager {

private:

	static std::set<GameObject*, decltype(&GameObject::CompareByLayer)> renderObjectSet;

	static std::unordered_set<Layer> noZoomLayerList;

public:

	static void UpdateRenderObject(GameObject* gameObject);
	static void RemoveRenderObject(GameObject* gameObject);

	static void RenderAll();

	static bool AffectByZoom(Layer layer);

};