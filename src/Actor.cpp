#include "Actor.h"

#include <lib/json.h>

Actor::Actor(JSON const& j) 
	: _obj{ model_library(j.at("model").get<std::string>()) }
	, _pose{ j.at("pose") }
{}