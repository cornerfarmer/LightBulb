#pragma once

#ifndef _ABSTRACTTEACHINGLESSON_H_
#define _ABSTRACTTEACHINGLESSON_H_

// Library Includes
#include <vector>
#include <map>

// Includes
#include "NeuralNetwork\NeuralNetworkIO.hpp"

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
	virtual ~AbstractTeachingLesson() {}
	// Put the teachingPattern into the neuralNetwork, refresh the network and fills (optional) the given output and netput values map
	std::unique_ptr<NeuralNetworkIO<float>> tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = 0, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	// This method should return a float vector of the teachingInput 
	virtual NeuralNetworkIO<float>* getTeachingInput(AbstractActivationFunction* activationFunction) = 0;
	// Returns a map of all teaching inputs of all neurons in all timesteps
	std::unique_ptr<ErrorMap_t> getTeachingInputMap(NeuralNetwork &neuralNetwork);
	// This method should return a float vector of the teachingPattern
	virtual NeuralNetworkIO<float>* getTeachingPattern() = 0;	
	// Calculate the Errormap and fills (optional) the given output and netput values map
	std::unique_ptr<ErrorMap_t> getErrormap(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = 0, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	// Returns the Errormap from the given output vector
	std::unique_ptr<ErrorMap_t> getErrormapFromOutputVector(NeuralNetworkIO<float>& outputVector, NeuralNetwork &neuralNetwork);
	// Calculate the euclidient distance
	float getEuclidienDistance(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the RootMeanSquare
	float getRMS(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the specific error
	float getSpecificError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Unfolds the teaching lesson
	virtual AbstractTeachingLesson* unfold() = 0;
	// Returns the maximal time step in the teaching lesson
	virtual int getMaxTimeStep() = 0;
};

#endif

