#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"

void AbstractTeachingLesson::tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	// Insert the input
	neuralNetwork.setInput(*getTeachingPattern());
	// Let the network calculate
	neuralNetwork.refreshAllNeurons(activationOrder);
}

std::unique_ptr<std::vector<float>> AbstractTeachingLesson::getErrorvector(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	// Get the teachingInput
	std::vector<float>* teachingInput = getTeachingInput(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction());

	// Create the errorVector with the right size
	std::unique_ptr<std::vector<float>> errorVector(new std::vector<float>(teachingInput->size()));

	// Try the lesson
	tryLesson(neuralNetwork, activationOrder);

	// Extract the output
	std::unique_ptr<std::vector<float>> outputVector = neuralNetwork.getOutput();

	// Calculate the error values (expected value - real value)
	for (int i = 0; i < teachingInput->size(); i++)
	{
		(*errorVector)[i] = (*teachingInput)[i] - (*outputVector)[i];
	}

	return errorVector;
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
