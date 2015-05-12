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
		(*cluster).position = (*point)->position;
	}

	// Create a boolean value that should indicate whether the process can be stopped
	bool clusterHasChanged = true;
	// This vector will help us to calculate the medians of our clusters
	std::vector<std::vector<float>> clusterMedian(clusterCount, std::vector<float>(dimensionCount));
	// Do as long as something has changed
	while (clusterHasChanged)
	{
		clusterHasChanged = false;
		// Go through every cluster
		int clusterIndex = 0;
		for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++, clusterIndex++)
		{
			// Clear the points list
			(*cluster).points.clear();
			// Set all medians to zero
			for (int i = 0; i < dimensionCount; i++)
				clusterMedian[clusterIndex][i] = 0;
		}

		// Add every point to its nearest cluster
		// Go through every point
		for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
		{
			// Be sure the cluster of the point is null
			(*point)->cluster = NULL;
			// Set the current nearest cluster distance to zero
			float nearestClusterDistance = 0;
			// The nearestClusterIndex contains the index of the current nearest cluster
			int nearestClusterIndex;

			// Go through all clusters
			clusterIndex = 0;
			for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++, clusterIndex++)
			{
				// Calculate the distance between the point and the current cluster
				float currentDistance = getDistanceBetweenPositions((*point)->position, (*cluster).position);
				// If the currentDistance is less than the nearestClusterDistance or if this is the first cluster
				if (currentDistance < nearestClusterDistance || (*point)->cluster == NULL)
				{
					// Set the current cluster to the cluster of the current point					
					nearestClusterIndex = clusterIndex;
					(*point)->cluster = &*cluster;
					// Set the nearestClusterDistance to the current distance
					nearestClusterDistance = currentDistance;
				}
			}

			// Increase the point counter of the choosen cluster
			(*point)->cluster->points.push_back((*point));
			// Add the position of the point to the median of the choosen cluster
			for (int i = 0; i < dimensionCount; i++)
				clusterMedian[nearestClusterIndex][i] += (*point)->position[i];
		}	

		// Calculate new cluster positions from their medians
		// Go through all clusters
		clusterIndex = 0;
		for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++, clusterIndex++)
		{
			// Go through all dimensions of the position vector
			for (int i = 0; i < dimensionCount; i++)
			{
				// If the cluster has at least one point
				if ((*cluster).points.size() != 0)
				{
					// Divide the sum of all points from this cluster by the point count, so now we have the median of the cluster
					clusterMedian[clusterIndex][i] /= (*cluster).points.size();
					// If the median (new cluster position) is not equal to the old cluster position
					if (clusterMedian[clusterIndex][i] != (*cluster).position[i])
					{
						// Indicate that we need at least one more iteration
						clusterHasChanged = true;
						// Set the position to the calculated median
						(*cluster).position[i] = clusterMedian[clusterIndex][i];
					}
				}
			}
		}
	}

	// Calculate the widths of all calculated clusters
	calculateAllClusterWidths(*clusters.get());
	return clusters;
}
