#include "View.h"
#include "../types.h"
#include "../Utility.h"
#include <lib/json.h>

View::View(JSON const& j)
	: _position{get_point3(j.at("position"))}
	, _target{get_point3(j.at("target"))}
	, _up{get_point3(j.at("up"))}
{}