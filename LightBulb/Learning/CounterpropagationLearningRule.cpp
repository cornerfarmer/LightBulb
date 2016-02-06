// Includes
#include "Learning/CounterpropagationLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "Neuron/RBFThreshold.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "NetworkTopology/CounterpropagationNetwork.hpp"


CounterpropagationLearningRule::CounterpropagationLearningRule(CounterpropagationLearningRuleOptions &options_)
	: AbstractLearningRule(new CounterpropagationLearningRuleOptions(options_)) 
{	

}

void CounterpropagationLearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	// Set the calculated weight as new weight
	edge->setWeight(edge->getWeight() + deltaWeight);
}

void CounterpropagationLearningRule::printDebugOutput()
{

}

bool CounterpropagationLearningRule::learningHasStopped()
{
	return false;
}

void CounterpropagationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Divide neurons into classes
		static_cast<CounterpropagationNetwork*>(neuralNetwork.getNetworkTopology())->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
		// Place them on random teaching lessons
		static_cast<CounterpropagationNetwork*>(neuralNetwork.getNetworkTopology())->placeCodebookVectorsOnTeachingLessons(teacher);		
	}
}

void CounterpropagationLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	mode = 0;
}

void CounterpropagationLearningRule::initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// Switch to the second mode depending on the current iteration
	if (iteration >= getOptions()->iterationsToChangeMode)
		mode = 1;
}

AbstractActivationOrder* CounterpropagationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

double CounterpropagationLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	if (mode == 0 && layerIndex == 0 && neuron.getActivation() == neuron.getActivationFunction()->getMaximum())
	{	
		// If the neuron is in the right class move it nearer to the teachingLesson, else move it further away
		return getOptions()->firstLayerLearningRate * (lesson.getTeachingPattern()->get(0, edgeIndex) - edge.getWeight());
	}
	else if (mode == 1 && layerIndex == 1)
	{	
		// If the neuron is in the right class move it nearer to the teachingLesson, else move it further away
		return getOptions()->secondLayerLearningRate * edge.getPrevNeuron()->getActivation() * (*errormap)[0][&neuron];
	}
	else
		return 0;
}

CounterpropagationLearningRuleOptions* CounterpropagationLearningRule::getOptions()
{
	return static_cast<CounterpropagationLearningRuleOptions*>(options.get());
}