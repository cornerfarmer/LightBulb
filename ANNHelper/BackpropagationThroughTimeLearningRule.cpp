#include "BackpropagationThroughTimeLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "RecurrentLayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"


BackpropagationThroughTimeLearningRule::BackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_) 
	: BackpropagationLearningRule(new BackpropagationThroughTimeLearningRuleOptions(options_))
{

}

NeuralNetwork* BackpropagationThroughTimeLearningRule::initializeNeuralNetwork(NeuralNetwork &neuralNetwork)
{
	originalNeuralNetwork = &neuralNetwork;
	return new NeuralNetwork(dynamic_cast<RecurrentLayeredNetwork*>(neuralNetwork.getNetworkTopology())->unfold(getOptions()->maxTimeSteps).release());
}

Teacher* BackpropagationThroughTimeLearningRule::initializeTeacher(Teacher &teacher)
{
	return teacher.unfold().release();
}

void BackpropagationThroughTimeLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{	
	BackpropagationLearningRule::initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	deltaWeightSums = std::vector<float>(originalNeuralNetwork->getNetworkTopology()->getEdgeCount(), 0);
}

void BackpropagationThroughTimeLearningRule::adjustWeight(Edge* edge, float gradient)
{
	static int totalEdgeIndex = 0;

	deltaWeightSums[totalEdgeIndex] += calculateDeltaWeight(edge, gradient);

	totalEdgeIndex++;
	totalEdgeIndex %= deltaWeightSums.size();
}

void BackpropagationThroughTimeLearningRule::initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork)
{
	for (std::vector<float>::iterator deltaWeightSum = deltaWeightSums.begin(); deltaWeightSum != deltaWeightSums.end(); deltaWeightSum++)
		*deltaWeightSum = 0;
}

void BackpropagationThroughTimeLearningRule::doCalculationAfterAllWeightAdjustments(NeuralNetwork &neuralNetwork)
{
	int edgeIndex = 0;
	// Go through all layers
	for (int l = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1; l > 0; l--)
	{
		std::vector<AbstractNeuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeuronsInLayer(l);
		// Go through all neurons
		for (std::vector<AbstractNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++)
		{
			std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
			// Go through all afferentEdges of the actual neuron
			for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
			{	
				(*edge)->setWeight((*edge)->getWeight() + deltaWeightSums[edgeIndex] / getOptions()->maxTimeSteps);			
				edgeIndex++;
				edgeIndex %= deltaWeightSums.size();
			}
		}
	}
}

void BackpropagationThroughTimeLearningRule::doCalculationAfterLearningProcess(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	dynamic_cast<LayeredNetwork*>(originalNeuralNetwork->getNetworkTopology())->copyWeightsFrom(*dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()));
	
	delete(&neuralNetwork);
	delete(&teacher);
}

BackpropagationThroughTimeLearningRuleOptions* BackpropagationThroughTimeLearningRule::getOptions()
{
	return static_cast<BackpropagationThroughTimeLearningRuleOptions*>(options.get());
}

void BackpropagationThroughTimeLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		originalNeuralNetwork->getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}

	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->initialize(neuralNetwork);

	dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->copyWeightsFrom(*dynamic_cast<LayeredNetwork*>(originalNeuralNetwork->getNetworkTopology()));	
}