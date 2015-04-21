#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"

TeachingLesson::TeachingLesson(std::vector<float>* teachingPattern_, std::vector<float>* teachingInput_)
{
	teachingInput = teachingInput_;
	teachingPattern = teachingPattern_;
}

std::unique_ptr<std::vector<float>> TeachingLesson::getErrorvector(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder)
{
	// Create the errorVector with the right size
	std::unique_ptr<std::vector<float>> errorVector(new std::vector<float>(teachingInput->size()));

	// Insert the input
	neuralNetwork.setInput(*teachingPattern);
	// Let the network calculate
	neuralNetwork.refreshAllNeurons(activationOrder);
	// Extract the output
	std::unique_ptr<std::vector<float>> outputVector = neuralNetwork.getOutput();

	// Calculate the error values (expected value - real value)
	for (int i = 0; i < teachingInput->size(); i++)
	{
		(*errorVector)[i] = (*teachingInput)[i] - (*outputVector)[i];
	}

	return errorVector;
}

float TeachingLesson::getEuclidienDistance(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder)
{
	return 0;
}

float TeachingLesson::getRMS(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder)
{
	return 0;
}

float TeachingLesson::getSpecificError(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder)
{
	// Calculate the errorVector
	std::unique_ptr<std::vector<float>> errorVector = getErrorvector(neuralNetwork, activationOrder);

	float specificError = 0;

	// Add the square of every errorValue in the errorVector
	for (std::vector<float>::iterator errorValue = errorVector->begin(); errorValue != errorVector->end(); errorValue++)
	{
		specificError += pow(*errorValue, 2);
	}

	// Divide the specific error by two
	specificError /= 2;
	
	return specificError;
}
