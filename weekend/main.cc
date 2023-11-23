#include <iostream>
#include "includes/color.h"
#include "includes/ray.h"
#include "includes/vec3.h"

// lerp (linear interpolation) between white and blue
// when a = 0, white and when a = 1, blue
// in between, blend
color ray_color(const ray& r) {
    vec3 unit_dir = unit_vector(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // defaults
    auto aspect_ratio = 16.0 / 9.0;
    int img_w = 400;

    // compute img height from defaults
    // important formula:
    // width / height = aspect ratio
    // e.g: 16/9 = 1.7778
    int img_h = static_cast<int>(img_w / aspect_ratio);
    img_h = (img_h < 1) ? 1 : img_h;

    // camera stuff
    auto focal_len = 1.0;
    auto viewport_h = 2.0;

    // compute viewport width from default height
    // important formula:
    // width / height = aspect ratio
    auto viewport_w = viewport_h * (static_cast<double>(img_w) / img_h);
    auto camera_center = point3(0, 0, 0);

    // calculate the vectors across the horizontal and down the vertical
    // viewport edges
    auto viewport_u = vec3(viewport_w, 0, 0);
    auto viewport_v = vec3(0, -viewport_h, 0);

    // calculate the horizontal and vertical delta vectors from pixel to pixel
    // For each pixel in the image, you would move a certain amount horizontally 
    // and vertically across the viewport. pixel_delta_u is the amount you move 
    // horizontally for each pixel, and pixel_delta_v is the amount you move 
    // vertically. These values are used to calculate the exact position on the 
    // viewport that the ray for each pixel should pass through.
    auto pixel_delta_u = viewport_u / img_w;
    auto pixel_delta_v = viewport_v / img_h;

    // calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_len)
        - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // rendering
    std::cout << "P3\n" << img_w << " " << img_h << "\n255\n";
    for (int j = 0; j < img_h; j++) {
        std::clog << "\rscanlines remaining -- " << ' ' << std::flush;
        for (int i = 0; i < img_w; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_dir = pixel_center - camera_center;
            ray r(camera_center, ray_dir);

            color pixel_col = ray_color(r);
            write_color(std::cout, pixel_col);
        }
    }

    std::clog << "\rdone.                 \n";
}