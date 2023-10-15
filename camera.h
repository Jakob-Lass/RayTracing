#ifndef CAMERA_H
#define CAMERA_H


#include "_tools.h"
#include "color.h"
#include "hittable.h"
#include "_tools.h"
#include "vec3.h"
#include "ray.h"
#include "material.h"
#include <iostream>

using namespace std;


class camera {
public:

	double	aspect_ratio		= 1.0;
	int		image_width			= 100;
	int		samples_per_pixel	= 10;
	int		max_depth			= 10;

	double vfov = 90; // field of view vertically in degrees

	point3 look_from = point3(0.0, 0.0, -1.0); // Origin of camera
	point3 look_at = point3(0.0, 0.0, 0.0); // Point to look at
	vec3 vup = vec3(0.0, 1.0, 0.0); // Local up-direction


	void render(const hittable& world, const char* file)
	{
		initialize();
		// Setup file
		FILE* f = freopen(file, "w", stdout);

		// Setup headers
		cout << "P3\n" << image_width << " " << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++)
		{
			clog << "\rScanlines remaing: " << (image_height - j) << " " << std::flush;
			for (int i = 0; i < image_width; i++)
			{
				color pixel_color(0.0, 0.0, 0.0);
				for (int sample = 0; sample < samples_per_pixel; sample++)
				{
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				
				//auto c = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
				write_color(cout, pixel_color, samples_per_pixel);

			}
		}
		clog << "\rRendering done                          \n";

	}

	color ray_color(const ray& r, int depth, const hittable& world) {
		hit_record hr;
		if (depth <= 0)
		{	
			return color(0.0, 0.0, 0.0); // Reached max depth
		}
		if (world.hit(r, interval(0.0000001, infinity), hr))
		{
			ray r_out;
			color attenuation;
			if (hr.mat->scatter(r, hr, attenuation, r_out))
			{
				return attenuation*ray_color(r_out, depth - 1, world);
			}
			return color(0, 0, 0);
		}
		vec3 unit_vector_direction = unit_vector(r.direction());
		auto a = 0.9 * (unit_vector_direction.y() + 1.0);
		return (1.0 - a)* color(1, 1, 1) + a * color(0.5, 0.7, 1.0);
	}

private:


	point3 camera_centre;
	point3 pixel_00_location;
	int image_height;

	vec3   pixel_delta_u;  // Offset to pixel to the right
	vec3   pixel_delta_v;  // Offset to pixel below
	vec3   u, v, w;        // Camera basis vectors

	void initialize()
	{
		image_height = static_cast<int>(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height; // make sure the image height is at least 1 pixel
		
		camera_centre = look_from;
		// Setup camera

		auto focal_length = (look_from-look_at).length(); // eye distance from the view port
		auto theta = deg2rad(vfov); // Vertical field of view in radians
		auto h = tan(theta / 2.0); // Calculate height 
		auto view_port_height = 2.0 * h * focal_length; // height of view port
		auto view_port_width = view_port_height * (static_cast<double>(image_width) / image_height);

		

		// Calculate u,v, and w
		w = unit_vector(look_from - look_at);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);


		// Calculation of vectors across view port
		vec3 view_port_u = view_port_width * u;
		vec3 view_port_v = view_port_height * -v; // y axis starts top left and goes down

		// Calculate pixel sizes
		pixel_delta_u = view_port_u / image_width;
		pixel_delta_v = view_port_v / image_height;

		// Calculate corner position, pixel 0,0 is located half a pixel down and to the right of upper left corner
		auto view_port_upper_left_corner = camera_centre -(focal_length*w) - view_port_u * 0.5 - view_port_v * 0.5;
		pixel_00_location = view_port_upper_left_corner + 0.5 * (pixel_delta_u + pixel_delta_v);


	}

	ray get_ray(int i, int j)
	{
		auto pixel_center = pixel_00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
		auto pixel_sample = pixel_center + pixel_sample_square();

		auto ray_direction = pixel_sample - camera_centre;
		return ray(camera_centre, ray_direction);
	}

	vec3 pixel_sample_square() const
	{
		double px = -0.5 + random_double(); // random_double is on average +0.5
		double py = -0.5 + random_double(); // random_double is on average +0.5
		return (px * pixel_delta_u) + (py * pixel_delta_v);
	}
};


#endif // !CAMERA_H

