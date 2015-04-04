#pragma once

#ifndef _TEACHINGLESSON_H_
#define _TEACHINGLESSON_H_

// Library Includes
#include <vector>

// Forward declarations
class NeuralNetwork;
class ActivationOrder;

class TeachingLesson
{
private:
	// The values the neural network should give back
	std::vector<float>* teachingInput;
	// The values we will put into the neural network
	std::vector<float>* teachingPattern;
public:
	TeachingLesson(std::vector<float>* teachingPattern_, std::vector<float>* teachingInput_);
	// Calculate the Errorvector
	std::unique_ptr<std::vector<float>> getErrorvector(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder);
	// Calculate the euclidient distance
	float getEuclidienDistance(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder);
	// Calculate the RootMeanSquare
	float getRMS(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder);
	// Calculate the specific error
	float getSpecificError(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder);
};

#endif

