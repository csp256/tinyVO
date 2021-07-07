#include "Scene.h"

#include <lib/json.h>

#include <unordered_map>

using SceneLibrary = std::unordered_map<std::string, std::unique_ptr<Scene const>>;

SceneLibrary const& scene_library_impl(SceneLibrary * init = nullptr)
{
       static SceneLibrary library = std::move( *init );
       return library;
}

Scene const * scene_library(std::string const& name)
{
       auto const& library = scene_library_impl(); 
       auto it = library.find(name);
       if (it == library.end()) {
              throw std::runtime_error("Could not find scene in the library");
       }
       return it->second.get();
}

void initialize_scene_library(JSON const& scene_config)
{
       SceneLibrary scenes;
       for (auto const& j : scene_config.at("scenes")) {
              auto const& name = j.at("name").get<std::string>();
              auto unique_ptr = std::make_unique<Scene const>(j.at("scene"));
              scenes.emplace(name, std::move(unique_ptr));
       }
       scene_library_impl( &scenes );
}
