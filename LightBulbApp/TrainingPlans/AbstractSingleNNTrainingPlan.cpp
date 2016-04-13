// Includes
#include "TrainingPlans/AbstractSingleNNTrainingPlan.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>


void AbstractSingleNNTrainingPlan::fillDefaultLearningRuleOptions(AbstractSupervisedLearningRuleOptions* options)
{
	AbstractLearningRuleTrainingPlan::fillDefaultLearningRuleOptions(options);
	options->neuralNetwork = network;
}

void AbstractSingleNNTrainingPlan::initializeStart()
{
	if (network == NULL)
		network = createNeuralNetwork();
	network->setState(NN_STATE_TRAINED);
}

AbstractNeuralNetwork* AbstractSingleNNTrainingPlan::getNeuralNetwork()
{
	return network;
}

void AbstractSingleNNTrainingPlan::setNeuralNetwork(AbstractNeuralNetwork* network_)
{
	network = network_;
}
