#pragma once

#ifndef _KNEARESTCLUSTERING_H_
#define _KNEARESTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>
#include <map>

// Includes
#include "ClusterAnalysis/AbstractNearestClustering.hpp"
#include "ClusterAnalysis/Point.hpp"

namespace LightBulb
{
	// Forward declarations
	struct Cluster;
	class PointSet;

	// This class contains all stuff needed to calculate clusters with the k-nearest cluster algorithm 
	// This algorithm connects to every point its k nearest points. By doing this it is possible that clusters/groups occur.
	class KNearestClustering : public AbstractNearestClustering
	{
	private:
		// Caches the ordered relative position between two points (e.q. A -> B, 2 means A is the second nearest point relative to B)
		std::map<Point*, std::vector<std::pair<Point*, int>>> nthNearestPointToPoint;
		// Add all points which have the pointToAdd in their k-nearest points list to the cluster
		void addKNearestPointsToCluster(PointSet& points, Cluster& cluster, Point &pointToAdd, double nearestPointsCount) override;
	public:
		// Refresh cache (nthNearestPointToPoint)
		void calculateCache(PointSet& points) override;
	};
}

#endif