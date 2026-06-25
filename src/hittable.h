#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"
#include "interval.h"
#include <memory>

class material;

class hit_record{
    public:
        point3 p;
        double t;
        vec3 normal;
        shared_ptr<material> mat;
        bool front_face;
        void set_face_normals(const ray &r, const vec3& normal_vector)
        {
            front_face = dot_product(r.direction(), normal_vector) < 0;
            normal = front_face ? normal_vector : -normal_vector; 
        }
};
class hittable{
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
#endif