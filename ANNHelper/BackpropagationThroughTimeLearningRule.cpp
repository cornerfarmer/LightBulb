#include "BackpropagationThroughTimeLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "RecurrentNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"


BackpropagationThroughTimeLearningRule::BackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_) 
	: BackpropagationLearningRule(new BackpropagationThroughTimeLearningRuleOptions(options_))
{
	options->offlineLearning = false;
}

NeuralNetwork* BackpropagationThroughTimeLearningRule::initializeNeuralNetwork(NeuralNetwork &neuralNetwork)
{
	originalNeuralNetwork = &neuralNetwork;
	return new NeuralNetwork(dynamic_cast<RecurrentNetwork*>(neuralNetwork.getNetworkTopology())->unfold(getOptions()->maxTimeSteps).release());
}


void BackpropagationThroughTimeLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{	
	BackpropagationLearningRule::initializeLearningAlgoritm(neuralNetwork, teacher);
	deltaWeightSums = std::vector<float>(originalNeuralNetwork->getNetworkTopology()->getEdgeCount(), 0);
}

void BackpropagationThroughTimeLearningRule::adjustWeight(Edge* edge, float gradient)
{
	static int totalEdgeIndex = 0;

	deltaWeightSums[totalEdgeIndex] += calculateDeltaWeight(edge, gradient);

	totalEdgeIndex++;
	totalEdgeIndex %= deltaWeightSums.size();
}

void BackpropagationThroughTimeLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork)
{
	for (std::vector<float>::iterator deltaWeightSum = deltaWeightSums.begin(); deltaWeightSum != deltaWeightSums.end(); deltaWeightSum++)
		*deltaWeightSum = 0;
}

void BackpropagationThroughTimeLearningRule::doCalculationAfterTeachingLesson(NeuralNetwork &neuralNetwork)
{
	int edgeIndex = 0;
	// Go through all layers
	for (int l = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1; l > 0; l--)
	{
		std::vector<AbstractNeuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeuronsInLayer(l);
		// Go through all neurons
		int neuronIndex = 0;
		for (std::vector<AbstractNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++, neuronIndex++)
		{
			if (l == dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1 || neuronIndex + 1 < neuronsInLayer->size() || !dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->usesBiasNeurons()) // If its the last layer or a BiasNeuron
			{
				std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
				// Go through all afferentEdges of the actual neuron
				for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
				{	
					if (deltaWeightSums[edgeIndex] == std::numeric_limits<double>::infinity())
						edgeIndex = edgeIndex;
					(*edge)->setWeight((*edge)->getWeight() + deltaWeightSums[edgeIndex] / getOptions()->maxTimeSteps);
					edgeIndex++;
					edgeIndex %= deltaWeightSums.size();
				}
			}
		}
	}

	edgeIndex = 0;
	for (int l = dynamic_cast<LayeredNetwork*>(originalNeuralNetwork->getNetworkTopology())->getLayerCount() - 1; l > 0; l--)
	{
		std::vector<AbstractNeuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(originalNeuralNetwork->getNetworkTopology())->getNeuronsInLayer(l);
		// Go through all neurons
		int neuronIndex = 0;
		for (std::vector<AbstractNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++, neuronIndex++)
		{
			if (l == dynamic_cast<LayeredNetwork*>(originalNeuralNetwork->getNetworkTopology())->getLayerCount() - 1 || neuronIndex + 1 < neuronsInLayer->size() || !dynamic_cast<LayeredNetwork*>(originalNeuralNetwork->getNetworkTopology())->usesBiasNeurons()) // If its the last layer or a BiasNeuron
			{
				std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
				// Go through all afferentEdges of the actual neuron
				for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
				{	
					(*edge)->setWeight(deltaWeightSums[edgeIndex] / getOptions()->maxTimeSteps);
					edgeIndex++;
				}
			}
		}
	}
}

void BackpropagationThroughTimeLearningRule::doCalculationAfterLearningProcess(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	delete(&neuralNetwork);
}

BackpropagationThroughTimeLearningRuleOptions* BackpropagationThroughTimeLearningRule::getOptions()
{
	return static_cast<BackpropagationThroughTimeLearningRuleOptions*>(options.get());
}

