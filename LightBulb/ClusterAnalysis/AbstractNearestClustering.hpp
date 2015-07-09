#pragma once

#ifndef _ABSTRACTNEARESTCLUSTERING_H_
#define _ABSTRACTNEARESTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>
#include <map>

// Includes
#include "ClusterAnalysis\AbstractClustering.hpp"
#include "ClusterAnalysis\Point.hpp"

// Forward declarations
struct Cluster;
class PointSet;

// This class contains all stuff needed to calculate clusters with any ? nearest cluster algorithm 
class AbstractNearestClustering : public AbstractClustering
{
protected:
	virtual void addKNearestPointsToCluster(PointSet& points, Cluster& cluster, Point &pointToAdd, double parameter) = 0;
	// Compares two pairs (Point, distance) (used to order points depending on their distance)
	static bool pairCompare(const std::pair<Point*, double>& a ,const std::pair<Point*, double>& b);	

public:
	// Refresh cache
	virtual void calculateCache(PointSet& points) = 0;
	// Calculates from the given points a specified count of cluster depending on k (nearestPointsCount)
	std::unique_ptr<std::list<Cluster>> doClustering(PointSet& points, double parameter, int dimensionCount);
};

#endif