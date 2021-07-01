#pragma once

#include "../types.h"

struct View {
	Point3 _position;
	Point3 _direction;
	Point3 _up = Point3{0, 1, 0};

	inline Matrix4 matrix() 
	{
		return linalg::lookat_matrix(_position, _position + _direction, _up);
	}

	inline void set_target(Point3 const& target)
	{
		_direction = target - _position;
	}
};