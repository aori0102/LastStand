#include <RenderManager.h>
#include <GameComponent.h>

std::set<GameObject*, decltype(&GameObject::CompareByLayer)> RenderManager::renderObjectSet = std::set<GameObject*, decltype(&GameObject::CompareByLayer)>(&GameObject::CompareByLayer);
std::unordered_set<Layer> RenderManager::noZoomLayerList = {
	Layer::Menu,
	Layer::GUI
};


void RenderManager::UpdateRenderObject(GameObject* gameObject) {

	RemoveRenderObject(gameObject);

	renderObjectSet.insert(gameObject);

}

void RenderManager::RenderAll() {

	std::erase_if(renderObjectSet, [](GameObject* obj) { return obj == nullptr; });
	//std::cout << "----- Start rendering... -----" << std::endl;
	for (auto obj : renderObjectSet) {

		if (obj->IsActive()) {
			//std::cout << "Rendering " << obj->name << " (Layer: " << (int)obj->GetLayer() << " | ID: " << obj->ID() << ")" << std::endl;
			obj->Render();
		}

	}

}

void RenderManager::RemoveRenderObject(GameObject* gameObject) {

	if (renderObjectSet.contains(gameObject))
		renderObjectSet.erase(gameObject);

}

bool RenderManager::AffectByZoom(Layer layer) {

	return !noZoomLayerList.contains(layer);

}