#pragma once

#ifndef _KMEANSCLUSTERING_H_
#define _KMEANSCLUSTERING_H_

// Library includes
#include <vector>

// Includes
#include "AbstractClustering.hpp"
#include "Point.hpp"
#include "Cluster.hpp"

// Forward declarations
struct Cluster;
class Teacher;

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class KMeansClustering : public AbstractClustering
{
private:

public:
	// Calculates from the given points a specified count of cluster
	std::unique_ptr<std::list<Cluster>> doClustering(std::list<Point*> &points, int clusterCount, int dimensionCount);
};

#endif