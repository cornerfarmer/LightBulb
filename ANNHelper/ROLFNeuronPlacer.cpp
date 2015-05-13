#include "ROLFNeuronPlacer.hpp"
#include "RBFNetwork.hpp"
#include "Cluster.hpp"
#include "ROLFClustering.hpp"
#include "Teacher.hpp"
#include "Point.hpp"

void ROLFNeuronPlacer::doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher)
{
	// The clusterCount should be the count of RBFNeurons in the given RBFNetwork
	int clusterCount = neuralNetwork.getNeuronsInLayer(1)->size();
	// Set the dimensionCount to the neuron count in the first layer
	int dimensionCount = neuralNetwork.getNeuronsInLayer(0)->size();
	// Calculate all points from the teaching lessons
	std::unique_ptr<std::list<Point*>> points = getPointsFromTeachingLessons(teacher, neuralNetwork.getNeuronsInLayer(0)->size());

	ROLFClusteringOptions options;
	// Create a new KMeansClustering object which will do all hard work :)
	ROLFClustering clustering(options);

	// Let the clustering algorithm calculate clusters from our teachingLessons
	std::unique_ptr<std::list<Cluster>> clusters = clustering.doClustering(*points.get(), clusterCount, dimensionCount);

	fillUpClusters(*points.get(), *clusters.get(), clusterCount, dimensionCount);

	// Replace the RBFNeurons from given network with the help of the calculated clusters
	placeRBFNeuronsFromClusters(clusters.get(), neuralNetwork);
}

AbstractRBFNeuronPlacer* ROLFNeuronPlacer::getCopy()
{
	return new ROLFNeuronPlacer(*this);
}