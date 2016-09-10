// Includes
#include "ClusterAnalysis/ROLFClustering.hpp"
#include "ClusterAnalysis/Cluster.hpp"
#include "ClusterAnalysis/Point.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/TeachingLessonLinearInput.hpp"
#include "ClusterAnalysis/PointSet.hpp"

namespace LightBulb
{
	ROLFClustering::ROLFClustering(ROLFClusteringOptions &options_)
	{
		options = options_;
	}

	std::unique_ptr<std::list<Cluster>> ROLFClustering::doClustering(PointSet &points, int dimensionCount)
	{
		// Create a list which will hold all smaller clusters we will calculate in the first step of our algorithm
		std::unique_ptr<std::list<Cluster>> smallClusters(new std::list<Cluster>());

		// Go through all points
		for (auto point = points.begin(); point != points.end(); point++)
		{
			// Define a variable which should contain the distance to the nearest cluster that contains the current point
			double nearestClusterDistance = 0;
			// A variable which holds the nearest cluster
			Cluster* nearestCluster = NULL;
			// Go through all clusters
			for (auto cluster = smallClusters->begin(); cluster != smallClusters->end(); cluster++)
			{
				// Calculate the distance from the current point to the current cluster
				double currentDistance = (*point)->valPos.getDistanceBetweenValuePositions(cluster->center, points.getMaxPositionDistance(), points.getMaxValueDistance());
				// If the distance is inside of the cluster radius and the distance is smaller than the current nearest cluster
				if (currentDistance < nearestClusterDistance || (nearestCluster == NULL && currentDistance <= cluster->radius * options.widthMultiplier))
				{
					// Set the nearestCluster to the current cluster
					nearestClusterDistance = currentDistance;
					nearestCluster = &*cluster;
				}
			}

			// If no cluster which contains the current point has been found
			if (nearestCluster == NULL)
			{
				// Create a new Cluster
				Cluster newCluster;
				// Set the center of the cluster to the point position
				newCluster.center = (*point)->valPos;

				// Set the radius
				// If its the first small cluster or useConstantRadius has been selected, set the radius to a constant value
				if (smallClusters->empty() || options.radiusInitMethod == useConstantRadius)
					newCluster.radius = options.contantInitRadius;
				else
				{
					// If the min or max method has been choosen, first set the radius to the radius if the first small cluster (so the radius will be comparable)
					if (options.radiusInitMethod == useMaxRadius || options.radiusInitMethod == useMinRadius)
						newCluster.radius = smallClusters->front().radius;
					else if (options.radiusInitMethod == useMeanRadius) // If we should calculate the mean radius, set the radius to 0
						newCluster.radius = 0;

					for (auto cluster = smallClusters->begin(); cluster != smallClusters->end(); cluster++)
					{
						// If the max or min method is used, choose the max or min of the current new radius and the radius of the current cluster
						if (options.radiusInitMethod == useMaxRadius)
							newCluster.radius = std::max(newCluster.radius, (*cluster).radius);
						else if (options.radiusInitMethod == useMinRadius)
							newCluster.radius = std::min(newCluster.radius, (*cluster).radius);
						else if (options.radiusInitMethod == useMeanRadius) // If we should calculate the mean radius, add every radius to our new radius
							newCluster.radius += (*cluster).radius;
					}

					// If we should calculate the mean radius, we now only have to divide by the smallClusterCount 
					if (options.radiusInitMethod == useMeanRadius)
						newCluster.radius /= smallClusters->size();
				}

				// Add the current point to the cluster
				newCluster.points.push_back(*point);
				// Add the new cluster to the cluster list
				smallClusters->push_back(newCluster);
			}
			else
			{
				// If a nearestCluster has been found, adjust this cluster
				// Go thourgh all position dimensions
				for (int i = 0; i < dimensionCount; i++)
				{
					// Adjust the position: position = position + centerLearningRate * (pointPosition - position)
					nearestCluster->center.position[i] = nearestCluster->center.position[i] + options.centerLearningRate * ((*point)->valPos.position[i] - nearestCluster->center.position[i]);
				}
				// Go thourgh all value dimensions
				for (unsigned int i = 0; i < nearestCluster->center.value.size(); i++)
				{
					// Adjust the position: value = value + centerLearningRate * (pointValue - value)
					nearestCluster->center.value[i] = nearestCluster->center.value[i] + options.centerLearningRate * ((*point)->valPos.value[i] - nearestCluster->center.value[i]);
				}

				// Adjust the radius: radius = radius + widthLearningRate * (distanceClusterPoint - radius)
				nearestCluster->radius = nearestCluster->radius + options.widthLearningRate * (nearestClusterDistance - nearestCluster->radius);
				// Add the point to the cluster
				nearestCluster->points.push_back(*point);
			}
		}

		// Create a new list which will hold all our final (big) clusters. You can also describe them as clusters from (small)clusers ;)
		std::unique_ptr<std::list<Cluster>> bigClusters(new std::list<Cluster>());

		// While there are small clusters
		while (!smallClusters->empty())
		{
			// Extract the first small cluster
			Cluster currentCluster = smallClusters->front();
			// Delete this first small cluster from the list
			smallClusters->pop_front();

			// Create a new big cluster which will contain the current small cluster and all its neighbour clusters
			Cluster newBigCluster;
			// Copy the small cluster position to the new big cluster
			newBigCluster.center = currentCluster.center;
			// Insert all points from the small cluster into the new big cluster point list
			newBigCluster.points.insert(newBigCluster.points.end(), currentCluster.points.begin(), currentCluster.points.end());

			// A list which holds all clusters which the new big cluster contains
			std::list<Cluster> clustersFromBigCluster;
			// Add the current small cluster to this list (only position and radius, we will not need the point list any more)
			clustersFromBigCluster.push_back(Cluster(currentCluster.center, currentCluster.radius));

			// Go through all small clusters which are part of the new big cluster
			for (auto clusterFromBigCluster = clustersFromBigCluster.begin(); clusterFromBigCluster != clustersFromBigCluster.end(); clusterFromBigCluster++)
			{
				// Go through all left small clusters
				for (auto cluster = smallClusters->begin(); cluster != smallClusters->end();)
				{
					// If the current small cluster has at least one point and it intersects with the current clusterFromBigCluster (dist(cluster1, cluster2) < cluster1Radius + cluster2Radius)
					if (!cluster->points.empty() && (*clusterFromBigCluster).center.getDistanceBetweenValuePositions(cluster->center, points.getMaxPositionDistance(), points.getMaxValueDistance()) < ((*clusterFromBigCluster).radius + cluster->radius) * options.widthMultiplier)
					{
						// Extract all points from the current small cluster and put them into the point list of the new big cluster
						newBigCluster.points.insert(newBigCluster.points.end(), (*cluster).points.begin(), (*cluster).points.end());
						// Insert the current small cluster in the list of the current big cluster
						clustersFromBigCluster.push_back(Cluster((*cluster).center, (*cluster).radius));

						// Remove the current small cluster from the smallClusters list
						std::list<Cluster>::iterator clusterToRemove = cluster;
						cluster++;
						smallClusters->erase(clusterToRemove);
					}
					else // Go to the next small cluster
						cluster++;
				}
			}

			// Add the new big cluster to the cluster list
			bigClusters->push_back(newBigCluster);
		}

		// Recalculate all centers of the bigClusters
		calculateClusterCentersFromMedians(*bigClusters.get(), false);

		calculateAllClusterWidths(*bigClusters);

		return bigClusters;
	}
}