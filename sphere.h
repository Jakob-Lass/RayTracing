#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"


class sphere :public hittable {
public:
	sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

	bool hit(const ray& r, interval ray_t, hit_record& hr) const override
	{
		vec3 oc = r.origin() - center;
		auto a = r.direction().length_squared();
		auto halfb = dot(oc, r.direction());
		auto c = oc.length_squared() - radius * radius;
		auto D = halfb * halfb - a * c;
		if (D < 0)	{return false;}
		
		auto sqrtD = sqrt(D);

		auto root = (-halfb - sqrtD) / a;

		if (!ray_t.surrounds(root)) // if first root is outside allowed time
		{
			root = (-halfb + sqrtD) / a; // calculate the other
			if (!ray_t.surrounds(root)) return false;
		}
		// Else! we have the root we want

		hr.t = root;
		hr.p = r.at(hr.t);
		hr.normal = (hr.p - center) / radius;
		vec3 outward_normal = (hr.p - center) / radius; // unit normal
		hr.set_face_normal(r, outward_normal);

		
		return true;
	}

private:
	point3 center;
	double radius;
};

#endif
