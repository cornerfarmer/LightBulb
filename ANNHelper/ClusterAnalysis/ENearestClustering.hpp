#pragma once

#ifndef _KNEARESTCLUSTERING_H_
#define _KNEARESTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>
#include <map>

// Includes
#include "ClusterAnalysis\AbstractNearestClustering.hpp"
#include "ClusterAnalysis\Point.hpp"

// Forward declarations
struct Cluster;
class PointSet;

// This class contains all stuff needed to calculate clusters with the e-nearest cluster algorithm 
// This algorithm connects to every point all points with distance smaller than epsilon. By doing this it is possible that clusters/groups occur.
class ENearestClustering : public AbstractNearestClustering
{
private:
	// Caches the orderd distance between all points
	std::map<Point*, std::vector<std::pair<Point*, float>>> distanceToPoint;
	// Add all points of which the distance to pointToAdd is less than epsilon (nearestPointDistance)
	void addKNearestPointsToCluster(PointSet& points, Cluster& cluster, Point &pointToAdd, float nearestPointDistance);
public:
	// Refresh cache (nthNearestPointToPoint)
	void calculateCache(PointSet& points);
	float getBiggestDistance(PointSet& points);
};

#endif