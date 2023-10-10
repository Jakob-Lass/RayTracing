#ifndef _TOOLS_H
#define _TOOLS_H


#include <cmath>
#include <limits>
#include <memory>
//#include <cstdlib>
#include <random>



// Usings section

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Cosntant section
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// Utility functions
inline double deg2rad(double degrees)
{
	return degrees * pi / 180.0;
}



inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_range(double min, double max)
{
	return min + (max - min) * random_double();
}

// Common Headers

#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif // !_TOOLS_H

