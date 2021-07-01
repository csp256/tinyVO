#include "../types.h"

struct Projection {
	double _fovy;
	double _aspect_ratio;
	double _near;
	double _far;
	linalg::fwd_axis _forward_axis = linalg::fwd_axis::neg_z;
	linalg::z_range _z_range = linalg::z_range::neg_one_to_one;

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