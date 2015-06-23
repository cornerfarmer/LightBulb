#include "ResilientDeltaLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "LayeredNetwork.hpp"
#include "RBFNetwork.hpp"

ResilientDeltaLearningRule::ResilientDeltaLearningRule(ResilientDeltaLearningRuleOptions &options_) 
	: AbstractDeltaLearningRule(new ResilientDeltaLearningRuleOptions(options_))
{
	resilientLearningRateHelper.reset(new ResilientLearningRateHelper(getOptions()));
}

void ResilientDeltaLearningRule::initializeDeltaLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	resilientLearningRateHelper->initialize(neuralNetwork);
}

void ResilientDeltaLearningRule::adjustWeight(Edge* edge, float gradient)
{
	// Add the learningRate and the weight decay term to the weight
	edge->setWeight(edge->getWeight() + resilientLearningRateHelper->getLearningRate(edge, gradient));		
}

void ResilientDeltaLearningRule::printDebugOutput()
{
	resilientLearningRateHelper->printDebugOutput();
}

bool ResilientDeltaLearningRule::learningHasStopped()
{
	return resilientLearningRateHelper->learningHasStopped();
}

ResilientDeltaLearningRuleOptions* ResilientDeltaLearningRule::getOptions()
{
	return static_cast<ResilientDeltaLearningRuleOptions*>(options.get());
}
