#ifndef BVH_H
#define BVH_H

#include "RayTracing.h"

#include "hittable.h"
#include "hittable_list.h"

#include "_tools.h"


class bvh_node : public hittable {
public:
	bvh_node(const hittable_list &list): bvh_node(list.objects, 0, list.objects.size()) {}

	bvh_node(const std::vector<shared_ptr<hittable>>& src_objects, size_t start, size_t end)
	{
		auto objects = src_objects;

		int axis = random_int(0, 2); // choose a random axis


		auto comparer = (axis == 0) ? box_x_compare
			: (axis == 1) ? box_y_compare 
			: box_z_compare;

		size_t objects_span = end - start;

		if (objects_span == 1) { // only one element
			left = right = objects[start]; // dublicate
		}
		else if (objects_span == 2) {
			if (comparer(objects[start], objects[start + 1])) {
				left = objects[start];
				right = objects[start+1];
			}
			else {
				left = objects[start + 1];
				right = objects[start];
			}
		}
		else {
			std::sort(objects.begin() + start, objects.begin() + end, comparer); // if more than two, sort along the random axis and repeat
			auto mid = start + objects_span / 2; // floor division on perpuse
			left = make_shared<bvh_node>(objects, start, mid);
			right = make_shared<bvh_node>(objects, mid, end);
		}

		// calculate total bounding box
		bbox = aabb(left->bounding_box(), right->bounding_box());



	}

	bool hit(const ray& r_in, interval ray_t, hit_record& hr) const override
	{
		if (!bbox.hit(r_in, ray_t))
		{
			return false;
		}
		bool hit_left = left->hit(r_in, ray_t, hr);
		bool hit_right = right->hit(r_in, interval(ray_t.min, hit_left ? hr.t : ray_t.max), hr);

		return hit_left || hit_right;
	}


	aabb bounding_box() const override { return bbox; }
	

private:
	shared_ptr<hittable> right;
	shared_ptr<hittable> left;
	aabb bbox;


	static bool box_compare(
		const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis_index
	) {
		return a->bounding_box().axis(axis_index).min < b->bounding_box().axis(axis_index).min;
	}

	static bool box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
		return box_compare(a, b, 0);
	}

	static bool box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
		return box_compare(a, b, 1);
	}

	static bool box_z_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
		return box_compare(a, b, 2);
	}

};


#endif // !BVH_H
