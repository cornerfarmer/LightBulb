#include "KMeansClustering.hpp"
#include "Cluster.hpp"

std::unique_ptr<std::vector<Cluster>> KMeansClustering::doClustering(std::vector<std::vector<float>>* points, int clusterCount, int dimensionCount)
{
	// Create a new cluster vector
	std::unique_ptr<std::vector<Cluster>> clusters(new std::vector<Cluster>(clusterCount));
	// Go through all clusters
	for (int c = 0; c < clusters->size(); c++)
	{
		// Set the position to one random point, so every cluster does now contain at least one point
		(*clusters)[c].position = (*points)[c % points->size()];
		// Set the width to a constant value (TODO: Make this value variable)
		(*clusters)[c].width = 0.5f;
	}

	// Create a boolean value that should indicate whether the process can be stopped
	bool clusterHasChanged = true;
	// This vector will help us to calculate the medians of our clusters
	std::vector<std::vector<float>> clusterMedian(clusterCount, std::vector<float>(dimensionCount));
	// This vector contains informations about which point referrs to which cluster
	std::vector<int> clusterFromPoint(points->size());
	// Do as long as something has changed
	while (clusterHasChanged)
	{
		clusterHasChanged = false;
		// Go through every cluster
		for (int c = 0; c < clusters->size(); c++)
		{
			// Set the point counter to zero
			(*clusters)[c].pointCount = 0;
			// Set all medians to zero
			for (int i = 0; i < dimensionCount; i++)
				clusterMedian[c][i] = 0;
		}

		// Add every point to its nearest cluster
		// Go through every point
		for (int p = 0; p < points->size(); p++)
		{
			// Set the corresponding cluster to -1 (none)
			clusterFromPoint[p] = -1;
			// Set the current nearest cluster distance to zero
			float nearestClusterDistance = 0;
			// Go through all clusters
			for (int c = 0; c < clusters->size(); c++)
			{
				// If the distance between the current point and this cluster is less than the nearestClusterDistance or if this is the first cluster
				if (float currentDistance = getDistanceBetweenPoints((*points)[p], (*clusters)[c].position) < nearestClusterDistance || clusterFromPoint[p] == -1)
				{
					// Set the current cluster to the cluster of the current point
					clusterFromPoint[p] = c;
					// Set the nearestClusterDistance to the current distance
					nearestClusterDistance = currentDistance;
				}
			}
			// Increase the point counter of the choosen cluster
			(*clusters)[clusterFromPoint[p]].pointCount++;
			// Add the position of the point to the median of the choosen cluster
			for (int i = 0; i < dimensionCount; i++)
				clusterMedian[clusterFromPoint[p]][i] += (*points)[p][i];
		}	

		// Calculate new cluster positions from their medians
		// Go through all clusters
		for (int c = 0; c < clusters->size(); c++)
		{
			// Go through all dimensions of the position vector
			for (int i = 0; i < dimensionCount; i++)
			{
				// If the cluster has at least one point
				if ((*clusters)[c].pointCount != 0)
				{
					// Divide the sum of all points from this cluster by the point count, so now we have the median of the cluster
					clusterMedian[c][i] /= (*clusters)[c].pointCount;
					// If the median (new cluster position) is not equal to the old cluster position
					if (clusterMedian[c][i] != (*clusters)[c].position[i])
					{
						// Indicate that we need at least one more iteration
						clusterHasChanged = true;
						// Set the position to the calculated median
						(*clusters)[c].position[i] = clusterMedian[c][i];
					}
				}
			}
		}
	}

	return clusters;
}
