#include "OBJ.h"
#include "Camera/Model.h"



//

class Instance {
public:
	Shared<OBJ> _obj;
	Model _model;

public:
	struct IterConfig {
		bool cull_backface = true;
		bool apply_model_transform = true;

		static constexpr uint32_t kCullBackface	= 1;
		static constexpr uint32_t kApplyModel 	= 1 << 1;

		inline uint32_t bitset() const {
			uint32_t out = 0;
			if (cull_backface) 			out |= kCullBackface;
			if (apply_model_transform) 	out |= kApplyModel;
			return out;
		}

		bool verify_triangles = true;
	};
	using Config = IterConfig;

private:
	inline std::array<Point4, 3> 
	extract_triangle(
				std::vector<tinyobj::index_t> const& indices, 
				size_t const i) const
	{
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

private:
	template <int kCullBackface, int kApplyModel, typename Functor>
	inline void for_each_triangle_impl(Functor && functor) const
	{
		auto const model_matrix = _model.matrix();

	    for (auto const& shape : _obj->GetShapes()) {
	        auto const& indices = shape.mesh.indices;
	        for (size_t i = 0; i < indices.size(); i += 3) {
	        	auto tri = extract_triangle(indices, i);

	        	if constexpr (kApplyModel) {
	        		for (auto& v : tri) {
	        			v = mul(model_matrix, v);
	        		}
	        	}

	            if constexpr (kCullBackface) {
	            	if (is_backfacing(tri)) {
	            		continue;
	            	}
	            }

	            functor(tri);
	        }
	    }
	}

public:
	template <typename Functor>
	inline void for_each_triangle(IterConfig const config, Functor && functor) const
	{
		if (config.verify_triangles) {
			verify_triangles();
		}

		switch (config.bitset()) {
			case 0 | 0:
				for_each_triangle_impl<0, 0, Functor>(std::forward<Functor&&>(functor));
				break;
			case IterConfig::kCullBackface | 0:
				for_each_triangle_impl<1, 0, Functor>(std::forward<Functor&&>(functor));
				break;
			case 0 | IterConfig::kApplyModel:
				for_each_triangle_impl<0, 1, Functor>(std::forward<Functor&&>(functor));
				break;
			case IterConfig::kCullBackface | IterConfig::kApplyModel:
				for_each_triangle_impl<1, 1, Functor>(std::forward<Functor&&>(functor));
				break;
			default:
				throw std::runtime_error("Should not be able to get here.");
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
