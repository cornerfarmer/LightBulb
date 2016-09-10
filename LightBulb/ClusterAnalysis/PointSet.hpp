#pragma once

#ifndef _POINTSET_H_
#define _POINTSET_H_

// Library includes
#include <list>

namespace LightBulb
{
	// Forward declarations
	struct Point;

	// This class contains all stuff needed to describe a ROLFNeuronPlacer 
	class PointSet : public std::list<Point*>
	{
	private:
		// Holds the maximum position distance
		double maxPositionDistance;
		// Holds the maximum value distance
		double maxValueDistance;
	public:
		PointSet();
		double getMaxPositionDistance();
		double getMaxValueDistance();
		// Recalculate the max distances
		void refreshMaxDistances();
	};
}

#endif