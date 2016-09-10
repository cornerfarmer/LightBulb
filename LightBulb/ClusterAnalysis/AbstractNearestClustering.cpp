// Includes
#include "ClusterAnalysis/AbstractNearestClustering.hpp"
#include "ClusterAnalysis/Cluster.hpp"
#include "ClusterAnalysis/Point.hpp"
#include "ClusterAnalysis/PointSet.hpp"

namespace LightBulb
{
	std::unique_ptr<std::list<Cluster>> AbstractNearestClustering::doClustering(PointSet &points, double nearestPointsCount, int dimensionCount)
	{
		// Create a new cluster list
		std::unique_ptr<std::list<Cluster>> clusters(new std::list<Cluster>());

		// Go through every point and set the cluster to null
		for (auto point = points.begin(); point != points.end(); point++)
			(*point)->cluster = NULL;

		// Group every point with its k nearest points
		// Go through every point
		for (auto point = points.begin(); point != points.end(); point++)
		{
			// If the point does not have already a cluster
			if ((*point)->cluster == NULL)
			{
				// Create a new Cluster for this point
				Cluster newCluster;
				// Set the position size to the given dimension
				newCluster.center.position.resize(dimensionCount);
				// Add the new cluster to the cluster list
				clusters->push_back(newCluster);

				// Set the cluster of the current point to the new cluster
				(*point)->cluster = &clusters->back();
				// Add the point to the cluster
				(*point)->cluster->points.push_back(*point);

				// Go through all points in this cluster and add all points, which have the pointInCluster in their k-nearest points list
				for (auto pointInCluster = (*point)->cluster->points.begin(); pointInCluster != (*point)->cluster->points.end(); pointInCluster++)
					addKNearestPointsToCluster(points, clusters->back(), *(*pointInCluster), nearestPointsCount);
			}
		}

		calculateClusterCentersFromMedians(*clusters, false);

		// Calculate the widths of all calculated clusters
		calculateAllClusterWidths(*clusters.get());
		return clusters;
	}

	bool AbstractNearestClustering::pairCompare(const std::pair<Point*, double>& a, const std::pair<Point*, double>& b)
	{
		return a.second < b.second;
	}
}