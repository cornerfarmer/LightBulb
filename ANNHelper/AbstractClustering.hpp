#pragma once

#ifndef _ABSTRACTCLUSTERING_H_
#define _ABSTRACTCLUSTERING_H_

// Library includes
#include <vector>

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class AbstractClustering 
{
protected:
	// Calculates the distance between two points
	float getDistanceBetweenPoints(std::vector<float> &point1, std::vector<float> &point2);
public:
	virtual ~AbstractClustering() {}
};

#endif