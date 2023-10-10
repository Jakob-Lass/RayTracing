#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"


class sphere :public hittable {
public:
	sphere(point3 _centre, double _radius) : center(_center), radius(_radius) {}

	bool hit(const ray& ray, double t_min, double t_max, hit_record& hr)
	{
		vec3 oc = r.origin() - center;
		auto a = r.direction().length_squared();
		auto halfb = dot(oc, r.direction());
		auto c = oc.length_squared() - radius * radius;
		auto D = halfb * halfb - a * c;
		if (D < 0)	{return false;}
		
		auto sqrtD = sqrt(D);

		auto root = (-halfb - Dsq) / a;

		if (root <= t_min || root >= t_max) // if first root is outside allowed time
		{
			root = (-halfb + Dsq) / a; // calculate the other
			if (root <= t_min || root >= t_max) return false;
		}
		// Else! we have the root we want

		rec.t = root;
		rec.p = r.at(root);
		vec3 outward_normal = (rec.p - center) / radius; // unit normal
		rec.set_face_normal(ray, outward_normal);


		return true
	}

private:
	point3 center;
	double radius
};

#endif
