#include "Scene.h"

#include <lib/json.h>

Scene::Scene(JSON const& j)
{
	auto actor_json = j["actors"].get<std::vector<JSON>>();
	_actors.reserve(actor_json.size());
	for (auto& k : actor_json) {
		_actors.emplace_back(k);
	}
}

//

