// Includes
#include "Learning\HopfieldLearningRule.hpp"
#include "Teaching\Teacher.hpp"
#include "ActivationOrder\AsynchronousOrder.hpp"
#include "Teaching\AbstractTeachingLesson.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "NetworkTopology\RBFNetwork.hpp"
#include "Neuron\RBFThreshold.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "NetworkTopology\CounterpropagationNetwork.hpp"


HopfieldLearningRule::HopfieldLearningRule(HopfieldLearningRuleOptions &options_)
	: AbstractLearningRule(new HopfieldLearningRuleOptions(options_)) 
{	
	options->maxTries = 1;
	options->maxIterationsPerTry = 1;	
	options->offlineLearning = true;
	options->totalErrorGoal = -1;
}

void HopfieldLearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	// Set the calculated weight as new weight
	edge->setWeight(edge->getWeight() + deltaWeight);
}

void HopfieldLearningRule::printDebugOutput()
{

}

bool HopfieldLearningRule::learningHasStopped()
{
	return false;
}

void HopfieldLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	for (auto neuron = neuralNetwork.getNetworkTopology()->getNeurons()->front().begin(); neuron != neuralNetwork.getNetworkTopology()->getNeurons()->front().end(); neuron++)
	{
		for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++)
		{
			(*edge)->setWeight(0);
		}
	}
}

void HopfieldLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{

}


AbstractActivationOrder* HopfieldLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new AsynchronousOrder();
}

double HopfieldLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	double res = edge.getNextNeuron()->getNetInput() * static_cast<StandardNeuron*>(edge.getPrevNeuron())->getNetInput();

	if (getOptions()->trainHeteroassociation)
		res += static_cast<StandardNeuron*>(edge.getPrevNeuron())->getNetInput() * lesson.getTeachingInput(neuron.getActivationFunction())->get(0, neuronIndex);
	return res;
}

HopfieldLearningRuleOptions* HopfieldLearningRule::getOptions()
{
	return static_cast<HopfieldLearningRuleOptions*>(options.get());
}


bool HopfieldLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	// Only do one calculation per teaching lesson
	if (*nextStartTime != -1)
		return false;
	else
	{
		*nextTimeStepCount = 1;
		*nextStartTime = 0;		
		return true;
	}
}