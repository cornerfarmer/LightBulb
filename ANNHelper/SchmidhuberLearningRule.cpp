#include "SchmidhuberLearningRule.hpp"
#include "Teacher.hpp"
#include "SynchronousOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "ResilientLearningRateHelper.hpp"

SchmidhuberLearningRule::SchmidhuberLearningRule(SchmidhuberLearningRuleOptions& options_) 
	: AbstractLearningRule(new SchmidhuberLearningRuleOptions(options_))
{
	
}


void SchmidhuberLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// Remove all output values
	outputValuesInTime.clear();
	// Resize it to the new max time steps
	outputValuesInTime.resize(10);
	// Remove all output values
	netInputValuesInTime.clear();
	// Resize it to the new max time steps
	netInputValuesInTime.resize(10);

	currentBlockSize = neuralNetwork.getNetworkTopology()->getInputNeurons()->size();
}


float SchmidhuberLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	float outputNeuronsDependency = 0;
	for (ErrorMap_t::iterator outputNeurons = errormap->begin(); outputNeurons != errormap->end(); outputNeurons++)
	{
		for (std::map<StandardNeuron*, float>::iterator outputNeuron = outputNeurons->second.begin(); outputNeuron != outputNeurons->second.end(); outputNeuron++)
		{
			outputNeuronsDependency += outputNeuron->second * getDynamicSystemValueOfEdgeAtTime(edge, outputNeuron->first, outputNeurons->first, true, errormap);
		}
	}

	float returnValue = getOptions()->learningRate * outputNeuronsDependency;
	return returnValue;
}

void SchmidhuberLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	
}


AbstractActivationOrder* SchmidhuberLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new SynchronousOrder();
}

void SchmidhuberLearningRule::adjustWeight(Edge* edge, float deltaWeight)
{
	edge->setWeight(edge->getWeight() + deltaWeight);
}

void SchmidhuberLearningRule::printDebugOutput()
{

}

bool SchmidhuberLearningRule::learningHasStopped()
{
	return false;
}

SchmidhuberLearningRuleOptions* SchmidhuberLearningRule::getOptions()
{
	return static_cast<SchmidhuberLearningRuleOptions*>(options.get());
}

void SchmidhuberLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}
}

void SchmidhuberLearningRule::initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork)
{
	dynamicSystemCache.clear();
}

void SchmidhuberLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{

}

float SchmidhuberLearningRule::getDynamicSystemValueOfEdgeAtTime(Edge* edge, StandardNeuron* neuron, int time, bool isInFirstCalculationLayer, ErrorMap_t* errormap)
{
	if (time != 0)
	{
		float gradient = 0;

		for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			gradient -= backpropagationThroughTimeLearningRule.getDeltaVectorOfNeuronInTime(*outputNeuron, currentBlockStart, errormap) * getDynamicSystemValueOfEdgeAtTime(edge, *outputNeuron, currentBlockStart, true, errormap);
		}

		for (int t = currentBlockStart + 1; t < currentBlockStart + currentBlockSize; t++)
		{
			gradient -= backpropagationThroughTimeLearningRule.getDeltaVectorOfNeuronInTime(edge->getNextNeuron(), t, errormap) * outputValuesInTime[t - 1][edge->getPrevNeuron()];
		}	

		return gradient;
	}
	else
		return 0;
}

bool SchmidhuberLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	*nextTimeStepCount = currentBlockSize;
	if (*nextStartTime == -1)
		*nextStartTime = 0;
	else
		*nextStartTime += currentBlockSize;
	*nextTimeStepCount = std::min(currentBlockSize, teachingLesson.getMaxTimeStep() + 1 - *nextStartTime);
	return (*nextStartTime < teachingLesson.getMaxTimeStep() + 1);
}

std::vector<std::map<AbstractNeuron*, float>>* SchmidhuberLearningRule::getOutputValuesInTime()
{
	return &outputValuesInTime;
}

std::vector<std::map<AbstractNeuron*, float>>* SchmidhuberLearningRule::getNetInputValuesInTime()
{
	return &netInputValuesInTime;
}
