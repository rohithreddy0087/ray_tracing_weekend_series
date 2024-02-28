//
// Created by rrr on 2/26/24.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "constants.h"
#include "color.h"
#include "hittable.h"
#include "material.h"

class camera{
public:
    double aspect_ratio{16.0/9.0};
    int img_width{400};
    int samples_per_pixel{10};
    int max_child_rays{10};
    double vfov{90};
    point3 lookfrom{-2,2,1};
    point3 lookat{0,0,-1};
    vec3 vup {0,1,0};
    double defocus_angle{0};
    double focus_dist{10};

    void render(const hittable& world){
        initalize();
        std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

        for(int j = 0; j < img_height; ++j){
            std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
            for(int i = 0; i < img_width; ++i){

                color pixel_color(0,0,0);
                for( int sample = 0; sample < samples_per_pixel; ++sample){
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_child_rays, world);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }

        std::clog<<"\rDone.             \n";
    }



private:
    //img height is calculated based on aspect ratio and image width, its needs to be atleast 1
    int img_height{static_cast<int>(img_width/aspect_ratio)};
    point3 camera_center;
    point3 pixel00_loc;
    // Viewport delta vectors
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u, v, w;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;

    double shadow_acne{0.001};

    void initalize(){
        img_height = (img_height < 1) ? 1: img_height;
        camera_center = lookfrom;

        auto theta{degrees_to_radians(vfov)};
        auto h{tan(theta/2)};
//        auto focal_length = (lookfrom - lookat).length();
        double viewport_ht {2.0*h*focus_dist}; // -1 to 1
        double viewport_wt {viewport_ht*static_cast<double>(img_width/img_height)};

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        // Viewport Vectors Vu, Vv
        vec3 viewport_u = viewport_wt*u;
        vec3 viewport_v = -viewport_ht*v;
        pixel_delta_u = viewport_u/img_width;
        pixel_delta_v = viewport_v/img_height;

        // Location of upper left pixel
        point3 viewport_upper_left = camera_center - (focus_dist*w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    color ray_color(const ray& r, int depth, const hittable& world) {

        if(depth <=0) return color(0,0,0);
        hitRecord rec;

        if (world.hit(r, interval(shadow_acne, infinity), rec)) {
            ray scattered;
            color attenuation;
            if(rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation* ray_color(scattered, depth-1, world);
            return color(0,0,0);
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0); // to make it from 0 to 1
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

    ray get_ray(int i, int j) const {
        auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
        auto ray_direction = pixel_sample - camera_center;
        ray r(ray_origin, ray_direction);
        return r;
    }

    vec3 pixel_sample_square() const{
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py* pixel_delta_v);
    }

    point3 defocus_disk_sample() const {
        auto p = random_in_unit_disk();
        return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
};
#endif //RAY_TRACING_CAMERA_H
