// Includes
#include "Learning/SingleLayerPerceptronLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Function/BinaryFunction.hpp"

SingleLayerPerceptronLearningRule::SingleLayerPerceptronLearningRule(AbstractLearningRuleOptions &options_)
	: AbstractLearningRule(new AbstractLearningRuleOptions(options_)) 
{

}

void SingleLayerPerceptronLearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	// Just add the weight
	edge->setWeight(edge->getWeight() + deltaWeight);
}

bool SingleLayerPerceptronLearningRule::learningHasStopped()
{
	return false;
}

void SingleLayerPerceptronLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// Check if all given parameters are correct
	if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	if (dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() != 2)
		throw std::invalid_argument("The given neuralNetwork has to contain exactly two layers");
	if (!dynamic_cast<BinaryFunction*>(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction()))
		throw std::invalid_argument("All outputNeurons have to use binary activationFunctions");
}

AbstractActivationOrder* SingleLayerPerceptronLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

double SingleLayerPerceptronLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errorVector)
{
	// If the errorValue is positive add the activation to the weight, else substract the activation from the weight
	if ((*errorVector)[0][edge->getNextNeuron()] > 0)
		return edge->getPrevNeuron()->getActivation();
	else if ((*errorVector)[0][edge->getNextNeuron()] < 0)
		return -edge->getPrevNeuron()->getActivation();
	else
		return 0;
}

void SingleLayerPerceptronLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}
}