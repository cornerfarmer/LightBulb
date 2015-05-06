#pragma once

#ifndef _POINT_H_
#define _POINT_H_

// Library includes
#include <vector>

// This class contains all stuff needed to describe a Point 
struct Point
{
	std::vector<float> position;
	std::vector<float> value;
	Point(std::vector<float> &position_, std::vector<float> &value_)
	{
		position = position_;
		value = value_;
	}
};

#endif