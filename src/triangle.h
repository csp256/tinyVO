#include "types.h"

inline void draw_wire_triangle(Lattice2 p0, Lattice2 p1, Lattice2 p2, Image & image, RGBA color)
{
	draw_line(p0, p1, image, color);
	draw_line(p1, p2, image, color);
	draw_line(p0, p2, image, color);
}