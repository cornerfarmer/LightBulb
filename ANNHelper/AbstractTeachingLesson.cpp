#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "NeuralNetworkIO.hpp"

std::unique_ptr<NeuralNetworkIO> AbstractTeachingLesson::tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime)
{
	// Let the network calculate
	return neuralNetwork.calculate(*getTeachingPattern(), activationOrder, outputValuesInTime, netInputValuesInTime);
}

std::unique_ptr<std::map<StandardNeuron*, float>> AbstractTeachingLesson::getErrormap(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime)
{
	// Get the teachingInput
	std::vector<float>* teachingInput = getTeachingInput(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction());

	// Create the errorVector with the right size
	std::unique_ptr<std::map<StandardNeuron*, float>> errorMap(new std::map<StandardNeuron*, float>());

	// Try the lesson and extract the output
	std::unique_ptr<NeuralNetworkIO> outputVector = tryLesson(neuralNetwork, activationOrder, outputValuesInTime, netInputValuesInTime);

	// Calculate the error values (expected value - real value)
	for (int i = 0; i < teachingInput->size(); i++)
	{
		(*errorMap)[static_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[i])] = (*teachingInput)[i] - outputVector->back()[i];
	}

	return errorMap;
}

float AbstractTeachingLesson::getEuclidienDistance(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	return 0;
}

float AbstractTeachingLesson::getRMS(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	return 0;
}

float AbstractTeachingLesson::getSpecificError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	// Calculate the errorVector
	std::unique_ptr<std::map<StandardNeuron*, float>> errorMap = getErrormap(neuralNetwork, activationOrder);

	float specificError = 0;

	// Add the square of every errorValue in the errorVector
	for (std::map<StandardNeuron*, float>::iterator errorValue = errorMap->begin(); errorValue != errorMap->end(); errorValue++)
	{
		specificError += pow(errorValue->second, 2);
	}

	// Divide the specific error by two
	specificError /= 2;
	
	return specificError;
}
