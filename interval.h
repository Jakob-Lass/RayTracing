#ifndef INTERVAL_H
#define INTERVAL_H

#include "_tools.h"

class interval {
public:
	double min, max;
	interval() : min(+infinity), max(-infinity) {} //Define default interval

	interval(double _min, double _max) : min(_min), max(_max) {};

	interval(const interval& a, const interval& b) :
		min(fmin(a.min, b.min)), max(fmax(a.max, b.max)) {}

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

	double size() const
	{
		return max - min;
	}

	interval expand(double delta) const {
		auto padding = delta * 0.5;
		return interval(min - padding, max + padding);
	}
};

const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif // !INTERVAL_H

