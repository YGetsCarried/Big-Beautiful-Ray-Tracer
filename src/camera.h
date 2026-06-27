#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include "rtweekend.h"
#include "hittable.h"
#include "ray.h"
#include "color.h"
#include "material.h"

class camera{
    public:
        double aspect_ratio = 1.0;
        int image_width  = 100;
        int samples_per_pixel = 100;
        int max_bounces = 10;
        double vfov = 90;
        point3 lookfrom = point3(0,0,0);
        point3 lookat = point3(0,0,-1);
        point3 vup = vec3(0,1,0);
        double defocus_angle = 0;  // Variation angle of rays through each pixel
        double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus



        void render(const hittable& world){
            initialize();
            std::ofstream MyFile("image.ppm");
            MyFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
            for(int i = 0; i < image_height; i++){
                std::clog << "\rScanlines Remaining: " << (image_height - i) << ' ' << std::flush; //forces output immediately 
                for(int j = 0; j < image_width; j++){
                    color pixel_color(0,0,0);
                    for(int sample = 0; sample < samples_per_pixel; sample++){
                        ray r = getRay(i,j); //rand ray within pixel (i,j)
                        pixel_color += ray_color(r, max_bounces, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                    write_color(MyFile, pixel_samples_scale * pixel_color);

                }
            }
            std::clog << "\rDone              \n";
        }
    private:
        int image_height;   
        point3 camera_center;    
        double pixel_samples_scale;   
        point3 pixel00_loc;    
        vec3 pixel_delta_lr;  
        vec3 pixel_delta_ud;  
        vec3 u,v,w;
        vec3   defocus_disk_u;       // Defocus disk horizontal radius
        vec3   defocus_disk_v;       // Defocus disk vertical radius


        void initialize(){
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0/samples_per_pixel;

            camera_center = lookfrom;


            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta/2);
            auto viewport_height = 2 * h * focus_dist;

            auto viewport_width = viewport_height * (double(image_width) / image_height); 
            

            //viewpoint edge vectors
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross_product(vup, w));
            v = cross_product(w, u);

            vec3 viewport_lr = viewport_width * u;    // Vector across viewport horizontal edge
            vec3 viewport_ud = viewport_height * -v;  // Vector down viewport vertical edge


            //viewpoint delta vectors per pixel
            pixel_delta_lr = viewport_lr/image_width;
            pixel_delta_ud = viewport_ud/image_height;


            auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_lr/2 - viewport_ud/2;

            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_lr + pixel_delta_ud); // center of upper left pixel
            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
 
        }
        ray getRay(int y, int x) const {
            auto offset = sample_square(); // jitter in [-0.5,0.5]^2

            auto pixel_sample =
                pixel00_loc
                + ((x + offset.x()) * pixel_delta_lr)  // horizontal movement
                + ((y + offset.y()) * pixel_delta_ud); // vertical movement

            auto ray_origin =
                (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
            auto ray_direction = pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction);
        }
        color ray_color(const ray& r, int max_bounces, const hittable& world) const {
            hit_record rec;
            if(max_bounces <= 0)
                return color(0,0,0);
            if(world.hit(r, interval(0.001, infinity), rec)){
                ray scattered;
                color attenuation;
                if(rec.mat->scatter(r, rec, attenuation, scattered)){
                    return attenuation * ray_color(scattered, max_bounces-1, world);
                }
                return color(0,0,0);
            }
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
        vec3 sample_square() const {
            return vec3(rand_num_gen() - 0.5, rand_num_gen() - 0.5, 0);
        }
        point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
            auto p = random_in_unit_disk();
            return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        }

        
};

#endif