// Includes
#include "ClusterAnalysis/KMeansRBFNeuronPlacer.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "ClusterAnalysis/Cluster.hpp"
#include "ClusterAnalysis/KMeansClustering.hpp"

void KMeansRBFNeuronPlacer::doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher)
{
	// The clusterCount should be the count of RBFNeurons in the given RBFNetwork
	int clusterCount = neuralNetwork.getNeuronCountInLayer(1);
	// Create a new KMeansClustering object which will do all hard work :)
	KMeansClustering clustering;

	// Let the clustering algorithm calculate clusters from our teachingLessons
	std::unique_ptr<std::list<Cluster>> clusters = clustering.doClustering(*getPointsFromTeachingLessons(teacher, neuralNetwork.getNeuronCountInLayer(0)).get(), clusterCount, neuralNetwork.getNeuronCountInLayer(0));

	// Replace the RBFNeurons from given network with the help of the calculated clusters
	placeRBFNeuronsFromClusters(clusters.get(), neuralNetwork);
}

AbstractRBFNeuronPlacer* KMeansRBFNeuronPlacer::getCopy()
{
	return new KMeansRBFNeuronPlacer(*this);
}