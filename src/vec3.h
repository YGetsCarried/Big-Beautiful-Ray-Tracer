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
        vec3& operator/=(double t) {
            return *this *= 1/t;
        }
        double length() const{
            return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        double length_squared(){
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
    }
};



#endif 