#ifndef INTERVAL_H
#define INTERVAL_H

#include "_tools.h"

class interval {
public:
	double min, max;
	interval() : min(+infinity), max(-infinity) {} //Define default interval

	interval(double _min, double _max) : min(_min), max(_max) {};

	bool contains(double x) const {
		return min <= x && x <= max;
	}

	bool surrounds(double x) const { // stricter version of contains
		return min < x && x < max;
	}

	static const interval empty, universe;

	double clamp(double x) const
	{
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}
};

const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif // !INTERVAL_H

