// Includes
#include "Learning/OLVQ1LearningRule.hpp"
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


OLVQ1LearningRule::OLVQ1LearningRule(OLVQ1LearningRuleOptions &options_)
	: AbstractLearningRule(new OLVQ1LearningRuleOptions(options_)) 
{	

}

void OLVQ1LearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	// Set the calculated weight as new weight
	edge->setWeight(edge->getWeight() + deltaWeight);
}

void OLVQ1LearningRule::printDebugOutput()
{

}

bool OLVQ1LearningRule::learningHasStopped()
{
	return false;
}

void OLVQ1LearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
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

void OLVQ1LearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Reset all learningRates
	for (auto neuron = neuralNetwork.getNetworkTopology()->getNeurons()->front().begin(); neuron != neuralNetwork.getNetworkTopology()->getNeurons()->front().end(); neuron++)
	{
		learningRates[*neuron] = getOptions()->learningRateStart;
	}
}

AbstractActivationOrder* OLVQ1LearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

double OLVQ1LearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLessoni& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	// If the current neuron is the nearest neuron
	if (layerIndex == 0 && neuron.getActivation() == neuron.getActivationFunction()->getMaximum())
	{	
		// If the neuron is in the right class move it nearer to the teachingLesson, else move it further away
		if (static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfNeuronWithIndex(neuronIndex) == static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfTeachingLesson(lesson))
		{	
			return learningRates[&neuron] * (lesson.getTeachingPattern()->get(0, edgeIndex) - edge.getWeight());
		}
		else
		{
			return - learningRates[&neuron] * (lesson.getTeachingPattern()->get(0, edgeIndex) - edge.getWeight());
		}
	}
	else
		return 0;
}

void OLVQ1LearningRule::initializeNeuronWeightCalculation(AbstractTeachingLessoni& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap)
{
	// If the current neuron is the nearest neuron
	if (layerIndex == 0 && neuron.getActivation() == neuron.getActivationFunction()->getMaximum())
	{	
		float sign;
		if (static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfNeuronWithIndex(neuronIndex) == static_cast<LVQNetwork*>(currentNeuralNetwork->getNetworkTopology())->getClassOfTeachingLesson(lesson))
			sign = 1;
		else
			sign = -1;
		// Adjust the learningRate
		learningRates[&neuron] = std::min(getOptions()->learningRateStart, learningRates[&neuron] / (1 + sign * learningRates[&neuron]));
	}
}

OLVQ1LearningRuleOptions* OLVQ1LearningRule::getOptions()
{
	return static_cast<OLVQ1LearningRuleOptions*>(options.get());
}