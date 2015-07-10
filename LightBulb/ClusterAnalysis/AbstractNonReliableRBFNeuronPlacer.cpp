#include "ClusterAnalysis\AbstractNonReliableRBFNeuronPlacer.hpp"
#include "ClusterAnalysis\KMeansClustering.hpp"
#include "ClusterAnalysis\Cluster.hpp"
#include "ClusterAnalysis\PointSet.hpp"

void AbstractNonReliableRBFNeuronPlacer::fillUpClusters(PointSet &points, std::list<Cluster> &clusters, int clusterCount, int dimensionCount)
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

			// Make sure the max distances are calculated
			clusters.front().points.refreshMaxDistances();

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

		// Do n-th times (n = neededClustersLeft)
		for (int i = 0; i < abs(neededClustersLeft); i++)
		{
			// Create a variable which should hold the radius of current smallest merged cluster
			double smallestMergedClusterRadius = -1;
			// The first cluster for merging
			std::list<Cluster>::iterator firstClusterForMerging;
			// The second cluster for merging
			std::list<Cluster>::iterator secondClusterForMerging;
			// Go through all clusters
			for (auto firstCluster = clusters.begin(); firstCluster != clusters.end(); firstCluster++)
			{
				// Go through all other clusters
				for (auto secondCluster = firstCluster; secondCluster != clusters.end(); secondCluster++)
				{
					if (secondCluster != firstCluster)
					{
						// Compute the distance between the two centers and treat it like the mergedClusterRadius (sure its just a approximation ;) )
						double mergedClusterRadius  = (*firstCluster).center.getDistanceBetweenValuePositions((*secondCluster).center, points.getMaxPositionDistance(), points.getMaxValueDistance());
						// If there is no current smallestMergedClusterRadius or the clusterCentersDistance is smaller
						if (smallestMergedClusterRadius == -1 || mergedClusterRadius  < smallestMergedClusterRadius)
						{
							// Set the current merging situation as the current best one
							firstClusterForMerging = firstCluster;
							secondClusterForMerging = secondCluster;
							smallestMergedClusterRadius = mergedClusterRadius;
						}
					}
				}
			}

			// Insert all points from the second cluster for merging into the first one
			firstClusterForMerging->points.insert(firstClusterForMerging->points.end(), secondClusterForMerging->points.begin(), secondClusterForMerging->points.end());
		
			// Make sure the max distances are calculated
			firstClusterForMerging->points.refreshMaxDistances();

			// Let the k-means clustering algorithm calculate a new cluster based on the points from the two choosen clusters for merging
			std::unique_ptr<std::list<Cluster>> mergedCluster = kMeansclustering.doClustering(firstClusterForMerging->points, 1, dimensionCount);

			// Remove the original clusters
			clusters.erase(firstClusterForMerging);
			clusters.erase(secondClusterForMerging);

			// Add all the merged cluster to the cluster list
			clusters.push_back(mergedCluster->front());
		}
	}
}