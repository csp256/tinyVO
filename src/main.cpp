#include "Image.h"
#include "line.h"
#include "triangle.h"

#include "OBJ.h"
#include "Instance.h"

#include "Timer.h"

#include <lib/linalg.h>
#include <lib/tiny_obj_loader.h>

#include <iostream>
#include <iomanip>
#include <cstdlib>

int main(int argc, char *argv[])
try
{
    (void) argc;
    (void) argv;

    auto image = Image(800, 640);

    auto tri = std::array<Lattice2, 3>{
        Lattice2{2, 90}, 
        Lattice2{30, 6}, 
        Lattice2{60,40}};

    auto const red = RGBA{255,0,0,255};
    auto const green = RGBA{0,255,0,255};
    auto const blue = RGBA{0,0,255,255};
    auto const cyan = RGBA{0,255,255,255};

    (void) red;
    (void) green;
    (void) blue;
    (void) cyan;


    draw_filled_triangle(tri, image, red);
    draw_wire_triangle(tri, image, cyan);

    // auto obj = load_OBJ("models/catmark_torus_creases0.obj");
    auto obj = load_OBJ("models/head/african_head.obj");

    auto thing = Instance{};
    thing._obj = obj;
    thing._model.rotation = Point3{-0.4, 0.2, 0.0};

    auto offset = 300.0;
    auto scale = 250.0;

    thing.for_each_triangle({}, [&](std::array<Point4, 3> const p) -> void
        {
            auto const q = std::array<Lattice2,3>{
                Lattice2{(int)(scale * p[0].x + offset), (int)(scale * p[0].y + offset)},
                Lattice2{(int)(scale * p[1].x + offset), (int)(scale * p[1].y + offset)},
                Lattice2{(int)(scale * p[2].x + offset), (int)(scale * p[2].y + offset)}};

            auto const normal = unit_face_normal(p);
            auto const s = 100 + (int)(100 * normal.z);
            auto const shading = RGBA{ s, s, s, 255};

            draw_filled_triangle(q, image, shading);
            draw_wire_triangle(q, image, green);
        });

    image.write_png("image.png");

    return 0;
}
catch (std::exception const& ex)
{
    std::cout << "\nEXCEPTION\n\t" << ex.what() << std::endl;
    return -1;
}