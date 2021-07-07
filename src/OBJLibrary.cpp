#include "OBJ.h"

#include "Parallel.h"

#include <lib/json.h>

#include <unordered_map>

//

using ModelLibrary = std::unordered_map<std::string, Shared<OBJ>>;

Shared<OBJ> load_OBJ(std::string const& filename)
{
       auto obj = CreateShared<OBJ>();
       auto valid = obj->ParseFromFile(filename);
       if (not valid) {
              throw std::runtime_error("Failed to load OBJ");
       }
       return obj;
}

ModelLibrary const& model_library_impl(ModelLibrary * init = nullptr)
{
       static ModelLibrary library = std::move( *init );
       return library;
}

void initialize_model_library(JSON const& config)
{
       auto load_OBJ_from_json = [](JSON const& j) -> Shared<OBJ>
              {
                     auto path = j.find("path")->get<std::string>();
                     return load_OBJ(path);
              };
       auto config_vector = config["models"].get<std::vector<JSON>>();
       auto results = parallel(load_OBJ_from_json, config_vector);

       ModelLibrary models;
       for (size_t i = 0; i < results.size(); i++) {
              auto const name = config_vector[i]["name"].get<std::string>();
              models[ name ] = results[i].get();
       }

       model_library_impl( &models );
}

Shared<OBJ> model_library(std::string const& name)
{
       auto const& library = model_library_impl(); 
       auto it = library.find(name);
       if (it == library.end()) {
              throw std::runtime_error("Could not find model in the library");
       }
       // Shared<OBJ> out = it->second;
       return it->second;
}