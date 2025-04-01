/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <set>
#include <unordered_set>

#include <GameComponent.h>

class RenderManager {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::set<GameObject*, decltype(&GameObject::CompareByLayer)> renderObjectSet;
	std::unordered_set<Layer> noZoomLayerList;		// Layers that are not affected by zoom in (usually UI)

	static RenderManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	RenderManager();
	~RenderManager();
	void RemoveRenderObject(GameObject* gameObject);
	void RenderAll();
	void UpdateRenderObject(GameObject* gameObject);
	bool AffectByZoom(Layer layer);

	static RenderManager* Instance();

};