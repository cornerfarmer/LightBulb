#include "ResilientBackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

ResilientBackpropagationLearningRule::ResilientBackpropagationLearningRule(ResilientBackpropagationLearningRuleOptions &options_) 
	: AbstractBackpropagationLearningRule(new ResilientBackpropagationLearningRuleOptions(options_))
{
	resilientLearningRateHelper.reset(new ResilientLearningRateHelper(getOptions()));
}

void ResilientBackpropagationLearningRule::initializeBackpropagationLearningAlgorithm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	resilientLearningRateHelper->initialize(neuralNetwork);
}

void ResilientBackpropagationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	// Add the learningRate and the weight decay term to the weight
	edge->setWeight(edge->getWeight() + resilientLearningRateHelper->getNextLearningRate(gradient)  - getOptions()->weightDecayFac * edge->getWeight());		
}

void ResilientBackpropagationLearningRule::printDebugOutput()
{
	resilientLearningRateHelper->printDebugOutput();
}

bool ResilientBackpropagationLearningRule::learningHasStopped()
{
	return resilientLearningRateHelper->learningHasStopped();
}

ResilientBackpropagationLearningRuleOptions* ResilientBackpropagationLearningRule::getOptions()
{
	return static_cast<ResilientBackpropagationLearningRuleOptions*>(options.get());
}