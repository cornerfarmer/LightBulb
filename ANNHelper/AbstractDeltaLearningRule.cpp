#include "AbstractDeltaLearningRule.hpp"
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


AbstractDeltaLearningRule::AbstractDeltaLearningRule(AbstractLearningRuleOptions *options_)
	: AbstractLearningRule(options_) 
{

}

void AbstractDeltaLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Check if all given parameters are correct
	if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	if (!dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology()) && dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() != 2)
		throw std::invalid_argument("The given neuralNetwork has to contain exactly two layers");

	initializeDeltaLearningAlgoritm(neuralNetwork, teacher);
}

AbstractActivationOrder* AbstractDeltaLearningRule::getNewActivationOrder()
{
	return new TopologicalOrder();
}

float AbstractDeltaLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector)
{
	if (layerIndex == layerCount - 1)
	{
		// Use the delta rule: deltaWeight = learningRate * Output(prevNeuron) * errorValue
		return -edge->getPrevNeuron()->getActivation() * (*errorvector)[neuronIndex];	
	}
	else
		return 0;
}

void AbstractDeltaLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Randomize all weights
	neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	if (dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology()))
		dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology())->randomizeCenters(0, 1);
}
