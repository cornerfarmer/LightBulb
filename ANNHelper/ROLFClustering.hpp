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
class PointSet;

enum ROLFClusteringRadiusInitMethod
{
	// Always use the same radius
	useConstantRadius, 
	// Use the smallest radius of all clusters
	useMinRadius, 
	// Use the biggest radius of all clusters
	useMaxRadius, 
	// Use mean radius of all clusters
	useMeanRadius
};

struct ROLFClusteringOptions 
{
	// A rate which describes how fast neuron centers will be adjusted
	float centerLearningRate;
	// A rate which describes how fast neuron widths will be adjusted
	float widthLearningRate;
	// A multiplier which will be used to increase widths
	float widthMultiplier;
	// Describes the way how the radius of a new cluster should be set
	ROLFClusteringRadiusInitMethod radiusInitMethod;
	// Sets the radius the first new cluster gets or - if 'useConstantRadius' is used - all new cluster get
	float contantInitRadius;
	ROLFClusteringOptions()
	{
		widthMultiplier = 2;
		centerLearningRate = 0.05;
		widthLearningRate = 0.05;
		radiusInitMethod = useMeanRadius;
		contantInitRadius = 0.01f;
	}
};

// This class contains all stuff needed to calculate clusters with the rolf (regional and online learnable fields) clustering algorithm 
class ROLFClustering : public AbstractClustering
{
private:
	ROLFClusteringOptions options;
public:
	// Execute the clustering algorithm and calculate a specified count clusters which depends on the given points
	std::unique_ptr<std::list<Cluster>> doClustering(PointSet &points, int dimensionCount);
	ROLFClustering(ROLFClusteringOptions &options_);
};

#endif