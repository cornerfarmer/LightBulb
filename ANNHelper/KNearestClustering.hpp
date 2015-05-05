#pragma once

#ifndef _KNEARESTCLUSTERING_H_
#define _KNEARESTCLUSTERING_H_

// Library includes
#include <vector>

// Includes
#include "AbstractClustering.hpp"

// Forward declarations
struct Cluster;
class Teacher;

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class KNearestClustering : public AbstractClustering
{
private:
	void addKNearestPointsToCluster(std::vector<std::vector<float>>& points, std::vector<int>& clusterFromPoint, std::vector<Cluster>& clusters, int pointIndex, int clusterIndex, int nearestPointsCount);
	static bool KNearestClustering::pairCompare(const std::pair<int, float>& a ,const std::pair<int, float>& b);
public:
	// Calculates from the given points a specified count of cluster
	std::unique_ptr<std::vector<Cluster>> doClustering(std::vector<std::vector<float>>* points, int clusterCount, int dimensionCount);
};

#endif