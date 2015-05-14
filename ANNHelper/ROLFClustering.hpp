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
	// A rate which describes how fast neuron centers will be adjusted
	float centerLearningRate;
	// A rate which describes how fast neuron widths will be adjusted
	float widthLearningRate;
	// A multiplier which will be used to increase widths
	float widthMultiplier;
	ROLFClusteringOptions()
	{
		widthMultiplier = 2;
		centerLearningRate = 0.05;
		widthLearningRate = 0.05;
	}
};

// This class contains all stuff needed to calculate clusters with the rolf (regional and online learnable fields) clustering algorithm 
class ROLFClustering : public AbstractClustering
{
private:
	ROLFClusteringOptions options;
public:
	// Execute the clustering algorithm and calculate a specified count clusters which depends on the given points
	std::unique_ptr<std::list<Cluster>> doClustering(std::list<Point*> &points, int dimensionCount);
	ROLFClustering(ROLFClusteringOptions &options_);
};

#endif