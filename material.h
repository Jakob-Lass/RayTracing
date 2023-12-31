#ifndef MATERIAL_H
#define MATERIAL_H


#include "RayTracing.h"
#include "vec3.h"


class hit_record;

class material {
public:
	virtual ~material() = default;

	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& r_out) const = 0;

};

class lambertian:public material
{
public:
	lambertian(const color& col) : albedo(col){}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& r_out)
		const override {
		auto scatter_direction = rec.normal + random_unit_vector();
		if (scatter_direction.near_zero())
		{
			scatter_direction = rec.normal;
		}
		r_out = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}
	
private:
	color albedo;
};



class metal: public material
{
public:
	metal(const color& col, double f) : albedo(col), fuzz(f<1?f:1) {}



	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& r_out)
		const override {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal)+
			fuzz*random_unit_vector();
		r_out = ray(rec.p, reflected);
		attenuation = albedo;
		return dot(r_out.direction(), rec.normal)>0;
	}

private:
	color albedo;
	double fuzz; // fuzzyness
};


class dielectric : public material
{
public:
	dielectric(double index_of_refraction) : ir(index_of_refraction) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& r_out)
		const override {
		attenuation = color(1, 1, 1); // could be changed
		double refraction_ratio = rec.front_face ? (1.0 / ir) : ir; // if inside to outside, reverse reflective index

		// check if refraction is possible
		auto unit_direction = unit_vector(r_in.direction());

		double cos_theta = fmin(dot(-unit_direction, rec.normal),1);
		double sin_theta = sqrt(1 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1;

		vec3 direction;
		if (cannot_refract || reflectance(cos_theta,refraction_ratio) > random_double()) // reflect if only possibility or if reflectance is probable
		{
			direction = reflect(unit_direction, rec.normal);
		}
		else 
		{
			direction = refract(unit_direction, rec.normal, refraction_ratio);
		}

		r_out = ray(rec.p, direction);
		return true;
	}

private:
	double ir;

	static double reflectance(double cosine, double ref_idx) {
		//Schlick's approximation
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};


#endif // !MATERIAL_H