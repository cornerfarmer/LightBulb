// Includes
#include "ClusterAnalysis/ROLFNeuronPlacer.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "ClusterAnalysis/Cluster.hpp"
#include "ClusterAnalysis/ROLFClustering.hpp"
#include "Teaching/Teacher.hpp"
#include "ClusterAnalysis/Point.hpp"
#include "ClusterAnalysis/PointSet.hpp"

void ROLFNeuronPlacer::doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher)
{
	// The clusterCount should be the count of RBFNeurons in the given RBFNetwork
	int clusterCount = neuralNetwork.getNeuronCountsPerLayer()[1];
	// Set the dimensionCount to the neuron count in the input layer
	int dimensionCount = neuralNetwork.getInputSize();
	// Calculate all points from the teaching lessons
	std::unique_ptr<PointSet> points = getPointsFromTeachingLessons(teacher, dimensionCount);

	// Create a ROLFClusteringOptions object which contains all standard options used by the clustering algorithm
	ROLFClusteringOptions options;
	// Create a new ROLFClustering object which will do all hard work :)
	ROLFClustering clustering(options);

	// Let the clustering algorithm calculate clusters from our teachingLessons
	std::unique_ptr<std::list<Cluster>> clusters = clustering.doClustering(*points.get(), dimensionCount);

	// Fill up the calculated clusters to reach the right clusterCount
	fillUpClusters(*points.get(), *clusters.get(), clusterCount, dimensionCount);

	// Replace the RBFNeurons from given network with the help of the calculated clusters
	placeRBFNeuronsFromClusters(clusters.get(), neuralNetwork);
}

AbstractRBFNeuronPlacer* ROLFNeuronPlacer::getCopy()
{
	return new ROLFNeuronPlacer(*this);
}