#include "CascadeCorrelationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

CascadeCorrelationLearningRule::CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_) 
	: AbstractLearningRule(new CascadeCorrelationLearningRuleOptions(options_))
{
	// Create a new ResilientLearningRateHelper
	backpropagationLearningRule.reset(new BackpropagationLearningRule(&getOptions()->backpropagationLearningRuleOptions));
}


void CascadeCorrelationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	backpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
}


float CascadeCorrelationLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	return backpropagationLearningRule->calculateDeltaWeightFromEdge(edge, lessonIndex, layerIndex, neuronIndex, edgeIndex, layerCount, neuronsInLayerCount, errormap);
}

void CascadeCorrelationLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	backpropagationLearningRule->initializeNeuronWeightCalculation(neuron, lessonIndex, layerIndex, neuronIndex, layerCount, neuronsInLayerCount, errormap);
}


AbstractActivationOrder* CascadeCorrelationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void CascadeCorrelationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	backpropagationLearningRule->adjustWeight(edge, gradient);
}

void CascadeCorrelationLearningRule::printDebugOutput()
{
	backpropagationLearningRule->printDebugOutput();
}

bool CascadeCorrelationLearningRule::learningHasStopped()
{
	return backpropagationLearningRule->learningHasStopped();
}

CascadeCorrelationLearningRuleOptions* CascadeCorrelationLearningRule::getOptions()
{
	return static_cast<CascadeCorrelationLearningRuleOptions*>(options.get());
}

void CascadeCorrelationLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	backpropagationLearningRule->initializeTry(neuralNetwork, teacher);
}