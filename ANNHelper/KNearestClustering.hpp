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

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class KNearestClustering : public AbstractClustering
{
private:
	std::map<Point*, std::vector<std::pair<Point*, float>>> distanceToPointCache;
	void addKNearestPointsToCluster(std::list<Point*>& points, Cluster& cluster, Point &pointToAdd, int nearestPointsCount, bool useCache);
	static bool KNearestClustering::pairCompare(const std::pair<Point*, float>& a ,const std::pair<Point*, float>& b);
	
public:
	// Calculates from the given points a specified count of cluster
	std::unique_ptr<std::list<Cluster>> doClustering(std::list<Point*>& points, int clusterCount, int dimensionCount);
	std::list<Cluster>* doClustering(std::list<Point*>& points, int nearestPointsCount, int dimensionCount, bool useCache);
	void flushCache(int pointCount);
};

#endif