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

	currentNetworkTopology = neuralNetwork.getNetworkTopology();

	int maxTimeStep = teacher.getMaxTimeStep();
	// Go through all hidden/output layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Create a new delta vector for this neuron
			deltaVectorOutputLayer[*neuron] = std::vector<std::pair<float, bool>>(maxTimeStep + 2);
		}
	}
}


float SchmidhuberLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	if (time != 0)
	{
		float gradient = 0;

		for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			gradient -= getDeltaVectorOfNeuronInTime(*outputNeuron, currentBlockStart, errormap) * (*currentDynamicSystemValues)[*outputNeuron][edge];
		}

		for (int t = currentBlockStart + 1; t <= currentBlockStart + currentBlockSize; t++)
		{
			gradient -= getDeltaVectorOfNeuronInTime(edge->getNextNeuron(), t, errormap) * outputValuesInTime[t - 1][edge->getPrevNeuron()];
		}	

		return gradient;
	}
	else
		return 0;	
}


float SchmidhuberLearningRule::getDeltaVectorOfNeuronInTime(StandardNeuron* neuron, int time, ErrorMap_t* errormap)
{
	// Only if the delta value has not calculated yet
	if (deltaVectorOutputLayer[neuron][time].second == false)
	{
		std::list<Edge*>* efferentEdges = neuron->getEfferentEdges();

		// Create a new variable which should hold the complete error fac
		float errorfac = 0;
		// If the neuron has a own error value then add it to the error fac
		if (errormap->count(time) > 0 && (*errormap)[time].count(neuron) > 0)
			errorfac = (*errormap)[time][neuron];
		
		// Go through all efferent edges
		for (std::list<Edge*>::iterator efferentEdge = efferentEdges->begin(); efferentEdge != efferentEdges->end(); efferentEdge++)
		{
			// If this is not the last timestep or the two neurons are in the same timestep
			if (time < currentBlockStart + currentBlockSize)
			{
				// Add to the errorfac: deltaValueNextNeuron(sameTimestepEdge ? t : t + 1) * weight
				errorfac += getDeltaVectorOfNeuronInTime((*efferentEdge)->getNextNeuron(), time + 1, errormap) * (*efferentEdge)->getWeight();
			}
		}

		// Calulate the deltaValue: activationFunction'(netInput) * errorfac
		deltaVectorOutputLayer[neuron][time].first = neuron->executeDerivationOnActivationFunction(netInputValuesInTime[time][neuron]) * errorfac;			
		// Mark the delta value as valid
		deltaVectorOutputLayer[neuron][time].second = true;
	}
	// Return the deltaValue
	return deltaVectorOutputLayer[neuron][time].first;
}

float SchmidhuberLearningRule::getDynamicSystemValue(StandardNeuron* neuron, Edge* edge)
{
	float dynamicSystemValue = 0;
	for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
	{
		dynamicSystemValue += getGammaOfNeuronsInTime(*outputNeuron, neuron, currentBlockStart) * (*oldDynamicSystemValues)[*outputNeuron][edge];
	}

	for (int t = currentBlockStart + 1; t <= currentBlockStart + currentBlockSize; t++)
	{
		dynamicSystemValue += getGammaOfNeuronsInTime(edge->getNextNeuron(), neuron, t) * outputValuesInTime[t - 1][edge->getPrevNeuron()];
	}

	return dynamicSystemValue;
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
	// Go through all hidden/output layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Set all deltaValues in all time steps to invalid
			for (int t = 0; t < deltaVectorOutputLayer[*neuron].size(); t++) 
				deltaVectorOutputLayer[*neuron][t].second = false;
		}
	}
}

void SchmidhuberLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{	
	currentBlockSize = neuralNetwork.getNetworkTopology()->getNeurons()->front().size();
}


float SchmidhuberLearningRule::getGammaOfNeuronsInTime(StandardNeuron* neuronj, StandardNeuron* neuronl, int time)
{
	float gamma = 0;

	if (time == currentBlockStart + currentBlockSize)
	{
		gamma = (neuronj == neuronl);
	}
	else
	{
		// Go through all efferent edges
		for (std::list<Edge*>::iterator efferentEdge = neuronj->getEfferentEdges()->begin(); efferentEdge != neuronj->getEfferentEdges()->end(); efferentEdge++)
		{			
			// Add to the errorfac: deltaValueNextNeuron(sameTimestepEdge ? t : t + 1) * weight
			gamma += getGammaOfNeuronsInTime((*efferentEdge)->getNextNeuron(), neuronl, time + 1) * (*efferentEdge)->getWeight();			
		}

		// Calulate the deltaValue: activationFunction'(netInput) * errorfac
		gamma = neuronj->executeDerivationOnActivationFunction(netInputValuesInTime[time][neuronj]) * gamma;			
	}

	return gamma;
}

bool SchmidhuberLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{	
	if (*nextStartTime == -1)
		*nextStartTime = 0;
	else
		*nextStartTime += currentBlockSize;

	currentBlockStart = *nextStartTime;

	*nextTimeStepCount = currentBlockSize;
	*nextTimeStepCount = std::min(currentBlockSize, teachingLesson.getMaxTimeStep() + 1 - currentBlockStart);
	currentBlockSize = *nextTimeStepCount;

	oldDynamicSystemValues.reset(new std::map<StandardNeuron*, std::map<Edge*, float>>());

	oldDynamicSystemValues.swap(currentDynamicSystemValues);

	if (*nextStartTime < teachingLesson.getMaxTimeStep() + 1 && *nextStartTime > 0)
	{	
		for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			// Go through all neurons
			for (std::vector<std::vector<StandardNeuron*>>::iterator neuronGroup = currentNetworkTopology->getNeurons()->begin(); neuronGroup != currentNetworkTopology->getNeurons()->end(); neuronGroup++)
			{
				// Go through all neurons
				for (std::vector<StandardNeuron*>::iterator neuron = neuronGroup->begin(); neuron != neuronGroup->end(); neuron++)
				{
					// Go through all affernetEdges of this neuron
					std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
					for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
					{
						(*currentDynamicSystemValues)[*outputNeuron][*edge] = getDynamicSystemValue(*outputNeuron, *edge);
					}
				}
			}
		}
	}

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
