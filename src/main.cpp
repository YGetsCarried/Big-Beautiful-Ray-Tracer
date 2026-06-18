#include <iostream>
#include <fstream>

int main(){
    int image_width = 256;
    int image_height = 256;
    std::ofstream MyFile("image.ppm");
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    MyFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int i = 0; i < image_height; i++){
        std::clog << "\rScanlines Remaining: " << (image_height - i) << ' ' << std::flush; //forces output immediately 
        for(int j = 0; j < image_width; j++){
            auto r = double(j) / (image_width -1);
            auto g = double(i) / (image_height -1);
            auto b = 0.0;
            
            int ir = int(255.999*r);
            int ig = int(255.999*g);
            int ib = int(255.999*b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            MyFile << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\rDone              \n";
    return 0;
}