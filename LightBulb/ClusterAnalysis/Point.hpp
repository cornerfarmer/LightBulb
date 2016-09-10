#pragma once

#ifndef _POINT_H_
#define _POINT_H_

// Library includes
#include <vector>
#include <cstddef>

// Includes
#include "ClusterAnalysis/ValuePosition.hpp"

namespace LightBulb
{
	// Forward declarations
	struct Cluster;

	// This class contains all stuff needed to describe a Point 
	struct Point
	{
		// Position of the point
		ValuePosition valPos;
		// Cluster which contains this point
		Cluster* cluster;
		Point(std::vector<double> &position_, std::vector<double> &value_)
			: valPos(position_, value_)
		{
			cluster = NULL;
		}
		Point()
		{
			cluster = NULL;
		}
	};
}

#endif
