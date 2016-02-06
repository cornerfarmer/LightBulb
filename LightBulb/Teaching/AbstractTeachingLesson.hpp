#pragma once

#ifndef _ABSTRACTTEACHINGLESSON_H_
#define _ABSTRACTTEACHINGLESSON_H_

// Library Includes
#include <vector>
#include <map>
#include <memory>

// Includes
#include "NeuralNetwork/NeuralNetworkIO.hpp"

// Forward declarations
class NeuralNetwork;
class AbstractActivationOrder;
class AbstractActivationFunction;
class AbstractNeuron;
class StandardNeuron;

typedef std::map<int, std::map<StandardNeuron*, double>> ErrorMap_t;

class AbstractTeachingLessoni
{
public:
	virtual ~AbstractTeachingLessoni() {}
	// Put the teachingPattern into the neuralNetwork, refresh the network and fills (optional) the given output and netput values map
	std::unique_ptr<NeuralNetworkIO<double>> tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = -1, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = NULL);
	// This method should return a double vector of the teachingInput 
	virtual NeuralNetworkIO<double>* getTeachingInput(AbstractActivationFunction* activationFunction) = 0;
	// Returns a map of all teaching inputs of all neurons in all timesteps
	std::unique_ptr<ErrorMap_t> getTeachingInputMap(NeuralNetwork &neuralNetwork);
	// This method should return a double vector of the teachingPattern
	virtual NeuralNetworkIO<double>* getTeachingPattern() = 0;	
	// Calculate the Errormap and fills (optional) the given output and netput values map
	std::unique_ptr<ErrorMap_t> getErrormap(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = -1, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = NULL);
	// Returns the Errormap from the given output vector
	std::unique_ptr<ErrorMap_t> getErrormapFromOutputVector(NeuralNetworkIO<double>& outputVector, NeuralNetwork &neuralNetwork);
	// Calculate the euclidient distance
	double getEuclidienDistance(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the RootMeanSquare
	double getRMS(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Calculate the specific error
	double getSpecificError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Unfolds the teaching lesson
	virtual AbstractTeachingLessoni* unfold() = 0;
	// Returns the maximal time step in the teaching lesson
	virtual int getMaxTimeStep() = 0;
};

#endif

