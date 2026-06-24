#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3{

    public:
        // e[3] -> x, y, z respectively
        double e[3];
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);} //unary operator, allows vector negation
        double operator[](int i) const {return e[i];} 
        double& operator[](int i) {return e[i];} 

        vec3& operator+=(const vec3& v){
            e[0] += v.x();
            e[1] += v.y();
            e[2] += v.z();
            return *this;
        }
        vec3& operator-=(const vec3& v){
            e[0] -= v.x();
            e[1] -= v.y();
            e[2] -= v.z();
            return *this;
        }
        vec3& operator*=(const vec3& v){
            e[0] *= v.x();
            e[1] *= v.y();
            e[2] *= v.z();
            return *this;
        }
        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double t) {
            return *this *= 1/t;
        }
        double length() const{
            return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        double length_squared() const{
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        static vec3 random(){return vec3(rand_num_gen(), rand_num_gen(), rand_num_gen());}
        static vec3 random(double min, double max){return vec3(rand_num_gen(min,max), rand_num_gen(min,max), rand_num_gen(min,max));}
    
};
using point3 = vec3;
inline std::ostream& operator<<(std::ostream& out, const vec3& v){
    out << ' ' << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    return out;
}
inline vec3 operator+(const vec3& v1, const vec3& v2){
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
inline vec3 operator-(const vec3& v1, const vec3& v2){
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}
inline vec3 operator*(const vec3& v1, const vec3& v2){
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}
inline vec3 operator*(double t, const vec3& v2){
    return vec3(t * v2.x(), t * v2.y(), t * v2.z());
}
inline vec3 operator*(const vec3& v2, double t){
    return vec3(t * v2.x(), t * v2.y(), t * v2.z());
}
inline vec3 operator/(const vec3& v2, double t){
    return vec3(v2.x() / t, v2.y() / t, v2.z() / t);
}
inline double dot_product(const vec3& v1, const vec3& v2){
    return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
} 
inline vec3 cross_product(const vec3& v1, const vec3& v2){
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}
inline vec3 unit_vector(const vec3& v){
    return v / v.length();
}
inline vec3 random_unit_vector(){
    while(true){
        auto p = vec3::random(-1,1);
        auto lensq = p.length_squared();
        if(lensq <= 1 && lensq > 1e-160){
            return p/sqrt(lensq);
        }
    }
}
inline vec3 random_on_hemisphere(const vec3& normal){
    vec3 rand_vector = random_unit_vector();
    if(dot_product(normal, rand_vector) > 0.0)
        return rand_vector;
    else
        return -rand_vector;
    
}
#endif 