//
// Created by rrr on 2/26/24.
//

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "constants.h"

class hitRecord;

class material{
public:
    virtual ~material() = default;

    virtual bool scatter( const ray& r, const hitRecord& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian: public material{
public:
    lambertian(const color& albedo): kalbedo(albedo) {}

    bool scatter( const ray& r, const hitRecord& rec, color& attenuation, ray& scattered) const override{
        auto scatter_dir = rec.normal + unit_random_in_unit_sphere();
        if (scatter_dir.near_zero())
            scatter_dir = rec.normal;
        scattered = ray(rec.p, scatter_dir);
        attenuation = kalbedo;
        return true;
    }
private:
    color kalbedo;
};

class metal: public material{
public:
    metal(const color& albedo, const double fuzz): kalbedo(albedo), kfuzz(fuzz<1? fuzz: 1) {}

    bool scatter( const ray& r, const hitRecord& rec, color& attenuation, ray& scattered) const override{
        auto reflected = reflect(unit_vector(r.direction()), rec.normal);
        scattered = ray(rec.p, reflected + kfuzz*unit_random_in_unit_sphere());
        attenuation = kalbedo;
        return true;
    }
private:
    color kalbedo;
    double kfuzz;
};

class dielectric: public material{
public:
    dielectric(double refractive_index): krefractive_index(refractive_index){}

    bool scatter( const ray& r, const hitRecord& rec, color& attenuation, ray& scattered) const override{
        auto eta_ratio = rec.front_face ? (1.0/krefractive_index): krefractive_index;

        auto incident_ray = unit_vector(r.direction());
        double cos_t = fmin(dot(-incident_ray, rec.normal), 1.0);
        double sin_t = sqrt(1-cos_t*cos_t);

        bool cannot_refract = eta_ratio*sin_t > 1.0;
        vec3 scattered_dir;

        if (cannot_refract || reflectance(cos_t, eta_ratio) > random_double()){
            scattered_dir = reflect(incident_ray, rec.normal);
        }else{
            scattered_dir = refract(incident_ray, rec.normal, eta_ratio);
        }

        scattered = ray(rec.p, scattered_dir);
        attenuation = color(1.0,1.0,1.0);
        return true;
    }
private:
    double krefractive_index;

    static double reflectance(double cosine, double eta_ratio) {
        auto r0 = (1-eta_ratio) / (1+eta_ratio);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }

};
#endif //RAY_TRACING_MATERIAL_H
