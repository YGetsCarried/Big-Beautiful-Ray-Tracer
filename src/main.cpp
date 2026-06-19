#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>
#include <fstream>


color color_ray(const ray& r){
    return color(0, 0, 0);
}

int main(){

    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);

    image_height = (image_height < 1) ? 1 : image_height;

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height / (double(image_width) / image_height); 

    std::ofstream MyFile("image.ppm");
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    MyFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int i = 0; i < image_height; i++){
        std::clog << "\rScanlines Remaining: " << (image_height - i) << ' ' << std::flush; //forces output immediately 
        for(int j = 0; j < image_width; j++){
            auto pixel_color = color(double(j)/(image_width -1), double(i)/(image_height -1), 0);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone              \n";
    return 0;
}