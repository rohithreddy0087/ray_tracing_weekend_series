//
// Created by rrr on 2/26/24.
//

#ifndef RAY_TRACING_HITTABLE_H
#define RAY_TRACING_HITTABLE_H

#include "constants.h"

class material;

class hitRecord{
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr<material> mat;

    void set_face_normal(const ray& r, const vec3& out_normal){
        front_face = dot(r.direction(), out_normal) < 0;
        normal = front_face? out_normal: -out_normal;
    }
};

class hittable{
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hitRecord& rec) const = 0;
};

#endif //RAY_TRACING_HITTABLE_H
