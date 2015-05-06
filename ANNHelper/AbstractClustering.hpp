#pragma once

#ifndef _ABSTRACTCLUSTERING_H_
#define _ABSTRACTCLUSTERING_H_

// Library includes
#include <vector>

// Forward declarations
struct Cluster;
struct Point;

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class AbstractClustering 
{
protected:
	// Calculates the distance between two points
	float getDistanceBetweenPoints(Point &point1, Point &point2);
	float getDistanceBetweenPositions(std::vector<float> &pos1, std::vector<float> &pos2);
public:
	virtual ~AbstractClustering() {}
	virtual std::unique_ptr<std::vector<Cluster>> doClustering(std::vector<Point>* points, int clusterCount, int dimensionCount) = 0;
};

#endif