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

using namespace std;


color ray_color(const ray& r, const hittable& world) {

	hit_record hr;
	if (world.hit(r,interval(0,infinity),hr))
	{
		return 0.5*(hr.normal + color(1.0, 1.0, 1.0));
	}
	vec3 unit_vector_direction = unit_vector(r.direction());
	auto a = 0.9 * (unit_vector_direction.y() + 1.0);
	return (1.0-a)*color(1, 1, 1)+a*color(0.5,0.7,1.0);
}


int main()
{
	// Desired aspect ratio
	auto aspect_ratio = 16.0 / 9.0;

	int image_width = 400; // Wanted width
	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height; // make sure the image height is at least 1 pixel

	// Setup WORLD

	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


	// Setup camera
	
	auto focal_length = 1.0; // eye distance from the view port
	auto view_port_height = 2.0; // height of view port
	auto view_port_width = view_port_height * (static_cast<double>(image_width) / image_height);

	auto camera_centre = point3(0.0, 0.0, 0.0);

	// Calculation of vectors across view port
	auto view_port_u = vec3(view_port_width, 0.0, 0.0);
	auto view_port_v = vec3(0.0, -view_port_height, 0.0); // y axis starts top left and goes down
	
	// Calculate pixel sizes
	auto pixel_delta_u = view_port_u / image_width;
	auto pixel_delta_v = view_port_v / image_height;

	// Calculate corner position, pixel 0,0 is located half a pixel down and to the right of upper left corner
	auto view_port_upper_left_corner = camera_centre + vec3(0.0, 0.0, -focal_length) - view_port_u * 0.5 - view_port_v * 0.5;
	auto pixel_00_location = view_port_upper_left_corner + 0.5 * (pixel_delta_u + pixel_delta_v);


	// Setup file
	FILE *f = freopen("C:\\Users\\lassj\\source\\repos\\RayTracing\\Output\\test2.ppm", "w", stdout);


	

	// Setup headers
	cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)
	{	
		clog << "\rScanlines remaing: " << (image_height - j) << " " << std::flush;
		for (int i = 0; i < image_width; i++)
		{

			auto pixel_center = pixel_00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_centre;
			ray r(camera_centre, ray_direction);

			color pixel_color = ray_color(r,world);
			//auto c = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
			write_color(cout, pixel_color);
			
		}
	}
	clog << "\rRendering done                          \n";
	
	return 0;
}
