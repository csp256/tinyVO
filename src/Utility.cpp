#include "Utility.h"
#include <lib/json.h>

Point3 get_point3(JSON const& j)
{
	auto k = j.get<std::vector<JSON>>();
	return { 
		k[0].get<Float>(), 
		k[1].get<Float>(), 
		k[2].get<Float>()};
}

Point4 get_point4(JSON const& j)
{
	auto const k = j.get<std::vector<JSON>>();
	return { 
		k[0].get<Float>(), 
		k[1].get<Float>(), 
		k[2].get<Float>(),
		k[3].get<Float>()};
}