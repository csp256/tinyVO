#pragma once
#include "../types.h"
#include "../OBJ.h"

#include <vector>

struct Vertex {
	Point4 const position_in_world;

	Vertex(Point4 const& p)
		: position_in_world{p}
		{}
};

struct Atlas;

std::vector<Vertex> vertex_shader(Atlas const& atlas, Shared<OBJ> obj);