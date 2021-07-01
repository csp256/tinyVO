#pragma once
#include "types.h"

#include "Camera/View.h"
#include "Camera/Projection.h"

#include <optional>

struct Camera {
	View _view;
	Projection _projection;

	Matrix4 view_projection_matrix()
	{
		return mul(_projection.matrix(), _view.matrix());
	}

	static Point3 project(Matrix4 const& model_view_projection, Point3 const& p3)
	{
		auto p4 = Point4{p3, 1.0};
		auto q4 = mul(model_view_projection, p4);
		auto w_inv = 1.0 / q4.w;
		return {
			q4.x * w_inv, 
			q4.y * w_inv, 
			q4.z * w_inv};
	}
};