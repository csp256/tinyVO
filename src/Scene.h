#pragma once

#include "Actor.h"

#include <lib/json_fwd.h>

#include <string>
#include <vector>

class Scene {
public:
	std::vector<Actor> _actors;
	std::string _name;

public:
	Scene(JSON const& j);
};

Scene const * scene_library(std::string const& name);

void initialize_scene_library(JSON const& j);