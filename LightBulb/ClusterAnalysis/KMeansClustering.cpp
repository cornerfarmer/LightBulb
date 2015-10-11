// Includes
#include "ClusterAnalysis/KMeansClustering.hpp"
#include "ClusterAnalysis/Cluster.hpp"
#include "ClusterAnalysis/Point.hpp"
#include "ClusterAnalysis/PointSet.hpp"

std::unique_ptr<std::list<Cluster>> KMeansClustering::doClustering(PointSet &points, int clusterCount, int dimensionCount)
{
	// Create a new cluster vector
	std::unique_ptr<std::list<Cluster>> clusters(new std::list<Cluster>(clusterCount));
	// Go through all clusters

	for (auto cluster = clusters->begin(); cluster != clusters->end(); cluster++)
	{
		PointSet::iterator point = points.begin();
		std::advance(point, (double)(rand() % RAND_MAX) / RAND_MAX * points.size());
		// Set the position to one random point, so every cluster does now contain at least one point
		(*cluster).center.position = (*point)->valPos.position;
		(*cluster).center.value = (*point)->valPos.value;
	}

	// Create a boolean value that should indicate whether the process can be stopped
	bool clusterHasChanged = true;
	// Do as long as something has changed
	while (clusterHasChanged)
	{
		// Go through every cluster
		int clusterIndex = 0;
		for (auto cluster = clusters->begin(); cluster != clusters->end(); cluster++, clusterIndex++)
		{
			// Clear the points list
			(*cluster).points.clear();
		}

		// Add every point to its nearest cluster
		// Go through every point
		for (auto point = points.begin(); point != points.end(); point++)
		{
			// Be sure the cluster of the point is null
			(*point)->cluster = NULL;
			// Set the current nearest cluster distance to zero
			double nearestClusterDistance = 0;

			for (auto cluster = clusters->begin(); cluster != clusters->end(); cluster++, clusterIndex++)
			{
				// Calculate the distance between the point and the current cluster
				double currentDistance = (*point)->valPos.getDistanceBetweenValuePositions((*cluster).center, points.getMaxPositionDistance(), points.getMaxValueDistance());
				// If the currentDistance is less than the nearestClusterDistance or if this is the first cluster
				if (currentDistance < nearestClusterDistance || (*point)->cluster == NULL)
				{
					(*point)->cluster = &*cluster;
					// Set the nearestClusterDistance to the current distance
					nearestClusterDistance = currentDistance;
				}
			}

			// Increase the point counter of the choosen cluster
			(*point)->cluster->points.push_back((*point));
		}	

		clusterHasChanged = calculateClusterCentersFromMedians(*clusters, true);
	}

	// Calculate the widths of all calculated clusters
	calculateAllClusterWidths(*clusters.get());
	return clusters;
}
