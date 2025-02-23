#include <RenderManager.h>
#include <GameComponent.h>

std::set<GameObject*, decltype(&GameObject::CompareByLayer)> RenderManager::renderObjectSet = std::set<GameObject*, decltype(&GameObject::CompareByLayer)>(&GameObject::CompareByLayer);

void RenderManager::UpdateRenderObject(GameObject* gameObject) {

	RemoveRenderObject(gameObject);

	renderObjectSet.insert(gameObject);

}

void RenderManager::RenderAll() {

	std::erase_if(renderObjectSet, [](GameObject* obj) { return obj == nullptr; });
	cout << "Start rendering..." << endl;
	for (auto obj : renderObjectSet) {

		cout << "Rendering " << obj->name << " (Layer: " << (int)obj->GetLayer() << " | ID: " << obj->ID() << ")" << endl;

		if (obj->IsActive())
			obj->Render();

	}
	cout << "Rendering finished." << endl;

}

void RenderManager::RemoveRenderObject(GameObject* gameObject) {

	auto it = renderObjectSet.begin();
	while (it != renderObjectSet.end()) {

		if (*it == gameObject) {

			renderObjectSet.erase(it);
			return;

		}

		it++;

	}

}