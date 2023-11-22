#include <iostream>
#include "color.h"

int main() {
    int img_width = 256;
    int img_height = 256;

    std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";

    for (int j = 0; j < img_height; j++) {
        std::clog << "\rscanlines remaining -- " << ' ' << std::flush;
        for (int i = 0; i < img_width; i++) {
            auto r = double(i) / (img_width - 1);
            auto g = double(j) / (img_height - 1);
            auto b = 0;
            auto pixel_col = color(r, g, b);
            write_color(std::cout, pixel_col);
        }
    }

    std::clog << "\rdone.                 \n";
}