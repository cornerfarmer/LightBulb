#include "ROLFClustering.hpp"
#include "Cluster.hpp"
#include "Point.hpp"
#include "RBFNetwork.hpp"
#include "NeuralNetwork.hpp"
#include "ROLFLearningRule.hpp"
#include "Teacher.hpp"
#include "TeachingLessonLinearInput.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "RBFThreshold.hpp"

ROLFClustering::ROLFClustering(ROLFClusteringOptions &options_)
{
	options = options_;
}

std::unique_ptr<std::list<Cluster>> ROLFClustering::doClustering(std::list<Point*> &points, int clusterCount, int dimensionCount)
{
	std::unique_ptr<std::list<Cluster>> smallClusters(new std::list<Cluster>());


	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
	{
		float nearestClusterDistance = 0;
		Cluster* nearestCluster = NULL;
		for (std::list<Cluster>::iterator cluster = smallClusters->begin(); cluster != smallClusters->end(); cluster++)
		{
			float currentDistance = getDistanceBetweenPoints(**point, cluster->position);
			if (currentDistance < nearestClusterDistance || (nearestCluster == NULL && currentDistance <= cluster->radius * options.widthMultiplier))			
			{
				nearestClusterDistance = currentDistance;
				nearestCluster = &*cluster;			
			}
		}

		if (nearestCluster == NULL)
		{
			Cluster newCluster;
			newCluster.position = **point;
			newCluster.radius = 0.5f;
			newCluster.points.push_back(*point);

			smallClusters->push_back(newCluster);
		}
		else
		{
			for (int i = 0; i < dimensionCount; i++)
			{
				nearestCluster->position.position[i] = nearestCluster->position.position[i] + options.centerLearningRate * ((*point)->position[i] - nearestCluster->position.position[i]);
			}
			for (int i = 0; i < nearestCluster->position.value.size(); i++)
			{
				nearestCluster->position.value[i] = nearestCluster->position.value[i] + options.centerLearningRate * ((*point)->value[i] - nearestCluster->position.value[i]);
			}

			nearestCluster->radius = nearestCluster->radius + options.widthLearningRate * (nearestClusterDistance - nearestCluster->radius);
			nearestCluster->points.push_back(*point);
		}
	}

	std::unique_ptr<std::list<Cluster>> bigClusters(new std::list<Cluster>());

	while (!smallClusters->empty())
	{	
		Cluster currentCluster = smallClusters->front();
		smallClusters->pop_front();

		Cluster newBigCluster;
		newBigCluster.position = currentCluster.position;
		newBigCluster.points.insert(newBigCluster.points.end(), currentCluster.points.begin(), currentCluster.points.end());

		std::list<Cluster> clustersFromBigCluster;
		clustersFromBigCluster.push_back(Cluster(currentCluster.position, currentCluster.radius));

		for (std::list<Cluster>::iterator clusterFromBigCluster = clustersFromBigCluster.begin(); clusterFromBigCluster != clustersFromBigCluster.end(); clusterFromBigCluster++)
		{
			for (std::list<Cluster>::iterator cluster = smallClusters->begin(); cluster != smallClusters->end();)
			{
				if (!currentCluster.points.empty() && getDistanceBetweenPoints((*clusterFromBigCluster).position, cluster->position) < ((*clusterFromBigCluster).radius + cluster->radius) * options.widthMultiplier)
				{
					newBigCluster.points.insert(newBigCluster.points.end(), (*cluster).points.begin(), (*cluster).points.end());
					clustersFromBigCluster.push_back(Cluster((*cluster).position, (*cluster).radius));

					std::list<Cluster>::iterator clusterToRemove = cluster;
					cluster++;
					smallClusters->erase(clusterToRemove);
				}
				else
					cluster++;
			}
		}

		bigClusters->push_back(newBigCluster);
	}
	
	calculateClusterCentersFromMedians(*bigClusters.get(), false);

	return bigClusters;
}
