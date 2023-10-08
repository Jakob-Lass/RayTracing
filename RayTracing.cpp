// RayTracing.cpp : Defines the entry point for the application.
//

#include "RayTracing.h"

using namespace std;




int main()
{
	// Setup file
	FILE *f = freopen("C:\\Users\\lassj\\source\\repos\\RayTracing\\Output\\test.ppm", "w", stdout);


	int image_width = 256;
	int image_height = 256;

	// Setup headers
	cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)
	{	
		clog << "\rScanlines remaing: " << (image_height - j) << " " << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height- 1);
			auto b = 0;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			cout << ir << " " << ig << " " << ib << endl;
		}
	}
	clog << "\rRendering done                          \n";
	
	return 0;
}
