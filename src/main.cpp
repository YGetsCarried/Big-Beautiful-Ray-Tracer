#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>
#include <fstream>


color ray_color(const ray& r){
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0); //convert to [0,1]
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main(){

    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height / (double(image_width) / image_height); 
    auto focal_length = 1.0;
    auto camera_center = point3(0,0,0);

    //viewpoint edge vectors
    auto viewport_lr = vec3(viewport_width, 0, 0);
    auto viewport_ud = vec3(0, -viewport_height, 0);
    //viewpoint delta vectors per pixel
    auto pixel_delta_lr = viewport_lr/viewport_width;
    auto pixel_delta_ud = viewport_ud/viewport_height;

    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_lr/2 - viewport_ud/2; 
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_lr + pixel_delta_ud); // center of upper left pixel 

    std::ofstream MyFile("image.ppm");

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    MyFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int i = 0; i < image_height; i++){
        std::clog << "\rScanlines Remaining: " << (image_height - i) << ' ' << std::flush; //forces output immediately 
        for(int j = 0; j < image_width; j++){
            auto pixel_center = pixel00_loc + (j*pixel_delta_lr) + (i*pixel_delta_ud);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone              \n";
    return 0;
}