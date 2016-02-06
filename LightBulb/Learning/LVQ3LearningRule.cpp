// Includes
#include "Learning/LVQ3LearningRule.hpp"
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
#include "NetworkTopology/LVQNetwork.hpp"


LVQ3LearningRule::LVQ3LearningRule(LVQ3LearningRuleOptions &options_)
	: AbstractLearningRule(new LVQ3LearningRuleOptions(options_)) 
{	

}

void LVQ3LearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	// Set the calculated weight as new weight
	edge->setWeight(edge->getWeight() + deltaWeight);
}

void LVQ3LearningRule::printDebugOutput()
{

}

bool LVQ3LearningRule::learningHasStopped()
{
	return false;
}

void LVQ3LearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	
}

void LVQ3LearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Divide neurons into classes
		static_cast<LVQNetwork*>(neuralNetwork.getNetworkTopology())->divideCodebookVectorsIntoClasses();
		// Place them on random teaching lessons
		static_cast<LVQNetwork*>(neuralNetwork.getNetworkTopology())->placeCodebookVectorsOnTeachingLessons(teacher);		
	}
}

AbstractActivationOrder* LVQ3LearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

double LVQ3LearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	if (changeWeights && (&neuron == firstWinnerNeuron || &neuron == secondWinnerNeuron))
	{		
		if (sameClasses)
		{
			// If they are in the same class move them nearer to the teachingInput (depending on the special learningRateFactor)
			return getOptions()->sameClassesLearningRateFactor * getOptions()->learningRate * (lesson.getTeachingPattern()->get(0, edgeIndex) - edge.getWeight());
		}
		else
		{
			// If the neuron is in the right class move it nearer to the teachingLesson, else move it further away
			if (static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfNeuronWithIndex(neuronIndex) == static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfTeachingLesson(lesson))
			{	
				return getOptions()->learningRate * (lesson.getTeachingPattern()->get(0, edgeIndex) - edge.getWeight());		
			}
			else
			{
				return - getOptions()->learningRate * (lesson.getTeachingPattern()->get(0, edgeIndex) - edge.getWeight());
			}
		}
	}
	else
		return 0;
}

void LVQ3LearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{
	// Determine the winner neurons
	secondWinnerNeuron = NULL;
	for (auto neuron = neuralNetwork.getNetworkTopology()->getNeurons()->front().begin(); neuron != neuralNetwork.getNetworkTopology()->getNeurons()->front().end(); neuron++)
	{
		if ((*neuron)->getActivation() == (*neuron)->getActivationFunction()->getMaximum())
			firstWinnerNeuron = *neuron;
		else if (!secondWinnerNeuron || secondWinnerNeuron->getNetInput() > (*neuron)->getNetInput())		
			secondWinnerNeuron = *neuron;		
	}
	
	changeWeights = false;
	// Extract the classes of the two winner neurons and the teachingInput
	int firstWinnerNeuronClass = static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfNeuron(firstWinnerNeuron);
	int secondWinnerNeuronClass = static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfNeuron(secondWinnerNeuron);
	int teachingInputClass = static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfTeachingLesson(teachingLesson);
	// Only change weights if the two winner neurons are not in the same class
	changeWeights = (firstWinnerNeuronClass != secondWinnerNeuronClass);
	// Only change weights if one of them is in the same class as the teachingInput
	changeWeights &= (firstWinnerNeuronClass == teachingInputClass || secondWinnerNeuronClass == teachingInputClass);
	// Only change weights if the input lies in the relative window
	changeWeights &= std::min(firstWinnerNeuron->getNetInput() / secondWinnerNeuron->getNetInput(), secondWinnerNeuron->getNetInput() / firstWinnerNeuron->getNetInput()) > (1 - getOptions()->relativeWindow) / (1 + getOptions()->relativeWindow);
	// Determine if they are all in the same class
	sameClasses = (firstWinnerNeuronClass == secondWinnerNeuronClass && firstWinnerNeuronClass == teachingInputClass);
	changeWeights |= sameClasses;
}

LVQ3LearningRuleOptions* LVQ3LearningRule::getOptions()
{
	return static_cast<LVQ3LearningRuleOptions*>(options.get());
}