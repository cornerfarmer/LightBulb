// Includes
#include "Learning\RealTimeRecurrentLearningRule.hpp"
#include "Teaching\Teacher.hpp"
#include "ActivationOrder\SynchronousOrder.hpp"
#include "Teaching\AbstractTeachingLesson.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "Learning\ResilientLearningRateHelper.hpp"

RealTimeRecurrentLearningRule::RealTimeRecurrentLearningRule(RealTimeRecurrentLearningRuleOptions& options_) 
	: AbstractLearningRule(new RealTimeRecurrentLearningRuleOptions(options_))
{
	
}


void RealTimeRecurrentLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	// Remove all output values
	outputValuesInTime.clear();
	// Resize it to the new max time steps
	outputValuesInTime.resize(10);
	// Remove all output values
	netInputValuesInTime.clear();
	// Resize it to the new max time steps
	netInputValuesInTime.resize(10);

}


double RealTimeRecurrentLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	double outputNeuronsDependency = 0;
	// Go through all error maps
	for (auto outputNeurons = errormap->begin(); outputNeurons != errormap->end(); outputNeurons++)
	{
		// Go through all output neurons
		for (auto outputNeuron = outputNeurons->second.begin(); outputNeuron != outputNeurons->second.end(); outputNeuron++)
		{
			// Add to the gradient: errorvalue * dynamicSystemValue
			outputNeuronsDependency += outputNeuron->second * getDynamicSystemValueOfEdgeAtTime(&edge, outputNeuron->first, outputNeurons->first, true, errormap);
		}
	}
	// If teacher forcing is enabled
	if (getOptions()->teacherForcing)
	{
		// If there are teaching inputs at the current time step
		if (currentTeachingInputMap->count(currentTimeStep) != 0)
		{
			// Go through all output neurons
			for (auto outputNeuron = (*currentTeachingInputMap)[currentTimeStep].begin();  outputNeuron != (*currentTeachingInputMap)[currentTimeStep].end(); outputNeuron++)
			{
				// Inject the wished activation (teachingInput)
				outputNeuron->first->injectActivation(outputNeuron->first->getActivation() + outputNeuron->second);
			}
		}
	}
	// Return the deltaWeight: learningRate * gradient
	return getOptions()->learningRate * outputNeuronsDependency;
}

void RealTimeRecurrentLearningRule::initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap)
{
	
}


AbstractActivationOrder* RealTimeRecurrentLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new SynchronousOrder();
}

void RealTimeRecurrentLearningRule::adjustWeight(Edge* edge, double deltaWeight)
{
	edge->setWeight(edge->getWeight() + deltaWeight);
}

void RealTimeRecurrentLearningRule::printDebugOutput()
{

}

bool RealTimeRecurrentLearningRule::learningHasStopped()
{
	return false;
}

RealTimeRecurrentLearningRuleOptions* RealTimeRecurrentLearningRule::getOptions()
{
	return static_cast<RealTimeRecurrentLearningRuleOptions*>(options.get());
}

void RealTimeRecurrentLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// If we can change the weights before learning
	if (options->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
	}
}

void RealTimeRecurrentLearningRule::initializeAllWeightAdjustments(NeuralNetwork &neuralNetwork)
{
	// Go through the whole dynamic system cache
	for (auto edge = dynamicSystemCache.begin(); edge != dynamicSystemCache.end(); edge++)
	{
		for (auto neuron = edge->second.begin(); neuron != edge->second.end(); neuron++)
		{
			for (auto time = neuron->second.begin(); time != neuron->second.end(); time++)
			{
				// Set the valid value to false
				time->second.second = false;
			}
		}
	}
}

void RealTimeRecurrentLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{
	// If we should use teacherForcing extract the teachingInputMap from the currentTeachingInputMap
	if (getOptions()->teacherForcing)
		currentTeachingInputMap = teachingLesson.getTeachingInputMap(neuralNetwork);
}

double RealTimeRecurrentLearningRule::getDynamicSystemValueOfEdgeAtTime(Edge* edge, StandardNeuron* neuron, int time, bool isInFirstCalculationLayer, ErrorMap_t* errormap)
{
	// If the corresponding cache value is not valid
	if (!dynamicSystemCache[edge][neuron][time].second)
	{
		// If this is not the first time step 
		if (time != 0 && (isInFirstCalculationLayer || !getOptions()->teacherForcing || currentTeachingInputMap->count(time) == 0 || (*currentTeachingInputMap)[time].count(neuron) == 0))
		{
			double previousValuesSum = 0;

			// Go through all afferent edges
			for (auto afferentEdge = neuron->getAfferentEdges()->begin(); afferentEdge != neuron->getAfferentEdges()->end(); afferentEdge++)
			{
				// If the prevNeuron is a standardNeuron (not a BiasNeuron/InputNeuron)
				StandardNeuron* prevNeuron = dynamic_cast<StandardNeuron*>((*afferentEdge)->getPrevNeuron());
				// Add the weighted dynamic system value of the previous neuron to the sum
				if (prevNeuron)
					previousValuesSum += (*afferentEdge)->getWeight() * getDynamicSystemValueOfEdgeAtTime(edge, prevNeuron, time - 1, false, errormap);
			}
			// Calculate the dynamic system value: activationFunction'(netInput) * (previousValue + output of the prev neuron, if the next neuron is the current one)
			dynamicSystemCache[edge][neuron][time].first = neuron->executeDerivationOnActivationFunction(netInputValuesInTime[time][neuron]) * (previousValuesSum + (edge->getNextNeuron() == neuron ? outputValuesInTime[time - 1][edge->getPrevNeuron()] : 0));
		}
		else
			dynamicSystemCache[edge][neuron][time].first = 0;
		// Set the cache to valid
		dynamicSystemCache[edge][neuron][time].second = true;
	}
	// Return the cached value
	return dynamicSystemCache[edge][neuron][time].first;
}

bool RealTimeRecurrentLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	// Always do one step
	*nextTimeStepCount = 1;
	// Increment the current starttime
	(*nextStartTime)++;
	currentTimeStep = *nextStartTime;
	// Only continue if we have not reached the end of the teachingLesson
	return (*nextStartTime < teachingLesson.getMaxTimeStep() + 1);
}

std::vector<std::map<AbstractNeuron*, double>>* RealTimeRecurrentLearningRule::getOutputValuesInTime()
{
	return &outputValuesInTime;
}

std::vector<std::map<AbstractNeuron*, double>>* RealTimeRecurrentLearningRule::getNetInputValuesInTime()
{
	return &netInputValuesInTime;
}
