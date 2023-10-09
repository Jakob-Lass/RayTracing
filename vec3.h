#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
	public:
		double e[3]; // elements

		vec3(): e{0,0,0} {} // Simple constructor
		vec3(double e0, double e1, double e2) : e{ e0,e1,e2 } {} // Overloaded constructor with input

		
		double x() const { return e[0]; } // Getter
		double y() const { return e[1]; } // Getter
		double z() const { return e[2]; } // Getter

		vec3 operator-() const { // Negation operator
			return vec3(-e[0], -e[1], -e[2]);
		} 

		double operator[](int i) const { return e[i]; } // Array-like getter
		double& operator[](int i) { return e[i]; } // Array like setter

		vec3& operator+=(const vec3& v) { // addition operator
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		} 

		vec3& operator*=(double t) { // scalar multiplication
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
		}

		vec3& operator/=(double t) {// scalar divide implemented as scalar multiplication of inverse
			return *this *= 1 / t; 
		}

		double length() const {
			return sqrt(length_squared());
		}

		double length_squared() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}
};


// Make point3 a simple copy of vec3 (DANGER OF DOING STUPID STUFF, by hey, such is life)
using point3 = vec3;

// Tools
inline std::ostream& operator << (std::ostream& out, const vec3 vec)
{
	return out << vec.e[0] << ' ' << vec.e[1] << ' ' << vec[2];
}

inline vec3 operator+(const vec3 &v, const vec3& u)
{
	return vec3(v.e[0] + u.e[0], v.e[1] + u.e[1], v.e[2] + u.e[2]);
}


inline vec3 operator-(const vec3& v, const vec3& u)
{
	return vec3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]);
}

inline vec3 operator*(const vec3& v, const vec3& u)
{
	return vec3(v.e[0] * u.e[0], v.e[1] * u.e[1], v.e[2] * u.e[2]);
}

inline vec3 operator*(double t, const vec3 v)
{
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline vec3 operator*(const vec3 v, double t)
{
	return t * v;
}

inline vec3 operator/(const vec3 v, double t)
{
	return (1/t) * v;
}

inline double dot(const vec3& v, const vec3& u)
{
	return v.e[0] * u.e[0] + v.e[1] * u.e[1] + v.e[2] * u.e[2];
}

inline vec3 cross(const vec3& v, const vec3& u)
{
	return vec3(v.e[1] * u.e[2] - v.e[2] * u.e[1],
		v.e[2] * u.e[0] - v.e[0] * u.e[2],
		v.e[1] * u.e[2] - v.e[2] * u.e[1]);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}
#endif