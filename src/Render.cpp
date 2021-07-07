#include "Render.h"
#include "triangle.h"

#include <lib/json.h>

Render::Render(JSON const& j)
	: _scene{ scene_library(j.at("scene")) }
	, _view{ j.at("view") }
	, _projection{ j.at("projection") }
	, _image{ j.at("image") }
{
	draw();
}

void perform_all_renders(JSON const& j)
{

	auto const& render_config = j.at("renders").get<std::vector<JSON>>();
	for (auto& j : render_config) {
		std::cout << "a" << std::endl;
		Render render{ j };
		std::cout << "b" << std::endl;
	}
}