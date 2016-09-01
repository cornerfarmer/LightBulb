// Includes
#include "Learning/TruncatedBackpropagationThroughTimeLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/Edge.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "ActivationOrder/SynchronousOrder.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/FreeNetwork.hpp"


TruncatedBackpropagationThroughTimeLearningRule::TruncatedBackpropagationThroughTimeLearningRule(BackpropagationThroughTimeLearningRuleOptions options_) 
	: BackpropagationLearningRule(new BackpropagationThroughTimeLearningRuleOptions(options_))
{

}

void TruncatedBackpropagationThroughTimeLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{	
	BackpropagationLearningRule::initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);

	// Remove all output values
	outputValuesInTime.clear();
	// Resize it to the new max time steps
	outputValuesInTime.resize(getOptions()->maxTimeSteps);
	// Remove all output values
	netInputValuesInTime.clear();
	// Resize it to the new max time steps
	netInputValuesInTime.resize(getOptions()->maxTimeSteps);
	// Get all same timestep edges
	sameTimestepEdges = activationOrder.getSameTimestepEdges(*neuralNetwork.getNetworkTopology());

	// Go through all hidden/output layers
	for (auto layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Create a new delta vector for this neuron
			deltaVectorOutputLayer[*neuron] = std::vector<std::pair<double, bool>>(getOptions()->maxTimeSteps);
		}
	}
}

double TruncatedBackpropagationThroughTimeLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	// Calculate the gradient
	double gradient = 0;
	
	// Go through all time steps
	for (unsigned int t = 0; t < getOptions()->maxTimeSteps; t++)
	{
		// If this is not the first timestep or both neurons are in the same time step
		if (t > 0 || (*sameTimestepEdges)[&edge])
		{
			// Calulate and add the gradient of the current time step: - outputPrevNeuron(sameTimestepEdge ? t : t - 1) * deltaValueNextNeuron(t)
			gradient += -1 * outputValuesInTime[(*sameTimestepEdges)[&edge] ? t : t - 1][edge.getPrevNeuron()] * deltaVectorOutputLayer[edge.getNextNeuron()][t].first;
		}
	}

	// Return the gradient (Divide through the time step count, so the gradient does not get too big)
	return gradient / getOptions()->maxTimeSteps;
}

void TruncatedBackpropagationThroughTimeLearningRule::initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap)
{
	// Go through all timesteps
	for (unsigned int t = 0; t < getOptions()->maxTimeSteps; t++)
	{
		// Calculate the delta vector of the current neuron
		getDeltaVectorOfNeuronInTime(&neuron, t, errormap);
	}
}

double TruncatedBackpropagationThroughTimeLearningRule::getDeltaVectorOfNeuronInTime(StandardNeuron* neuron, unsigned int time, ErrorMap_t* errormap)
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
			if (time < getOptions()->maxTimeSteps - 1 || (*sameTimestepEdges)[*efferentEdge])
			{
				// Add to the errorfac: deltaValueNextNeuron(sameTimestepEdge ? t : t + 1) * weight
				errorfac += getDeltaVectorOfNeuronInTime((*efferentEdge)->getNextNeuron(), (*sameTimestepEdges)[*efferentEdge] ? time : time + 1, errormap) * (*efferentEdge)->getWeight();
			}
		}

		// Calulate the deltaValue: activationFunction'(netInput) * errorfac
		deltaVectorOutputLayer[neuron][time].first = (neuron->executeDerivationOnActivationFunction(netInputValuesInTime[time][neuron]) + getOptions()->flatSpotEliminationFac) * errorfac;			
		// Mark the delta value as valid
		deltaVectorOutputLayer[neuron][time].second = true;
	}
	// Return the deltaValue
	return deltaVectorOutputLayer[neuron][time].first;
}

BackpropagationThroughTimeLearningRuleOptions* TruncatedBackpropagationThroughTimeLearningRule::getOptions()
{
	return static_cast<BackpropagationThroughTimeLearningRuleOptions*>(options.get());
}

std::vector<std::map<AbstractNeuron*, double>>* TruncatedBackpropagationThroughTimeLearningRule::getOutputValuesInTime()
{
	return &outputValuesInTime;
}

std::vector<std::map<AbstractNeuron*, double>>* TruncatedBackpropagationThroughTimeLearningRule::getNetInputValuesInTime()
{
	return &netInputValuesInTime;
}

void TruncatedBackpropagationThroughTimeLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{
	// Go through all hidden/output layers
	for (auto layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
	{
		// Go through all neurons in this layer
		for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Set all deltaValues in all time steps to invalid
			for (unsigned int t = 0; t < getOptions()->maxTimeSteps; t++) 
				deltaVectorOutputLayer[*neuron][t].second = false;
		}
	}
}

AbstractActivationOrder* TruncatedBackpropagationThroughTimeLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	if (dynamic_cast<FeedForwardNetworkTopology*>(neuralNetwork.getNetworkTopology()))
		return new TopologicalOrder();
	else if (dynamic_cast<FreeNetwork*>(neuralNetwork.getNetworkTopology()))
		return new SynchronousOrder();
	else
		throw std::logic_error("Something went wrong while setting the activation order for the LearningRule");
}

bool TruncatedBackpropagationThroughTimeLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	if (*nextStartTime != -1)
		return false;
	else
	{
		*nextStartTime = 0;
		*nextTimeStepCount = getOptions()->maxTimeSteps;
		return true;
	}
}