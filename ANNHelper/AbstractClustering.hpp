#pragma once

#ifndef _ABSTRACTCLUSTERING_H_
#define _ABSTRACTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>

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
	void calculateAllClusterWidths(std::list<Cluster> &clusters);
public:
	virtual ~AbstractClustering() {}
	virtual std::unique_ptr<std::list<Cluster>> doClustering(std::list<Point*> &points, int clusterCount, int dimensionCount) = 0;
};

#endif