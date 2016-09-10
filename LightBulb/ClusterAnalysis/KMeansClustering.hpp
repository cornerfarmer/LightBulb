#pragma once

#ifndef _KMEANSCLUSTERING_H_
#define _KMEANSCLUSTERING_H_

// Library includes
#include <vector>
#include <memory>

// Includes
#include "ClusterAnalysis/AbstractClustering.hpp"
#include "ClusterAnalysis/Point.hpp"
#include "ClusterAnalysis/Cluster.hpp"
#include "Random/AbstractRandomGeneratorUser.hpp"

namespace LightBulb
{
	// Forward declarations
	struct Cluster;
	class Teacher;
	class PointSet;
	class AbstractRandomGenerator;

	// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
	class KMeansClustering : public AbstractClustering, public AbstractRandomGeneratorUser
	{
	private:
	public:
		// Execute the clustering algorithm and calculate n-th clusters in the given point set
		std::unique_ptr<std::list<Cluster>> doClustering(PointSet &points, int clusterCount, int dimensionCount);
	};
}

#endif
