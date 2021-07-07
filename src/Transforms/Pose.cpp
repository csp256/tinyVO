#include "Pose.h"
#include "../Utility.h"
#include <lib/json.h>

Pose::Pose(JSON const& j)
	: position{ get_point3(j["position"]) }
	, rotation{ get_point3(j["rotation"]) }
	, scale{ get_point3(j["scale"]) }
{}