#include "DeltaLearningRule.hpp"
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

DeltaLearningRule::DeltaLearningRule(AbstractLearningRuleOptions &options_)
	: AbstractLearningRule(*new AbstractLearningRuleOptions(options_)) 
{

}

void DeltaLearningRule::adjustWeight(Edge* edge, float deltaWeight)
{
	// Just add the weight
	edge->setWeight(edge->getWeight() + deltaWeight);
}

bool DeltaLearningRule::learningHasStopped()
{
	return false;
}

void DeltaLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Check if all given parameters are correct
	if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	if (!dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology()) && dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() != 2)
		throw std::invalid_argument("The given neuralNetwork has to contain exactly two layers");
}

AbstractActivationOrder* DeltaLearningRule::getNewActivationOrder()
{
	return new TopologicalOrder();
}

float DeltaLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector)
{
	if (layerIndex == layerCount - 1)
	{
		// Use the delta rule: deltaWeight = learningRate * Output(prevNeuron) * errorValue
		return 0.5f * edge->getPrevNeuron()->getActivation() * (*errorvector)[neuronIndex];			
	}
	else
		return 0;
}
