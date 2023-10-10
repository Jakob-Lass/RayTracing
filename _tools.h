#ifndef _TOOLS_H
#define _TOOLS_H


#include <cmath>
#include <limits>
#include <memory>

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


// Common Headers

#include "ray.h"
#include "vec3.h"


#endif // !_TOOLS_H

