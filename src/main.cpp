import helloworld;

#include "Image.h"
#include "line.h"
#include "triangle.h"

#include "Timer.h"
#include "NQueens.h"

#include <lib/linalg.h>

#include <iostream>
#include <iomanip>
#include <cstdlib>

int main(int argc, char *argv[])
try
{
    (void) argc;
    (void) argv;

    auto g = Image(100, 100);
    g({3,3}) = {255,0,255,255};
    g.write_png("one.png");

    auto h = Image("one.png");
    draw_wire_triangle({2, 90}, {30, 6}, {60,40}, h, {0,255,255,255});
    h.write_png("two.png");

    auto const hardcoded = NQueens::hardcoded();

    for (int n = 0; n <= 12; n++) {
        Timer timer;
        auto solution_count = NQueens::count_solutions(n);
        auto seconds = timer.seconds();

        std::cout << std::to_string(n) 
            << " : " << std::to_string(solution_count) 
            << " : " << seconds << std::endl;

        if (solution_count != hardcoded[n]) {
            std::cout << "\t\tFAILURE" << std::endl;
        }
    }

    return 0;
}
catch (std::exception const& ex)
{
    std::cout << "\nEXCEPTION\n\t" << ex.what() << std::endl;
    return -1;
}