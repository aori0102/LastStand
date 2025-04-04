/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <RenderManager.h>

#include <GameComponent.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

RenderManager* RenderManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

RenderManager::RenderManager() {

	if (instance)
		throw std::exception("RenderManager can only have 1 instance!");

	renderObjectSet = std::set<GameObject*, decltype(&GameObject::CompareByLayer)>(&GameObject::CompareByLayer);
	noZoomLayerList = {
		Layer::Menu,
		Layer::GUI
	};

	instance = this;

}

RenderManager::~RenderManager() {

	renderObjectSet.clear();
	noZoomLayerList.clear();

	instance = nullptr;

}

void RenderManager::RemoveRenderObject(GameObject* gameObject) {

	for (auto it = renderObjectSet.begin(); it != renderObjectSet.end(); it++) {

		if (*it == gameObject) {

			renderObjectSet.erase(it);
			return;

		}

	}

}

void RenderManager::RenderAll() {

	std::erase_if(renderObjectSet, [](GameObject* obj) { return obj == nullptr; });
	for (auto obj : renderObjectSet) {
		
		if (obj->IsActive())
			obj->Render();

	}

}

void RenderManager::UpdateRenderObject(GameObject* gameObject) {

	RemoveRenderObject(gameObject);

	renderObjectSet.insert(gameObject);

}

bool RenderManager::AffectByZoom(Layer layer) {

	return !noZoomLayerList.contains(layer);

}

RenderManager* RenderManager::Instance() { return instance; }