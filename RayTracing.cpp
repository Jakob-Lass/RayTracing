// RayTracing.cpp : Defines the entry point for the application.
//
#include "_tools.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "RayTracing.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "camera.h"

using namespace std;





int main()
{
	// Desired aspect ratio
	auto aspect_ratio = 16.0 / 9.0;

	int image_width = 400; // Wanted width

	// Setup WORLD

	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;
	cam.aspect_ratio = aspect_ratio;
	cam.image_width = image_width;
	cam.samples_per_pixel = 100;
	cam.max_depth = 5;

	const char *file = "C:\\Users\\lassj\\source\\repos\\RayTracing\\Output\\test5.ppm";
	
	cam.render(world,file);


	
	
	return 0;
}
