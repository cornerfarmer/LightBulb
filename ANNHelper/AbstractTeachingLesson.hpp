#pragma once

#ifndef _ABSTRACTTEACHINGLESSON_H_
#define _ABSTRACTTEACHINGLESSON_H_

// Library Includes
#include <vector>
#include <map>

// Forward declarations
class NeuralNetwork;
class AbstractActivationOrder;
class AbstractActivationFunction;
class NeuralNetworkIO;
class AbstractNeuron;
class StandardNeuron;

class AbstractTeachingLesson
{
public:
	// Put the teachingPattern into the neuralNetwork, refresh the network and fills (optional) the given output and netput values map
	std::unique_ptr<NeuralNetworkIO> tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	// This method should return a float vector of the teachingInput 
	virtual std::vector<float>* getTeachingInput(AbstractActivationFunction* activationFunction) = 0;
	// This method should return a float vector of the teachingPattern
	virtual NeuralNetworkIO* getTeachingPattern() = 0;
	virtual ~AbstractTeachingLesson() {}
	// Calculate the Errormap and fills (optional) the given output and netput values map
	std::unique_ptr<std::map<StandardNeuron*, float>> getErrormap(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	// Calculate the euclidient distance
	float getEuclidienDistance(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the RootMeanSquare
	float getRMS(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the specific error
	float getSpecificError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Unfolds the teaching lesson
	virtual AbstractTeachingLesson* unfold() = 0;
};

#endif

