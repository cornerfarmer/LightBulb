// Includes
#include "Learning/BackpropagationThroughTimeLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/RecurrentFeedForwardNetworkTopology.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "NetworkTopology/RecurrentNetworkInterface.hpp"


BackpropagationThroughTimeLearningRule::BackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_) 
	: BackpropagationLearningRule(new BackpropagationThroughTimeLearningRuleOptions(options_))
{

}

NeuralNetwork* BackpropagationThroughTimeLearningRule::initializeNeuralNetwork(NeuralNetwork &neuralNetwork)
{
	// Save the current neural network
	originalNeuralNetwork = &neuralNetwork;

	// Create a new neural network from the unfolded network topology of the original neural network and return it
	return new NeuralNetwork(dynamic_cast<RecurrentNetworkInterface*>(neuralNetwork.getNetworkTopology())->unfold(getOptions()->maxTimeSteps).release());
}

Teacher* BackpropagationThroughTimeLearningRule::initializeTeacher(Teacher &teacher)
{
	// Unfold the teacher and return it
	return teacher.unfold();
}

void BackpropagationThroughTimeLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{	
	BackpropagationLearningRule::initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	// Create the delta weight sums vector in the size of the ORIGINAL network edge count
	deltaWeightSums = std::vector<double>(originalNeuralNetwork->getNetworkTopology()->getEdgeCount(), 0);
}

void BackpropagationThroughTimeLearningRule::adjustWeight(Edge* edge, double gradient)
{
	static int totalEdgeIndex = 0;

	// Add the calculated delta weight to the corresponding edge in the original network
	deltaWeightSums[totalEdgeIndex] += calculateDeltaWeight(edge, gradient);

	totalEdgeIndex++;
	totalEdgeIndex %= deltaWeightSums.size();
}

void BackpropagationThroughTimeLearningRule::initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork)
{
	// Reset all sums to zero
	for (auto deltaWeightSum = deltaWeightSums.begin(); deltaWeightSum != deltaWeightSums.end(); deltaWeightSum++)
		*deltaWeightSum = 0;
}

void BackpropagationThroughTimeLearningRule::doCalculationAfterAllWeightAdjustments(NeuralNetwork &neuralNetwork)
{
	int edgeIndex = 0;
	// Go through all layers
	for (int l = neuralNetwork.getNetworkTopology()->getNeurons()->size() - 1; l >= 0; l--)
	{
		std::vector<StandardNeuron*>* neuronsInLayer = &(*neuralNetwork.getNetworkTopology()->getNeurons())[l];
		// Go through all neurons
		for (auto neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++)
		{
			std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
			// Go through all afferentEdges of the actual neuron
			for (auto edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
			{	
				// Add to the edge weight the corresponding delta weight sum
				(*edge)->setWeight((*edge)->getWeight() + deltaWeightSums[edgeIndex] / getOptions()->maxTimeSteps);			
				edgeIndex++;
				edgeIndex %= deltaWeightSums.size();
			}
		}
	}
}

void BackpropagationThroughTimeLearningRule::doCalculationAfterLearningProcess(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Copy all weights from the unfolded network back into the orignal network
	originalNeuralNetwork->getNetworkTopology()->copyWeightsFrom(*neuralNetwork.getNetworkTopology());
	
	// Delete all temporary unfolded stuff
	delete(&neuralNetwork);
	delete(&teacher);
}

BackpropagationThroughTimeLearningRuleOptions* BackpropagationThroughTimeLearningRule::getOptions()
{
	return static_cast<BackpropagationThroughTimeLearningRuleOptions*>(options.get());
}

void BackpropagationThroughTimeLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights from the original network
		originalNeuralNetwork->getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}

	// If needed, intialize the resilientLearningRateHelper
	if (getOptions()->resilientLearningRate)
		resilientLearningRateHelper->initialize(neuralNetwork);

	// Copy all weights from the original network into the unfolded one
	dynamic_cast<AbstractNetworkTopology*>(neuralNetwork.getNetworkTopology())->copyWeightsFrom(*dynamic_cast<AbstractNetworkTopology*>(originalNeuralNetwork->getNetworkTopology()));	
}