#include "KNearestRBFNeuronPlacer.hpp"
#include "RBFNetwork.hpp"
#include "Cluster.hpp"
#include "KNearestClustering.hpp"
#include "Teacher.hpp"
#include <list>
#include "Point.hpp"

void KNearestRBFNeuronPlacer::doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher)
{
	// Create a new KNearestClustering object which will do all hard work :)
	KNearestClustering clustering;
	// Calculate all points from the teaching lessons
	std::unique_ptr<std::list<Point*>> points = getPointsFromTeachingLessons(teacher, neuralNetwork.getNeuronsInLayer(0)->size());
	// The clusterCount should be the count of RBFNeurons in the given RBFNetwork
	int clusterCount = neuralNetwork.getNeuronsInLayer(1)->size();
	// Set the dimensionCount to the neuron count in the first layer
	int dimensionCount = neuralNetwork.getNeuronsInLayer(0)->size();

	// Calculate the cache from the given points
	clustering.calculateCache(*points.get());

	// We now have to find the right parameter for the cluster algorightm to get the right count of clusters

	// First we have to set a interval, which will contain the right parameter
	// Set the intervalBegin to 0. This would produce as many clusters as many points we have
	int intervalBegin = 0;
	// Set the intervalEnd to pointCount -1. This would always produce exactly one cluster
	int intervalEnd = points->size() - 1;
	
	// This pointer will contain the list of clusters
	std::unique_ptr<std::list<Cluster>> clusters;
	do
	{
		// Start the clustering algorithm with the parameter in the middle between intervalEnd and intervalBegin
		clusters= clustering.doClustering(*points.get(), (intervalEnd - intervalBegin) / 2 + intervalBegin, dimensionCount);
		// If count of the calculated clusters equals the wished cluster count, we have found the right parameter and can stop the algorithm
		if (clusters->size() == clusterCount)
			break;
		else 
		{
			// If the count of the calculated clusters is greater than the wished cluster count, we have to increase the parameter
			if (clusters->size() > clusterCount)
			{
				// If the interval has the length 1, the normal calculation wouldn't change anything and would produce a endless loop
				if (intervalEnd - intervalBegin == 1)
				{
					// So increase both interval ends, so after the next calculation the interval calculation will take the other way. 
					intervalBegin++;
					intervalEnd++;
				}
				else // Set the intervalBegin to the middle between intervalEnd and intervalBegin
					intervalBegin = (intervalEnd - intervalBegin) / 2 + intervalBegin;
			}
			else
			{
				 // Set the intervalEnd to the middle between intervalEnd and intervalBegin
				intervalEnd = (intervalEnd - intervalBegin) / 2 + intervalBegin;
			}			
		}
		// Do as long as we have not found the best parameter from the interval
	} while(intervalBegin != intervalEnd);
	
	fillUpClusters(*points.get(), *clusters.get(), clusterCount, dimensionCount); 
	// Replace the RBFNeurons from given network with the help of the calculated clusters
	placeRBFNeuronsFromClusters(clusters.get(), neuralNetwork);
}

AbstractRBFNeuronPlacer* KNearestRBFNeuronPlacer::getCopy()
{
	return new KNearestRBFNeuronPlacer(*this);
}