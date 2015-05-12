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

std::unique_ptr<std::list<Cluster>> ROLFClustering::doClustering(std::list<Point*> &points, int clusterCount, int dimensionCount)
{
	RBFNetwork* rbfNetwork = new RBFNetwork(dimensionCount, 1, 1);

	NeuralNetwork neuralNetwork(rbfNetwork);

	ROLFLearningRuleOptions learningRuleOptions;

	Teacher teacher;
	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
	{
		teacher.addTeachingLesson(new TeachingLessonLinearInput(&(*point)->position, &(*point)->value));
	}

	ROLFLearningRule learningRule(learningRuleOptions);
	learningRule.doLearning(neuralNetwork, teacher);
	std::unique_ptr<std::list<Cluster>> clusters(new std::list<Cluster>());

	for (std::vector<AbstractNeuron*>::iterator neuron = rbfNetwork->getNeuronsInLayer(1)->begin(); neuron != rbfNetwork->getNeuronsInLayer(1)->end(); neuron++)
	{
		RBFThreshold& rbfThreshold = static_cast<RBFThreshold&>(*static_cast<StandardNeuron*>(*neuron)->getThreshold());
		Cluster newCluster;
		newCluster.position = *rbfThreshold.getCenterVector();
		newCluster.radius = rbfThreshold.getWidth();
		clusters->push_back(newCluster);
	}



	return clusters;
}
