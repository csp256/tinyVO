#include "OBJ.h"
#include "Camera/Model.h"

struct Instance {
	Shared<OBJ> _obj;
	Model _model;

	template <typename Functor>
	inline void for_each_triangle(Functor && functor) const
	{
		auto const model_matrix = _model.matrix();

	    auto const& vert = _obj->GetAttrib().vertices;

	    for (auto const& shape : _obj->GetShapes()) {
	        auto const& indices = shape.mesh.indices;
	        for (auto& v : shape.mesh.num_face_vertices) {
	            if (v != 3) {
	                throw std::runtime_error("Can only draw triangles");
	            }
	        }
	        for (size_t i = 0; i < indices.size(); i += 3) {
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

	            functor(std::array<Point4 const, 3>{ 
	            	mul(model_matrix, v0),
	            	mul(model_matrix, v1),
	            	mul(model_matrix, v2)});
	        }
	    }
	}

};