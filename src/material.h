#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "color.h"

class material{
    public:
        virtual ~material() = default;
        virtual bool scatter (
            const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered
        ) const{
            return false;
        }
};
class lambertian : public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered) const override{
            auto scatter_direction = rec.normal + random_unit_vector();

            if(scatter_direction.near_zero()){
                scatter_direction = rec.normal;
            }

            scattered = ray(rec.p, scatter_direction);
            attentuation = albedo;
            return true;
        }
    private:
        color albedo;
};
class metal : public material {
    public:
        metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered) const override{
            auto reflected = reflect(r_in.direction(), rec.normal);
            reflected = unit_vector(reflected) + (fuzz*random_unit_vector());
            scattered = ray(rec.p, reflected);
            attentuation = albedo;
            return (dot_product(scattered.direction(), rec.normal) > 0);
        }
    private:
        color albedo;
        double fuzz;
};
class dielectric : public material {
    public:
        dielectric(double refraction_index) : refraction_index(refraction_index) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered) const override{
            attentuation = color(1.0, 1.0, 1.0);
            double ri = rec.front_face ? (1/refraction_index) : refraction_index;
            vec3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = std::fmin(dot_product(-unit_direction, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = ri * sin_theta > 1.0;
            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, ri) > rand())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, ri);

            scattered = ray(rec.p, direction);
            return true;
        }
    private:
        double refraction_index;
        //schlicks approximation
        static double reflectance(double cos, double reflection_index){
            auto r0 = (1-reflection_index) / (1+reflection_index);
            r0 = r0*r0;
            return r0 + (1-r0)*std::pow((1-cos), 5);
        }
};


#endif