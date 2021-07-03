#include "line.h"

#include <utility>
#include <cstdlib>

// Bresenham's algorithm
void draw_line(Lattice2 p0, Lattice2 p1, Image & image, RGBA color) 
{
    int x0 = p0.x;
    int y0 = p0.y;
    int x1 = p1.x;
    int y1 = p1.y;

    bool steep = false; 
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 

    if (x1 < x0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0; 
    int dy = y1 - y0; 

    int dx2 = 2 * dx;
    int derror2 = 2 * std::abs(dy); 
    int error2 = 0; 

    int y = y0; 
    int y_increment = (y0 < y1) ? 1 : -1;

    if (steep) {
        for (int x = x0; x <= x1; x++) { 
            image({y, x}) = color; 
            error2 += derror2; 
            if (dx < error2) { 
                y += y_increment; 
                error2 -= dx2; 
            } 
        } 
    } else {
        for (int x = x0; x <= x1; x++) { 
            image({x, y}) = color; 
            error2 += derror2; 
            if (dx < error2) { 
                y += y_increment; 
                error2 -= dx2; 
            }
        }
    }
}