// RayTracing.cpp : Defines the entry point for the application.
//
#include "_tools.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "RayTracing.h"

#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "material.h"
#include "camera.h"

using namespace std;





int main()
{
	// Desired aspect ratio
	auto aspect_ratio = 16.0 / 9.0;

	int image_width = 1024; // Wanted width

	// Setup WORLD

	hittable_list world;
	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = make_shared<dielectric>(1.5);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	camera cam;
	cam.aspect_ratio = aspect_ratio;
	cam.image_width = image_width;
	cam.samples_per_pixel = 200;
	cam.max_depth = 50;
	
	cam.vfov = 20;
	 
	cam.look_from = point3(-2, 2, 1);
	cam.look_at = point3(0, 0, -1);
	cam.vup = vec3(0, 1, 0);
	

	const char *file = "C:\\Users\\lassj\\source\\repos\\RayTracing\\Output\\test15.ppm";
	
	cam.render(world,file);


	
	
	return 0;
}
