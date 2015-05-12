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
	// Create a new KMeansClustering object which will do all hard work :)
	ROLFClustering clustering;

	// Let the clustering algorithm calculate clusters from our teachingLessons
	std::unique_ptr<std::list<Cluster>> clusters = clustering.doClustering(*getPointsFromTeachingLessons(teacher, neuralNetwork.getNeuronsInLayer(0)->size()).get(), clusterCount, neuralNetwork.getNeuronsInLayer(0)->size());

	// Replace the RBFNeurons from given network with the help of the calculated clusters
	placeRBFNeuronsFromClusters(clusters.get(), neuralNetwork);
}

AbstractRBFNeuronPlacer* ROLFNeuronPlacer::getCopy()
{
	return new ROLFNeuronPlacer(*this);
}