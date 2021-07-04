#pragma once

#include "types.h"
#include "BoundingBox.h"

#include "lib/minmax.h"
#include "lib/linalg.h"

#include <iostream>

namespace {

	using vec2 = linalg::vec<double, 2>;

	/**
	 * Used for testing (many) points if they are inside a single planar triangle. 
	 */
	class TriangleTester {
		class LineTester {
			vec2 const shift;
			vec2 const normal;

		public:
			LineTester(vec2 const line0, vec2 const line1, vec2 const p)
				: shift{ line0 }
				, normal{ vec2{p - line0}.rejection_from(line1 - line0) }
			{}

			inline bool operator()(vec2 const p) const
			{
				return 0 <= dot(normal, p - shift);
			}
		};

		LineTester const test[3];

	public:
		TriangleTester(std::array<vec2,3> const p)
			: test{
				{ p[0], p[1], p[2] },
				{ p[1], p[2], p[0] },
				{ p[2], p[0], p[1] }
			}
		{}

		inline bool operator()(vec2 const p) const
		{
			return test[0](p) && test[1](p) && test[2](p);
		}
	};

} // anonymous namespace

inline void draw_wire_triangle(std::array<Lattice2, 3> tri, Image & image, RGBA color)
{
	draw_line(tri[0], tri[1], image, color);
	draw_line(tri[1], tri[2], image, color);
	draw_line(tri[0], tri[2], image, color);
}

inline void draw_filled_triangle(std::array<Lattice2, 3> tri, Image & image, RGBA color)
{
	auto const point_within_triangle = TriangleTester({ 
		vec2{tri[0].x, tri[0].y}, 
		vec2{tri[1].x, tri[1].y}, 
		vec2{tri[2].x, tri[2].y} });

	auto bounding_box = BoundingBox<Lattice2>(tri[0], tri[1]);
	bounding_box.expand_to_contain(tri[2]);
	bounding_box.clip_within(image);

	bounding_box.for_each([&](Lattice2 const& point) -> void
	{
		if (point_within_triangle({point.x, point.y})) {
			image(point) = color;
		}
	});
}

// 

inline Point3 face_normal(std::array<Point4, 3> const& v)
{
	auto const p0 = v[0].xyz();
	auto const q1 = v[1].xyz() - p0;
	auto const q2 = v[2].xyz() - p0;
	return cross(q1, q2);
}

inline Point3 unit_face_normal(std::array<Point4, 3> const& v)
{
	return normalize(face_normal(v));
}

inline bool is_backfacing(std::array<Point4, 3> const& v) 
{
	return face_normal(v).z < 0;
}