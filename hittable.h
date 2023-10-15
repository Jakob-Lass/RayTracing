#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "RayTracing.h"
#include "aabb.h"


class material;

class hit_record {
public:
	point3 p; // Intersection point
	vec3 normal; // normal to surface at p

	shared_ptr<material> mat; // entry point for the material
	double t; // Intersection 'time'

	bool front_face;

	void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		// Set the boolean flag whether the intersection is from the outside or not
		// Assuming that outward_normal has unit length
		front_face = dot(r.direction(), outward_normal) < 0; // opposing = we hit the face
		normal = front_face ? outward_normal : -outward_normal;
	}
};


class hittable {
public:
	virtual ~hittable() = default;
	
	virtual bool hit(const ray& r, interval  ray_t, hit_record& rec) const = 0;
	virtual aabb bounding_box() const = 0;

private:
	color albedo;
};




#endif

