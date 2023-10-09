// RayTracing.cpp : Defines the entry point for the application.
//

#include "RayTracing.h"
#include "color.h"
#include "vec3.h"

using namespace std;




int main()
{
	// Setup file
	FILE *f = freopen("C:\\Users\\lassj\\source\\repos\\RayTracing\\Output\\test2.ppm", "w", stdout);


	int image_width = 256;
	int image_height = 256;

	// Setup headers
	cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)
	{	
		clog << "\rScanlines remaing: " << (image_height - j) << " " << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			auto c = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
			write_color(cout, c);
			
		}
	}
	clog << "\rRendering done                          \n";
	
	return 0;
}
