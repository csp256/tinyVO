#pragma once
#include "../types.h"
#include <lib/json_fwd.h>
#include <cmath>

// aka "Model"

inline Matrix4 skew_symmetric_matrix4(Point3 const p)
{
	// linalg is column-major ordering, so matrix looks transposed
	return Matrix4{
		{ 0.0,  p.z, -p.y,  0.0},  // column 0
		{-p.z,  0.0,  p.x,  0.0},  // column 1
		{ p.y, -p.x,  0.0,  0.0},  // column 2
		{ 0.0,  0.0,  0.0,  1.0}}; // column 3
}

inline Matrix4 rotation_matrix(Point3 const p)
{
	// https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula#Matrix_notation
	Float const theta = length(p);
	static constexpr Float epsilon = 1e-5;
	if (theta <= epsilon) {
		return linalg::identity;
	}
	Point3 const p_hat = p / theta;

	Matrix4 const I = linalg::identity;
	Matrix4 const K = skew_symmetric_matrix4(p_hat);
	Matrix4 const K2 = mul(K, K);

	return I + cmul((Float)std::sin(theta), K) + cmul((Float)(1.0 - std::cos(theta)), K2);
}

inline Matrix4 scale_matrix(Point3 const p)
{
	Matrix4 out = linalg::identity;
	out[0][0] = p.x;
	out[1][1] = p.y;
	out[2][2] = p.z;
	return out;
	// return Matrix4{
	// 	{p.x, 0.0, 0.0, 0.0},
	// 	{0.0, p.y, 0.0, 0.0},
	// 	{0.0, 0.0, p.z, 0.0},
	// 	{0.0, 0.0, 0.0, 1.0}};
}

inline Matrix4 translation_matrix(Point3 const p)
{
	Matrix4 out = linalg::identity;
	out[3][0] = p.x;
	out[3][1] = p.y;
	out[3][2] = p.z;
	return out;
	// return transpose(Matrix4{
	// 	{1.0, 0.0, 0.0, p.x},
	// 	{0.0, 1.0, 0.0, p.y},
	// 	{0.0, 0.0, 1.0, p.z},
	// 	{0.0, 0.0, 0.0, 1.0}});
}



struct Pose {
	Point3 position = Point3{ 0.0 };
	Point3 rotation = Point3{ 0.0 }; // stored as rodriques vector
	Point3 scale = Point3{ 1.0 };

	Pose() = default;
	Pose(JSON const& j);

	inline Matrix4 matrix() const
	{
		return mul(translation_matrix(position),
			mul(rotation_matrix(rotation),
			scale_matrix(scale)));
	}
};

