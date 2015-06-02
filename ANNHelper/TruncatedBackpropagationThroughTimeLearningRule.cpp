#include "TruncatedBackpropagationThroughTimeLearningRule.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "Edge.hpp"
#include "AbstractActivationOrder.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"


TruncatedBackpropagationThroughTimeLearningRule::TruncatedBackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_) 
	: BackpropagationLearningRule(new BackpropagationThroughTimeLearningRuleOptions(options_))
{

}

void TruncatedBackpropagationThroughTimeLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{	
	BackpropagationLearningRule::initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	outputValuesInTime.clear();
	outputValuesInTime.resize(getOptions()->maxTimeSteps);
	netInputValuesInTime.clear();
	netInputValuesInTime.resize(getOptions()->maxTimeSteps);
	sameTimestepEdges = activationOrder.getSameTimestepEdges(*neuralNetwork.getNetworkTopology());

	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			deltaVectorOutputLayer[*neuron] = std::vector<std::pair<float, bool>>(getOptions()->maxTimeSteps);
		}
	}
}

float TruncatedBackpropagationThroughTimeLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::map<StandardNeuron*, float>* errormap)
{
	// Calculate the gradient
	// gradient = - Output(prevNeuron) * deltaValue
	float gradient = 0;
	
	for (int t = 0; t < getOptions()->maxTimeSteps; t++)
	{
		if (t > 0 || (*sameTimestepEdges)[edge])
			gradient += -1 * outputValuesInTime[(*sameTimestepEdges)[edge] ? t : t - 1][edge->getPrevNeuron()] * deltaVectorOutputLayer[edge->getNextNeuron()][t].first;
	}

	return gradient / getOptions()->maxTimeSteps;
}

void TruncatedBackpropagationThroughTimeLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::map<StandardNeuron*, float>* errormap)
{
	for (int t = 0; t < getOptions()->maxTimeSteps; t++)
	{
		getDeltaVectorOfNeuronInTime(neuron, t, errormap);
	}
}

float TruncatedBackpropagationThroughTimeLearningRule::getDeltaVectorOfNeuronInTime(StandardNeuron* neuron, int time, std::map<StandardNeuron*, float>* errormap)
{
	if (deltaVectorOutputLayer[neuron][time].second == false)
	{
		std::list<Edge*>* efferentEdges = neuron->getEfferentEdges();

		float errorfac = 0;
		if (errormap->count(neuron) > 0 && time == getOptions()->maxTimeSteps - 1)
			errorfac = (*errormap)[neuron];
		
		for (std::list<Edge*>::iterator efferentEdge = efferentEdges->begin(); efferentEdge != efferentEdges->end(); efferentEdge++)
		{
			if (time < getOptions()->maxTimeSteps - 1 || (*sameTimestepEdges)[*efferentEdge])
				errorfac += getDeltaVectorOfNeuronInTime((*efferentEdge)->getNextNeuron(), (*sameTimestepEdges)[*efferentEdge] ? time : time + 1, errormap) * (*efferentEdge)->getWeight();
		}

		deltaVectorOutputLayer[neuron][time].first = (neuron->executeDerivationOnActivationFunction(netInputValuesInTime[time][neuron]) + getOptions()->flatSpotEliminationFac) * errorfac;			
		deltaVectorOutputLayer[neuron][time].second = true;
	}
	return deltaVectorOutputLayer[neuron][time].first;
}

BackpropagationThroughTimeLearningRuleOptions* TruncatedBackpropagationThroughTimeLearningRule::getOptions()
{
	return static_cast<BackpropagationThroughTimeLearningRuleOptions*>(options.get());
}

std::vector<std::map<AbstractNeuron*, float>>* TruncatedBackpropagationThroughTimeLearningRule::getOutputValuesInTime()
{
	return &outputValuesInTime;
}

std::vector<std::map<AbstractNeuron*, float>>* TruncatedBackpropagationThroughTimeLearningRule::getNetInputValuesInTime()
{
	return &netInputValuesInTime;
}

void TruncatedBackpropagationThroughTimeLearningRule::initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork)
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			for (int t = 0; t < getOptions()->maxTimeSteps; t++) 
				deltaVectorOutputLayer[*neuron][t].second = false;
		}
	}
}