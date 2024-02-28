//
// Created by rrr on 2/10/24.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "vec3.h"

class ray{
public:
    ray()= default;

    ray(const point3& origin, const vec3& direction): org(origin), dir(direction) {}

    //getters of origin and destination
    point3 origin() const {return org;}
    vec3 direction() const {return dir;}

    point3 at(double t) const{
        return org + t*dir;
    }

private:
    point3 org;
    vec3 dir;
};
#endif //RAY_TRACING_RAY_H
