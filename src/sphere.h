#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"

class sphere : public hittable{
    public:
        sphere(const point3& center, double radius) : center(center), radius(radius) {}
        bool hit(const ray& r, interval ray_t, double ray_tmin, hit_record& rec) const override
        {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot_product((r.direction()), oc);
            auto c = oc.length_squared() - radius*radius;
            auto discriminant = h*h - a*c;
            if(discriminant < 0){
                return false;
            } 
            auto sqrtd = std::sqrt(discriminant);
            auto t  = (h-sqrtd)/a; //first sol
            if(!ray_t.surrounds(t)){
                t = (h + sqrtd) / a; //second sol
                if(!ray_t.surrounds(t)){
                    return false;
                }
            }
            rec.t = t;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normals(r, outward_normal);

            return true;
        }
        
    private:    
        double radius;
        point3 center;
};
#endif