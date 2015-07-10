// Includes
#include "ClusterAnalysis\PointSet.hpp"
#include "ClusterAnalysis\Point.hpp"
// Library includes
#include <math.h>

void PointSet::refreshMaxDistances()
{
	// Set the max distances to 0
	maxPositionDistance = 0;
	maxValueDistance = 0;
	// Go through all points
	for (auto point = this->begin(); point != this->end(); point++)
	{
		// Go through all other points
		for (auto otherPoint = point; otherPoint != this->end(); otherPoint++)
		{
			// Calculate the position distance between point and otherPoint and set it as the maximum position distance, if it is greater than the current one
			maxPositionDistance = std::max((*point)->valPos.getPositionDistance((*otherPoint)->valPos), maxPositionDistance);
			// Calculate the value distance between point and otherPoint and set it as the maximum value distance, if it is greater than the current one
			maxValueDistance = std::max((*point)->valPos.getValueDistance((*otherPoint)->valPos), maxValueDistance);
		}
	}
}

double PointSet::getMaxPositionDistance()
{
	return maxPositionDistance;
}

double PointSet::getMaxValueDistance()
{
	return maxValueDistance;
}

PointSet::PointSet()
{
	maxPositionDistance = 0;
	maxValueDistance = 0;
}
