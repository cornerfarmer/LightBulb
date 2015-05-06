#pragma once

#ifndef _KNEARESTCLUSTERING_H_
#define _KNEARESTCLUSTERING_H_

// Library includes
#include <vector>

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
	std::vector<std::vector<std::pair<int, float>>> distanceToPointCache;
	void addKNearestPointsToCluster(std::vector<Point>& points, std::vector<int>& clusterFromPoint, std::vector<Cluster>& clusters, int pointIndex, int clusterIndex, int nearestPointsCount, bool useCache);
	static bool KNearestClustering::pairCompare(const std::pair<int, float>& a ,const std::pair<int, float>& b);
	
public:
	// Calculates from the given points a specified count of cluster
	std::unique_ptr<std::vector<Cluster>> doClustering(std::vector<Point>* points, int clusterCount, int dimensionCount);
	std::unique_ptr<std::vector<Cluster>> doClustering(std::vector<Point>* points, int nearestPointsCount, int dimensionCount, bool useCache);
	void flushCache(int pointCount);
};

#endif