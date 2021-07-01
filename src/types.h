#pragma once
#include <lib/linalg.h>

using RGBA = linalg::vec<uint8_t, 4>;

using Point2 = linalg::vec<double, 2>;
using Point3 = linalg::vec<double, 3>;
using Point4 = linalg::vec<double, 4>;

using Lattice2 = linalg::vec<int, 2>;
using Lattice3 = linalg::vec<int, 3>;

using Matrix4 = linalg::mat<double, 4, 4>;