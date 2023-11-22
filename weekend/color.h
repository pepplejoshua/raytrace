#pragma once

#include <iostream>
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, color pixel_col) {
    // write the translated [0,255] value of each color component
    out << static_cast<int>(255.999 * pixel_col.x()) << ' '
        << static_cast<int>(255.999 * pixel_col.y()) << ' '
        << static_cast<int>(255.999 * pixel_col.z()) << '\n';
}