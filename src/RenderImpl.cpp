#include "Render.h"
#include "triangle.h"

#include "Transforms/Atlas.h"

#include "Shaders/VertexShader.h"

#include <iostream>

void Render::draw()
{
    Viewport viewport;

    for (auto& actor : _scene->_actors) {

    	auto const atlas = Atlas{actor, _view, _projection, _image};

	    auto vs_out = vertex_shader(atlas, actor._obj);

	    actor.for_each_triangle(vs_out, 
	    	[&](std::array<Vertex, 3> const p) -> void
	        {
	        	auto const q = std::array<Point4, 3>{
	        		100 * p[0].position_in_world,
	        		100 * p[1].position_in_world,
	        		100 * p[2].position_in_world};

	            auto const normal = unit_face_normal(q);

	            // backface culling
	            if (normal.z < 0.0) { 
	                return;
	            }

	            auto const s = 0 + (int)(255 * normal.z);
	            auto const shading = RGBA{ s, s, s, 255};

	            draw_filled_triangle(q, _image, shading);
	        });
	}

    _image.write_hdr();
}