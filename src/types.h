#pragma once
#include <lib/linalg.h>

using Float = double;

using RGBA = linalg::vec<uint8_t, 4>;

using Point2 = linalg::vec<Float, 2>;
using Point3 = linalg::vec<Float, 3>;
using Point4 = linalg::vec<Float, 4>;

using Lattice2 = linalg::vec<int, 2>;
using Lattice3 = linalg::vec<int, 3>;

using Matrix4 = linalg::mat<Float, 4, 4>;
// using Matrix3 = linalg::mat<double, 3, 3>;

// Matrix4 operator*(Matrix4 const& a, Matrix4 const& b) { return mul(a,b); }
// Matrix4 operator*(Float const c, Matrix4 const& m) { return mul(Matrix4{c}, m); }