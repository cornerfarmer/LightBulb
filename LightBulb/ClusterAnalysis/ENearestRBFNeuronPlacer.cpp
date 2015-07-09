#include "ClusterAnalysis\ENearestRBFNeuronPlacer.hpp"
#include "NetworkTopology\RBFNetwork.hpp"
#include "ClusterAnalysis\Cluster.hpp"
#include "ClusterAnalysis\ENearestClustering.hpp"
#include "Teaching\Teacher.hpp"
#include "ClusterAnalysis\Point.hpp"
#include "ClusterAnalysis\PointSet.hpp"

// Sets the minimum cluster width
const double ENearestRBFNeuronPlacer::iterationEndPrecision = 0.1f;

void ENearestRBFNeuronPlacer::doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher)
{
		// The clusterCount should be the count of RBFNeurons in the given RBFNetwork
	int clusterCount = neuralNetwork.getNeurons()->front().size();
	// Set the dimensionCount to the neuron count in the first layer
	int dimensionCount = neuralNetwork.getInputNeurons()->size();

	// Create a new KNearestClustering object which will do all hard work :)
	ENearestClustering clustering;
	// Calculate all points from the teaching lessons
	std::unique_ptr<PointSet> points = getPointsFromTeachingLessons(teacher, dimensionCount);

	// Calculate the cache from the given points
	clustering.calculateCache(*points.get());

	// We now have to find the right parameter for the cluster algorightm to get the right count of clusters

	// First we have to set a interval, which will contain the right parameter
	// Set the intervalBegin to 0. This would produce as many clusters as many points we have
	double intervalBegin = 0;
	// Set the intervalEnd to pointCount -1. This would always produce exactly one cluster
	double intervalEnd = clustering.getBiggestDistance(*points.get());
	
	// This pointer will contain the list of clusters
	std::unique_ptr<std::list<Cluster>> clusters;
	do
	{
		// Start the clustering algorithm with the parameter in the middle between intervalEnd and intervalBegin
		clusters = clustering.doClustering(*points.get(), (intervalEnd - intervalBegin) / 2 + intervalBegin, dimensionCount);
		// If count of the calculated clusters equals the wished cluster count, we have found the right parameter and can stop the algorithm
		if (clusters->size() == clusterCount)
			break;
		else 
		{
			// If the count of the calculated clusters is greater than the wished cluster count, we have to increase the parameter
			if (clusters->size() > clusterCount)
			{
				// Set the intervalBegin to the middle between intervalEnd and intervalBegin
				intervalBegin = (intervalEnd - intervalBegin) / 2 + intervalBegin;
			}
			else
			{
				// Set the intervalEnd to the middle between intervalEnd and intervalBegin
				intervalEnd = (intervalEnd - intervalBegin) / 2 + intervalBegin;
			}			
		}
		// Do as long as we have not found the best parameter from the interval
	} while(abs(intervalBegin -intervalEnd) > iterationEndPrecision);
	
	fillUpClusters(*points.get(), *clusters.get(), clusterCount, dimensionCount); 
	// Replace the RBFNeurons from given network with the help of the calculated clusters
	placeRBFNeuronsFromClusters(clusters.get(), neuralNetwork);
}

AbstractRBFNeuronPlacer* ENearestRBFNeuronPlacer::getCopy()
{
	return new ENearestRBFNeuronPlacer(*this);
}