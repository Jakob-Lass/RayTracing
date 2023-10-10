#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

static const interval intensity(0.000, 0.999);

inline double linear_to_gamma2(double linear_component) { return sqrt(linear_component); }

void write_color(std::ostream& out, const color c, int samples_per_pixel)
{
	auto r = c.x();
	auto g = c.y();
	auto b = c.z();

	// Scale to take care of samples
	auto scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Convert to gamma 2 space

	r = linear_to_gamma2(r);
	g = linear_to_gamma2(g);
	b = linear_to_gamma2(b);


	out << static_cast<int>(256 * intensity.clamp(r)) << ' '
		<< static_cast<int>(256 * intensity.clamp(g)) << ' '
		<< static_cast<int>(256 * intensity.clamp(b)) << '\n';
}
#endif 
