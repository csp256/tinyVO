#pragma once

#include "../types.h"

#include <lib/json_fwd.h>

struct View {
	Point3 _position = Point3{ 0, 0, 0 } ;
	Point3 _target = Point3{ 0, 0, 1 };
	Point3 _up = Point3{ 0, 1, 0 };

	View() = default;
	View(JSON const& j);

	inline Matrix4 matrix() const
	{
		return linalg::lookat_matrix(_position, _target, _up);
	}
};