#pragma once 

#include "OBJ.h"
#include "Transforms/Pose.h"

#include "Shaders/VertexShader.h"

#include <lib/json_fwd.h>

//

class Actor {
public:
	Shared<OBJ> _obj;
	Pose _pose;

	Actor() = default;
	Actor(JSON const& j);

	inline Point3 const& position() const { return _pose.position; }

private:
	using IndexVector = std::vector<tinyobj::index_t>;

	inline Point4 extract_triangle_vertex(
				IndexVector const& indices, 
				size_t const i) const
	{
		auto const& vert = _obj->GetAttrib().vertices;
		return Point4{
            vert[ 3 * indices[i].vertex_index + 0 ],
            vert[ 3 * indices[i].vertex_index + 1 ],
            vert[ 3 * indices[i].vertex_index + 2 ],
			1.0
		};
	}

private:
	inline std::array<Point4, 3> 
	extract_triangle(
				std::vector<tinyobj::index_t> const& indices, 
				size_t const i) const
	{
	// 	return {
	// 		extract_triangle_vertex(i + 0),
	// 		extract_triangle_vertex(i + 1),
	// 		extract_triangle_vertex(i + 2)};
	// }

		auto const& vert = _obj->GetAttrib().vertices;
		
        auto const v0 = Point4{
            vert[ 3 * indices[i+0].vertex_index + 0 ],
            vert[ 3 * indices[i+0].vertex_index + 1 ],
            vert[ 3 * indices[i+0].vertex_index + 2 ],
            1.0};
        auto const v1 = Point4{
            vert[ 3 * indices[i+1].vertex_index + 0 ],
            vert[ 3 * indices[i+1].vertex_index + 1 ],
            vert[ 3 * indices[i+1].vertex_index + 2 ],
            1.0};
        auto const v2 = Point4{
            vert[ 3 * indices[i+2].vertex_index + 0 ],
            vert[ 3 * indices[i+2].vertex_index + 1 ],
            vert[ 3 * indices[i+2].vertex_index + 2 ],
            1.0};

        return { v0, v1, v2 };
	}

	inline std::array<Vertex, 3>
	extract_triangle(
				std::vector<Vertex> const& vs_out,
				std::vector<tinyobj::index_t> const& indices, 
				size_t const i) const
	{
		return {
			vs_out[indices[i+0].vertex_index],
			vs_out[indices[i+1].vertex_index],
			vs_out[indices[i+2].vertex_index]};
	}

public:
	template <typename Functor>
	inline void for_each_triangle(std::vector<Vertex> const& vs_out, Functor && functor) const
	{
	    for (auto const& shape : _obj->GetShapes()) {
	        IndexVector const& indices = shape.mesh.indices;
	        for (size_t i = 0; i < indices.size(); i += 3) {
	        	// auto const tri = extract_triangle(indices, i);
	         //    functor(tri);
	        	auto const tri = extract_triangle(vs_out, indices, i);
	        	functor(tri);
	        }
	    }
	}

public:
	inline void verify_triangles() const
	{
	    for (auto const& shape : _obj->GetShapes()) {
	        for (auto& v : shape.mesh.num_face_vertices) {
	            if (v != 3) {
	                throw std::runtime_error("Can only draw shapes that are exclusively triangles");
	            }
	        }
	    }
	}
};
