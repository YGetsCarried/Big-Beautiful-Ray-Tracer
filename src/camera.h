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

        void initialize(){
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0/samples_per_pixel;

            camera_center = point3(0,0,0);

            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width) / image_height); 
            auto focal_length = 1.0;

            //viewpoint edge vectors
            auto viewport_lr = vec3(viewport_width, 0, 0);
            auto viewport_ud = vec3(0, -viewport_height, 0);
            //viewpoint delta vectors per pixel
            pixel_delta_lr = viewport_lr/image_width;
            pixel_delta_ud = viewport_ud/image_height;

            auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_lr/2 - viewport_ud/2; 
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_lr + pixel_delta_ud); // center of upper left pixel 
        }
        ray getRay(int j, int i) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_lr) + (pixel_delta_ud*(offset.y()+j));
            auto ray_origin = camera_center;
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
};

#endif