#include "VertexShader.h"
#include "../Transforms/Atlas.h"

std::vector<Vertex>
vertex_shader(Atlas const& atlas, Shared<OBJ> obj)
{
	auto const& raw_vertices = obj->GetAttrib().vertices;

	std::vector<Vertex> out;
	out.reserve(raw_vertices.size() / 3);

	for (size_t i = 0; i < raw_vertices.size(); i += 3) {
		auto const v = Point4{
			raw_vertices[i+0],
			raw_vertices[i+1],
			raw_vertices[i+2],
			1.0};
		out.emplace_back( linalg::mul(atlas.camera_from_model, v) );
	}

	return out;
}