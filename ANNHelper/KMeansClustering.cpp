#include "KMeansClustering.hpp"
#include "Cluster.hpp"
#include "Point.hpp"

std::unique_ptr<std::list<Cluster>> KMeansClustering::doClustering(std::list<Point*> &points, int clusterCount, int dimensionCount)
{
	// Create a new cluster vector
	std::unique_ptr<std::list<Cluster>> clusters(new std::list<Cluster>(clusterCount));
	// Go through all clusters

	for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++)
	{
		std::list<Point*>::iterator point = points.begin();
		std::advance(point, (float)(rand() % RAND_MAX) / RAND_MAX * points.size());
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
		for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++, clusterIndex++)
		{
			// Clear the points list
			(*cluster).points.clear();
		}

		// Add every point to its nearest cluster
		// Go through every point
		for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
		{
			// Be sure the cluster of the point is null
			(*point)->cluster = NULL;
			// Set the current nearest cluster distance to zero
			float nearestClusterDistance = 0;

			for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++, clusterIndex++)
			{
				// Calculate the distance between the point and the current cluster
				float currentDistance = getDistanceBetweenValuePositions((*point)->valPos, (*cluster).center);
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
