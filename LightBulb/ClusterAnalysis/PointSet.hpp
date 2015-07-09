#pragma once

#ifndef _POINTSET_H_
#define _POINTSET_H_

// Library includes
#include <list>

// Forward declarations
struct Point;

// This class contains all stuff needed to describe a ROLFNeuronPlacer 
class PointSet : public std::list<Point*>
{
private:
	// Holds the maximum position distance
	float maxPositionDistance;
	// Holds the maximum value distance
	float maxValueDistance;
public:
	PointSet();
	float getMaxPositionDistance();
	float getMaxValueDistance();
	// Recalculate the max distances
	void refreshMaxDistances();
};

#endif