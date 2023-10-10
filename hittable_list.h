#ifndef HITTABLE_LIST_H
#def HITTABLE_LIST_H


#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list :public hittable
{
	std::vector<shared_ptr<hittable>> objects;

	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }



	void clear(){objects.clear() }

	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	bool hit(const ray& ray, double t_min, double t_max, hit_record& hr) const override {
		hit_record temp_hr;
		bool hit_anything = false;
		auto closest_so_far = t_max;

		for (const auto& obj : objects) {
			if (obj->hit(ray, t_min, closest_so_far, temp_hr)) {
				hit_anything = true;
				closest_so_far = temp_hr.t;
				hr = temp_hr;
			}
		}

		return hit_anything;
	}

};


#endif

