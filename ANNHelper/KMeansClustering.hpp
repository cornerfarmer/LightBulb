#pragma once

#ifndef _KMEANSCLUSTERING_H_
#define _KMEANSCLUSTERING_H_

// Library includes
#include <vector>

// Forward declarations
struct Cluster;
class Teacher;

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class KMeansClustering 
{
private:
	// Calculates the distance between two points
	float getDistanceBetweenPoints(std::vector<float> &point1, std::vector<float> &point2);
public:
	// Calculates from the given points a specified count of cluster
	std::unique_ptr<std::vector<Cluster>> doClustering(std::vector<std::vector<float>>* points, int clusterCount, int dimensionCount);
};

#endif