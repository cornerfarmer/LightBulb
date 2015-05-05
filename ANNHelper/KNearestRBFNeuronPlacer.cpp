#include "KNearestRBFNeuronPlacer.hpp"
#include "RBFNetwork.hpp"
#include "Cluster.hpp"
#include "KNearestClustering.hpp"
#include "Teacher.hpp"

void KNearestRBFNeuronPlacer::doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher)
{

	int nearestPointsCount = 3;
	// Create a new KNearestClustering object which will do all hard work :)
	KNearestClustering clustering;

	// Let the clustering algorithm calculate clusters from our teachingLessons
	std::unique_ptr<std::vector<Cluster>> clusters = clustering.doClustering(getPointsFromTeachingLessons(teacher, neuralNetwork.getNeuronsInLayer(0)->size()).get(), nearestPointsCount, neuralNetwork.getNeuronsInLayer(0)->size());

	if (clusters->size() > neuralNetwork.getNeuronsInLayer(1)->size())
	{
		for (int i = clusters->size() - neuralNetwork.getNeuronsInLayer(1)->size(); i > 0; i--)
			clusters->pop_back();
	}
	else if (clusters->size() < neuralNetwork.getNeuronsInLayer(1)->size())
	{
		for (int i = 0; i < neuralNetwork.getNeuronsInLayer(1)->size() - clusters->size(); i++)
			clusters->push_back((*clusters)[i % clusters->size()]);
	}

	// Replace the RBFNeurons from given network with the help of the calculated clusters
	placeRBFNeuronsFromClusters(clusters.get(), neuralNetwork);
}

AbstractRBFNeuronPlacer* KNearestRBFNeuronPlacer::getCopy()
{
	return new KNearestRBFNeuronPlacer(*this);
}