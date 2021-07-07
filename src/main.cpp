#include "Texture.h"
#include "line.h"
#include "triangle.h"

#include "OBJ.h"
#include "Actor.h"

#include "Transforms/View.h"
#include "Transforms/Viewport.h"

#include "Scene.h"
#include "Render.h"

#include "Timer.h"

#include "Config.h"

#include <lib/linalg.h>
#include <lib/tiny_obj_loader.h>
#include <lib/ThreadPool.h>

#include <iostream>
#include <iomanip>
#include <cstdlib>

int main(int argc, char *argv[])
try
{
    read_config(argc, argv);

    // auto image = Texture(800, 640);

    // auto tri = std::array<Lattice2, 3>{
    //     Lattice2{2, 90}, 
    //     Lattice2{30, 6}, 
    //     Lattice2{60,40}};

    // auto const red = RGBA{1., 0, 0, 1.};
    // auto const green = RGBA{0, 1., 0, 1.};
    // auto const blue = RGBA{0, 0, 1., 1.};
    // auto const cyan = RGBA{0, 1., 1., 0.2};

    // (void) red;
    // (void) green; 
    // (void) blue;
    // (void) cyan;


    // draw_filled_triangle(tri, image, red);
    // draw_wire_triangle(tri, image, cyan);

    

    // auto const * scene = scene_library("face");
    // auto const& actor = scene->_actors[0];

    // // thing._pose.position = Point3{0.0, 0.0, 0.0};
    // // thing._pose.scale = Point3{ 1.0 };
    // // thing._model.rotation = Point3{-0.0, 2.6, 0.0};

    // View view;
    // view._position = Point3{100,200,-400};
    // view._target = actor.position();

    // Viewport viewport;

    // Matrix4 const world_from_model = actor._pose.matrix(); // world_from_model
    // Matrix4 const camera_from_world = view.matrix(); // camera_from_world
    // Matrix4 const NDC_from_camera = linalg::identity; // NDC_from_camera
    // Matrix4 const viewport_from_NDC = viewport.matrix(image);

    // Matrix4 const viewport_from_model = 
    //     linalg::mul(viewport_from_NDC, 
    //         linalg::mul(NDC_from_camera, 
    //             linalg::mul(camera_from_world, 
    //                 world_from_model)));

    // // std::cout << viewport_from_model << "\n";

    // actor.for_each_triangle([&](std::array<Point4, 3> const p) -> void
    //     {
    //         auto const q = std::array<Point4, 3>{
    //             linalg::mul(viewport_from_model, p[0]),
    //             linalg::mul(viewport_from_model, p[1]),
    //             linalg::mul(viewport_from_model, p[2])};

    //         // std::cout << "\t***\n" << p[0] << "\n" << q[0] << "\n";

    //         auto const normal = unit_face_normal(q);

    //         // backface culling
    //         if (normal.z < 0.0) {
    //             return;
    //         }

    //         // std::cout << normal << "\n";

    //         auto const s = 0 + (int)(255 * normal.z);
    //         auto const shading = RGBA{ s, s, s, 255};

    //         draw_filled_triangle(q, image, shading);
    //         // draw_wire_triangle(q, image, green);
    //     });

    // image.write_hdr("image.hdr");

    return 0;
}
catch (std::exception const& ex)
{
    std::cout << "\nEXCEPTION\n\t" << ex.what() << std::endl;
    return -1;
}