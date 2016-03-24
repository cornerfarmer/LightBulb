// Includes
#include "Teaching/AbstractTrainingPlan.hpp"
#include <thread>

void AbstractTrainingPlan::start(AbstractNeuralNetwork* network_)
{
	network = network_;
	thread = std::thread(&AbstractTrainingPlan::run, this);
}

AbstractNeuralNetwork* AbstractTrainingPlan::getNeuralNetwork()
{
	return network;
}

std::string AbstractTrainingPlan::getState()
{
	return "running";
}

AbstractTrainingPlan* AbstractTrainingPlan::getCopyForExecute()
{
	AbstractTrainingPlan* copy = getCopy();
	copy->pattern = this;
	return copy;
}

AbstractTrainingPlan* AbstractTrainingPlan::getTrainingPlanPattern()
{
	return pattern;
}
