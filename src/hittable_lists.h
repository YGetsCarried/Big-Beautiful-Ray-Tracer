#ifndef HITTABLE_TEST_H  
#define HITTABLE_TEST_H

#include "hittable.h"
#include "ray.h"
#include <vector>
#include <memory>

class hittable_lists : public hittable{
    public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_lists() {}
    hittable_lists(std::shared_ptr<hittable> object) {add(object);}
    void add(std::shared_ptr<hittable> object){objects.push_back(object);}
    void clear() {objects.clear();}

    bool hit(const ray& r, interval ray_t, double ray_tmin, hit_record& rec) const override{
        hit_record temp_rec;
        bool hit_anything = false;
        double closest = ray_t.max;
        
        for(const auto& object : objects){
            if(object->hit(r, interval(ray_t.min, closest), ray_tmin, temp_rec)){
                hit_anything = true;
                closest = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }

};
#endif