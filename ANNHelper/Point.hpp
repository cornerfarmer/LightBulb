#pragma once

#ifndef _POINT_H_
#define _POINT_H_

// Library includes
#include <vector>

// Forward declarations
struct Cluster;

// This class contains all stuff needed to describe a Point 
struct Point
{
	// Position of the point
	std::vector<float> position;
	// Value of the point
	std::vector<float> value;
	// Cluster which contains this point
	Cluster* cluster;
	Point(std::vector<float> &position_, std::vector<float> &value_)
	{
		position = position_;
		value = value_;
		cluster = NULL;
	}
	Point()
	{
		position = std::vector<float>();
		value = std::vector<float>();
		cluster = NULL;
	}
};

#endif