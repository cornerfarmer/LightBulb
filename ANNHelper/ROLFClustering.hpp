#pragma once

#ifndef _ROLFMEANSCLUSTERING_H_
#define _ROLFMEANSCLUSTERING_H_

// Library includes
#include <vector>

// Includes
#include "AbstractClustering.hpp"
#include "Point.hpp"
#include "Cluster.hpp"

// Forward declarations
struct Cluster;
class Teacher;

struct ROLFClusteringOptions 
{
	float centerLearningRate;
	float widthLearningRate;
	float widthMultiplier;
	ROLFClusteringOptions()
	{
		widthMultiplier = 2;
		centerLearningRate = 0.05;
		widthLearningRate = 0.05;
	}
};

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class ROLFClustering : public AbstractClustering
{
private:
	ROLFClusteringOptions options;
public:
	// Execute the clustering algorithm and calculate n-th clusters in the given point set
	std::unique_ptr<std::list<Cluster>> doClustering(std::list<Point*> &points, int clusterCount, int dimensionCount);
	ROLFClustering(ROLFClusteringOptions &options_);
};

#endif