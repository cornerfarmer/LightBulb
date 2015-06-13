#pragma once

#ifndef _ABSTRACTTEACHINGLESSON_H_
#define _ABSTRACTTEACHINGLESSON_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "NeuralNetworkIO.hpp"

// Forward declarations
class NeuralNetwork;
class AbstractActivationOrder;
class AbstractActivationFunction;
class AbstractNeuron;
class StandardNeuron;

typedef std::map<int, std::map<StandardNeuron*, float>> ErrorMap_t;

class AbstractTeachingLesson
{
public:
	// Put the teachingPattern into the neuralNetwork, refresh the network and fills (optional) the given output and netput values map
	std::unique_ptr<NeuralNetworkIO<float>> tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = 0, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	// This method should return a float vector of the teachingInput 
	virtual NeuralNetworkIO<float>* getTeachingInput(AbstractActivationFunction* activationFunction) = 0;

	std::unique_ptr<ErrorMap_t> getTeachingInputMap(NeuralNetwork &neuralNetwork);
	// This method should return a float vector of the teachingPattern
	virtual NeuralNetworkIO<float>* getTeachingPattern() = 0;
	virtual ~AbstractTeachingLesson() {}
	// Calculate the Errormap and fills (optional) the given output and netput values map
	std::unique_ptr<ErrorMap_t> getErrormap(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = 0, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	// Calculate the euclidient distance
	float getEuclidienDistance(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the RootMeanSquare
	float getRMS(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the specific error
	float getSpecificError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Unfolds the teaching lesson
	virtual AbstractTeachingLesson* unfold() = 0;

	virtual int getMaxTimeStep() = 0;
};

#endif

