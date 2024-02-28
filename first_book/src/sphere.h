//
// Created by rrr on 2/26/24.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H
#include "hittable.h"

class sphere: public hittable{
public:
    sphere(point3 center, double radius, shared_ptr<material> mat): kcenter(center), kradius(radius), kmat(mat){}

    bool hit(const ray& r, interval r_t, hitRecord& rec) const override{
        vec3 oc = r.origin() - kcenter;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - kradius*kradius;
        auto discriminant = half_b*half_b - a*c;

        if (discriminant < 0) {
            return false;
        } else {
            auto sqroot = sqrt(discriminant);
            auto root = (-half_b -  sqroot) / a;

            // Return false if both the roots are out of range
            if(!r_t.surrounds(root)){
                root = (-half_b +  sqroot) / a;
                if(!r_t.surrounds(root)){
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(root);
            vec3 out_normal = (rec.p - kcenter)/kradius; //unit vector
            rec.set_face_normal(r, out_normal);
            rec.mat = kmat;
            return true;
        }
    }
private:
    point3 kcenter;
    double kradius;
    shared_ptr<material> kmat;
};
#endif //RAY_TRACING_SPHERE_H
