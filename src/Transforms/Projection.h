#pragma once 

#include "../types.h"
#include "../Utility.h"

using ForwardAxis = linalg::fwd_axis;
using ZRange = linalg::z_range;

struct Projection {
	Float 			_fovy;
	Float 			_aspect_ratio;
	Float 			_near;
	Float 			_far;
	ForwardAxis 	_forward_axis = ForwardAxis::neg_z;
	ZRange			_z_range = ZRange::zero_to_one;

	Projection(JSON const& j);

	inline Matrix4 matrix() 
	{
		return linalg::perspective_matrix(
			_fovy, 
			_aspect_ratio, 
			_near, 
			_far,
			_forward_axis, 
			_z_range);
	}
};