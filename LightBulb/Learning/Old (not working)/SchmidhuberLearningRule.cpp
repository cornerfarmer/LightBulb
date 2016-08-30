// Includes
#include "Learning/SchmidhuberLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/SynchronousOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "Learning/ResilientLearningRateHelper.hpp"

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
	for (auto layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Create a new delta vector for this neuron
			deltaVectorOutputLayer[*neuron] = std::vector<std::pair<double, bool>>(maxTimeStep + 2);
		}
	}
}


double SchmidhuberLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	double gradient = lastGradients[&edge];
	// If this is not the first block
	if (currentBlockStart != 0)
	{
		// Go through all output neurons
		for (auto outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			// Add to the gradient: last delta vector * dynamicSystemValue
			gradient -= getDeltaVectorOfNeuronInTime(*outputNeuron, currentBlockStart - 1, errormap) * (*currentDynamicSystemValues)[*outputNeuron][&edge];
		}
	}

	// Go through all timesteps of the current block
	for (int t = currentBlockStart + (currentBlockStart == 0 ? 1 : 0); t < currentBlockStart + currentBlockSize; t++)
	{
		// Add to the gradient: deltaVector * previous output
		gradient -= getDeltaVectorOfNeuronInTime(edge.getNextNeuron(), t, errormap) * outputValuesInTime[t - 1][edge.getPrevNeuron()];
	}	

	// TODO: discuss if we should also add/remember the last gradient. The algorithm says to do that, but first experiences and my mind sayed not.
	//lastGradients[edge] = gradient;

	return gradient;
}


double SchmidhuberLearningRule::getDeltaVectorOfNeuronInTime(StandardNeuron* neuron, int time, ErrorMap_t* errormap)
{
	// Only if the delta value has not calculated yet
	if (deltaVectorOutputLayer[neuron][time].second == false)
	{
		std::list<Edge*>* efferentEdges = neuron->getEfferentEdges();

		// Create a new variable which should hold the complete error fac
		double errorfac = 0;
		// If the neuron has a own error value then add it to the error fac
		if (errormap->count(time) > 0 && (*errormap)[time].count(neuron) > 0)
			errorfac = (*errormap)[time][neuron];
		
		// Go through all efferent edges
		for (auto efferentEdge = efferentEdges->begin(); efferentEdge != efferentEdges->end(); efferentEdge++)
		{
			// If this is not the last timestep or the two neurons are in the same timestep
			if (time < currentBlockStart + currentBlockSize - 1)
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

double SchmidhuberLearningRule::getDynamicSystemValue(StandardNeuron* neuron, Edge* edge)
{
	double dynamicSystemValue = 0;

	// If this is not the first block
	if (currentBlockStart != 0)
	{
		// Go through all output neurons
		for (auto outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			// Add to the dynamicSystemValue: gamma(outputNeuron) * previous dynamicSystemValue
			dynamicSystemValue += getGammaOfNeuronsInTime(*outputNeuron, neuron, currentBlockStart - 1) * (*oldDynamicSystemValues)[*outputNeuron][edge];
		}
	}
	// Go through all timesteps of the current block
	for (int t = currentBlockStart + (currentBlockStart == 0 ? 1 : 0); t < currentBlockStart + currentBlockSize; t++)
	{
		// Add to the dynamicSystemValue: gamma(nextNeuron) * previous outputValue
		dynamicSystemValue += getGammaOfNeuronsInTime(edge->getNextNeuron(), neuron, t) * outputValuesInTime[t - 1][edge->getPrevNeuron()];
	}

	return dynamicSystemValue;
}

void SchmidhuberLearningRule::initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap)
{
	
}

AbstractActivationOrder* SchmidhuberLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new SynchronousOrder();
}

void SchmidhuberLearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	edge->setWeight(edge->getWeight() - getOptions()->learningRate * deltaWeight);
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
	for (auto layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Set all deltaValues in all time steps to invalid
			for (unsigned int t = 0; t < deltaVectorOutputLayer[*neuron].size(); t++) 
				deltaVectorOutputLayer[*neuron][t].second = false;
		}
	}
}

void SchmidhuberLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{	
	currentBlockSize = neuralNetwork.getNetworkTopology()->getNeurons()->front().size();
	lastGradients.clear();
}


double SchmidhuberLearningRule::getGammaOfNeuronsInTime(StandardNeuron* neuronj, StandardNeuron* neuronl, int time)
{
	double gamma = 0;

	// If this is the last time step of the current block
	if (time == currentBlockStart + currentBlockSize - 1)
	{
		// Return 1 if the two neurons are the same, else 0
		gamma = (neuronj == neuronl);
	}
	else
	{
		// Go through all efferent edges
		for (auto efferentEdge = neuronj->getEfferentEdges()->begin(); efferentEdge != neuronj->getEfferentEdges()->end(); efferentEdge++)
		{			
			// Add to the sum: previous gammaValue * weight
			gamma += getGammaOfNeuronsInTime((*efferentEdge)->getNextNeuron(), neuronl, time + 1) * (*efferentEdge)->getWeight();			
		}

		// Calulate the gammavalue: activationFunction'(netInput) * sum
		gamma = neuronj->executeDerivationOnActivationFunction(netInputValuesInTime[time][neuronj]) * gamma;			
	}

	return gamma;
}

bool SchmidhuberLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{	
	// At the beginning of every teachingLesson start with the first timestep, else add the blocksize to the old start time to get the new one
	if (*nextStartTime == -1)
		*nextStartTime = 0;
	else
		*nextStartTime += currentBlockSize;	
	currentBlockStart = *nextStartTime;

	// Calculate the next block size (which should stay the same except there aren't enough teachingInputs left
	*nextTimeStepCount = currentBlockSize;
	*nextTimeStepCount = std::min(currentBlockSize, teachingLesson.getMaxTimeStep() + 1 - currentBlockStart);
	currentBlockSize = *nextTimeStepCount;

	// Create a new map for the new dynamic system values
	oldDynamicSystemValues.reset(new std::map<StandardNeuron*, std::map<Edge*, double>>());

	// Swap the two caches. So the new one will be the old one.
	oldDynamicSystemValues.swap(currentDynamicSystemValues);

	// If we have not reached the end of the teaching lesson and this is not the first block, recalculate all dynamic system values
	if (*nextStartTime < teachingLesson.getMaxTimeStep() + 1 && *nextStartTime > 0)
	{	
		// Go through all output neurons
		for (auto outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			// Go through all neuron groups
			for (auto neuronGroup = currentNetworkTopology->getNeurons()->begin(); neuronGroup != currentNetworkTopology->getNeurons()->end(); neuronGroup++)
			{
				// Go through all neurons
				for (auto neuron = neuronGroup->begin(); neuron != neuronGroup->end(); neuron++)
				{
					// Go through all affernetEdges of this neuron
					std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
					for (auto edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
					{
						// Compute the dynamicSystem value of this constellation
						(*currentDynamicSystemValues)[*outputNeuron][*edge] = getDynamicSystemValue(*outputNeuron, *edge);
					}
				}
			}
		}
	}

	// Only continue, if we have not reached the end of the teachingLesson
	return (*nextStartTime < teachingLesson.getMaxTimeStep() + 1);
}

std::vector<std::map<AbstractNeuron*, double>>* SchmidhuberLearningRule::getOutputValuesInTime()
{
	return &outputValuesInTime;
}

std::vector<std::map<AbstractNeuron*, double>>* SchmidhuberLearningRule::getNetInputValuesInTime()
{
	return &netInputValuesInTime;
}
