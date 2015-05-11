#pragma once

#ifndef _KNEARESTCLUSTERING_H_
#define _KNEARESTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>
#include <map>

// Includes
#include "AbstractClustering.hpp"
#include "Point.hpp"

// Forward declarations
struct Cluster;
class Teacher;

// This class contains all stuff needed to calculate clusters with the k-nearest cluster algorithm 
// This algorithm connects to every point its k nearest points. By doing this it is possible that clusters/groups occur.
class KNearestClustering : public AbstractClustering
{
private:
	// Caches the ordered relative position between two points (e.q. A -> B, 2 means A is the second nearest point relative to B)
	std::map<Point*, std::vector<std::pair<Point*, int>>> nthNearestPointToPoint;
	// Add all points which have the pointToAdd in their k-nearest points list to the cluster
	void addKNearestPointsToCluster(std::list<Point*>& points, Cluster& cluster, Point &pointToAdd, int nearestPointsCount);
	// Compares two pairs (Point, distance) (used to order points depending on their distance)
	static bool pairCompare(const std::pair<Point*, float>& a ,const std::pair<Point*, float>& b);	
public:
	// Refresh cache (nthNearestPointToPoint)
	void calculateCache(std::list<Point*>& points);
	// Calculates from the given points a specified count of cluster depending on k (nearestPointsCount)
	std::unique_ptr<std::list<Cluster>> doClustering(std::list<Point*>& points, int nearestPointsCount, int dimensionCount);
};

#endif