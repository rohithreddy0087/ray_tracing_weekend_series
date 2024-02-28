//
// Created by rrr on 2/26/24.
//

#ifndef RAY_TRACING_CONSTANTS_H
#define RAY_TRACING_CONSTANTS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double(){
    return rand()/(RAND_MAX+1.0);
}

inline double random_double(double min, double max){
    return min + (max - min)*random_double();
}

#include "interval.h"
#include "ray.h"
#include "vec3.h"
#endif //RAY_TRACING_CONSTANTS_H
