// Includes
#include "Learning/LVQ1LearningRule.hpp"
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


LVQ1LearningRule::LVQ1LearningRule(LVQ1LearningRuleOptions &options_)
	: AbstractLearningRule(new LVQ1LearningRuleOptions(options_)) 
{	

}

void LVQ1LearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	// Set the calculated weight as new weight
	edge->setWeight(edge->getWeight() + deltaWeight);
}

void LVQ1LearningRule::printDebugOutput()
{

}

bool LVQ1LearningRule::learningHasStopped()
{
	return false;
}

void LVQ1LearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
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

void LVQ1LearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{

}

AbstractActivationOrder* LVQ1LearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

double LVQ1LearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	if (layerIndex == 0 && neuron.getActivation() == neuron.getActivationFunction()->getMaximum())
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
	else
		return 0;
}

LVQ1LearningRuleOptions* LVQ1LearningRule::getOptions()
{
	return static_cast<LVQ1LearningRuleOptions*>(options.get());
}