#include "Projection.h"

#include <lib/json.h>

Projection::Projection(JSON const& j)
	: _fovy{ j.at("field_of_view_y").get<Float>() }
	, _aspect_ratio{ j.at("aspect_ratio").get<Float>() }
	, _near{ j.at("near_plane").get<Float>() }
	, _far{ j.at("far_plane").get<Float>() }
{}