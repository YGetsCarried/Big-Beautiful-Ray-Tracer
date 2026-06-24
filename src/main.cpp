#include <fstream>
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_lists.h"
#include "sphere.h"
#include "camera.h"


int main(){

    hittable_lists world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.max_bounces = 50;

    cam.render(world);
    return 0;
}