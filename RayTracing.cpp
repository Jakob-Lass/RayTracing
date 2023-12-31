﻿// RayTracing.cpp : Defines the entry point for the application.
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
#include "bvh.h"

// timing
#include <chrono>

using namespace std;





int main()
{
    
	// Setup WORLD

	hittable_list world;
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_range(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.look_from = point3(13, 2, 3);
    cam.look_at = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;
	

	const char *file = "C:\\Users\\lassj\\source\\repos\\RayTracing\\Output\\final_un_optimized.ppm";
    const char* file2= "C:\\Users\\lassj\\source\\repos\\RayTracing\\Output\\final_optimized.ppm";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	cam.render(world,file);
    std::chrono::steady_clock::time_point mid = std::chrono::steady_clock::now();

    world = hittable_list(make_shared<bvh_node>(world));
    cam.render(world, file2);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::clog << "Time   optimized = " << std::chrono::duration_cast<std::chrono::microseconds>(end - mid).count()/1000000.0 << "[s]" << std::endl;
    std::clog << "Time unoptimized = " << std::chrono::duration_cast<std::chrono::microseconds>(mid - begin).count() / 1000000.0 << "[s]" << std::endl;

	
	return 0;
}
