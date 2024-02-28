//
// Created by rrr on 2/10/24.
//

#ifndef RAY_TRACING_COLOR_H
#define RAY_TRACING_COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

inline double linear_to_gamma(double linear){
    return sqrt(linear);
}

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    // 255.999 is used to minimize the risk of rounding down error, 1.0*255 can result in 254.9999, and when casted as int it results in 254
//    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
//        << static_cast<int>(255.999 * pixel_color.y()) << ' '
//        << static_cast<int>(255.999 * pixel_color.z()) << '\n';

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0/ samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif //RAY_TRACING_COLOR_H
