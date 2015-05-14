#include "ROLFClustering.hpp"
#include "Cluster.hpp"
#include "Point.hpp"
#include "RBFNetwork.hpp"
#include "NeuralNetwork.hpp"
#include "Teacher.hpp"
#include "TeachingLessonLinearInput.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "RBFThreshold.hpp"

ROLFClustering::ROLFClustering(ROLFClusteringOptions &options_)
{
	options = options_;
}

std::unique_ptr<std::list<Cluster>> ROLFClustering::doClustering(std::list<Point*> &points, int dimensionCount)
{
	// Create a list which will hold all smaller clusters we will calculate in the first step of our algorithm
	std::unique_ptr<std::list<Cluster>> smallClusters(new std::list<Cluster>());

	// Go through all points
	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
	{
		// Define a variable which should contain the distance to the nearest cluster that contains the current point
		float nearestClusterDistance = 0;
		// A variable which holds the nearest cluster
		Cluster* nearestCluster = NULL;
		// Go through all clusters
		for (std::list<Cluster>::iterator cluster = smallClusters->begin(); cluster != smallClusters->end(); cluster++)
		{
			// Calculate the distance from the current point to the current cluster
			float currentDistance = getDistanceBetweenPoints(**point, cluster->position);
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
			// Set the position of the cluster to the point position
			newCluster.position = **point;
			// Set the radius
			newCluster.radius = 0.5f;
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
				nearestCluster->position.position[i] = nearestCluster->position.position[i] + options.centerLearningRate * ((*point)->position[i] - nearestCluster->position.position[i]);
			}
			// Go thourgh all value dimensions
			for (int i = 0; i < nearestCluster->position.value.size(); i++)
			{
				// Adjust the position: value = value + centerLearningRate * (pointValue - value)
				nearestCluster->position.value[i] = nearestCluster->position.value[i] + options.centerLearningRate * ((*point)->value[i] - nearestCluster->position.value[i]);
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
		newBigCluster.position = currentCluster.position;
		// Insert all points from the small cluster into the new big cluster point list
		newBigCluster.points.insert(newBigCluster.points.end(), currentCluster.points.begin(), currentCluster.points.end());

		// A list which holds all clusters which the new big cluster contains
		std::list<Cluster> clustersFromBigCluster;
		// Add the current small cluster to this list (only position and radius, we will not need the point list any more)
		clustersFromBigCluster.push_back(Cluster(currentCluster.position, currentCluster.radius));

		// Go through all small clusters which are part of the new big cluster
		for (std::list<Cluster>::iterator clusterFromBigCluster = clustersFromBigCluster.begin(); clusterFromBigCluster != clustersFromBigCluster.end(); clusterFromBigCluster++)
		{
			// Go through all left small clusters
			for (std::list<Cluster>::iterator cluster = smallClusters->begin(); cluster != smallClusters->end();)
			{
				// If the current small cluster has at least one point and it intersects with the current clusterFromBigCluster (dist(cluster1, cluster2) < cluster1Radius + cluster2Radius)
				if (!cluster->points.empty() && getDistanceBetweenPoints((*clusterFromBigCluster).position, cluster->position) < ((*clusterFromBigCluster).radius + cluster->radius) * options.widthMultiplier)
				{
					// Extract all points from the current small cluster and put them into the point list of the new big cluster
					newBigCluster.points.insert(newBigCluster.points.end(), (*cluster).points.begin(), (*cluster).points.end());
					// Insert the current small cluster in the list of the current big cluster
					clustersFromBigCluster.push_back(Cluster((*cluster).position, (*cluster).radius));

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

	return bigClusters;
}
