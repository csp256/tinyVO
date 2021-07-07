#include "types.h"
#include "OBJ.h"
#include "Scene.h"
#include "Render.h"

#include <lib/json.h>

#include "Parallel.h"
#include <lib/ThreadPool.h>

#include <fstream>
#include <iostream>

JSON load_json(std::string const& path)
{
	JSON j;
	std::ifstream input(path);
	input >> j;
	return j;
}

void read_config(int const argc, char * argv[]) 
{
    std::string main_config_path = (argc == 1)
        ? "config/config.json"
        : argv[1];

	JSON config = load_json(main_config_path);
	thread_pool( config.at("worker_threads").get<size_t>() );

	// 

	auto load_json_from_name = [&config](std::string const& name)
		{
			return load_json(config[name].get<std::string>());
		};
	auto names = std::vector<std::string>{ "models", "scenes", "renders" };
	auto results = parallel<JSON>(load_json_from_name, names);

	// Models

	initialize_model_library( results[0].get() );

	// Scenes

	initialize_scene_library( results[1].get() );

	// Render

	perform_all_renders( results[2].get() );

}