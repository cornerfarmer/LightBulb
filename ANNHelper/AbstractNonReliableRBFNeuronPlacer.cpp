#include "AbstractNonReliableRBFNeuronPlacer.hpp"
#include "KMeansClustering.hpp"
#include "Cluster.hpp"

void AbstractNonReliableRBFNeuronPlacer::fillUpClusters(std::list<Point*>& points, std::list<Cluster> &clusters, int clusterCount, int dimensionCount)
{	
	// Calculate the count of additional needed clusters
	int neededClustersLeft = clusterCount - clusters.size();

	// If this value is not 0
	if (neededClustersLeft > 0)
	{
		// Create new kMeansclustering object, we will use this algorithm to divide one cluster into many
		KMeansClustering kMeansclustering;		
		// Save the start cluster size
		int originalClusterCount = clusters.size();
		// Go through all original given clusters
		for (int clusterIndex = 0; clusterIndex < originalClusterCount; clusterIndex++)
		{		
			// Calculate how many clusters we should make out of the current one (this has to be at least one, so we will not remove any clusters)
			int subClusterCount = 1;
			// If its the last cluster, set the subClusterCount so we will get all needed clusters, else set the subClusterCount depending on the number of points this cluster contains
			if (clusterIndex == originalClusterCount - 1)
				subClusterCount += clusterCount - clusters.size();
			else
				subClusterCount += neededClustersLeft * clusters.front().points.size() / points.size();

			// Let the clustering algorithm divide the cluster into subclusters
			std::unique_ptr<std::list<Cluster>> newSubClusters = kMeansclustering.doClustering(clusters.front().points, subClusterCount, dimensionCount);

			// Remove the original cluster
			clusters.pop_front();
			// Add all new subclusters to the cluster list
			clusters.insert(clusters.end(), newSubClusters->begin(), newSubClusters->end());
		}
	}
	else if (neededClustersLeft < 0)
	{
		// Create new kMeansclustering object, we will use this algorithm to merge two clusters to one
		KMeansClustering kMeansclustering;	

		for (int i = 0; i < abs(neededClustersLeft); i++)
		{
			float smallestMergedClusterRadius = -1;
			std::list<Cluster>::iterator firstClusterForMerging;
			std::list<Cluster>::iterator secondClusterForMerging;
			for (std::list<Cluster>::iterator firstCluster = clusters.begin(); firstCluster != clusters.end(); firstCluster++)
			{
				for (std::list<Cluster>::iterator secondCluster = firstCluster; secondCluster != clusters.end(); secondCluster++)
				{
					if (secondCluster != firstCluster)
					{
						float mergedClusterRadius = (*firstCluster).center.getDistanceBetweenValuePositions((*secondCluster).center) + (*firstCluster).radius +(*secondCluster).radius;
						if (smallestMergedClusterRadius == -1 || mergedClusterRadius < smallestMergedClusterRadius)
						{
							firstClusterForMerging = firstCluster;
							secondClusterForMerging = secondCluster;
							smallestMergedClusterRadius = mergedClusterRadius;
						}
					}
				}
			}

			firstClusterForMerging->points.insert(firstClusterForMerging->points.end(), secondClusterForMerging->points.begin(), secondClusterForMerging->points.end());
		
			std::unique_ptr<std::list<Cluster>> mergedCluster = kMeansclustering.doClustering(firstClusterForMerging->points, 1, dimensionCount);

			// Remove the original cluster
			clusters.erase(firstClusterForMerging);
			clusters.erase(secondClusterForMerging);

			// Add all new subclusters to the cluster list
			clusters.push_back(mergedCluster->front());
		}
	}
}