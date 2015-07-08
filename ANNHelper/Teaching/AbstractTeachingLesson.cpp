#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "NeuralNetworkIO.hpp"

std::unique_ptr<NeuralNetworkIO<float>> AbstractTeachingLesson::tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime)
{
	// Let the network calculate
	return neuralNetwork.calculate(*getTeachingPattern(), activationOrder, startTime, timeStepCount, outputValuesInTime, netInputValuesInTime);
}

std::unique_ptr<ErrorMap_t> AbstractTeachingLesson::getErrormap(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime)
{
	std::unique_ptr<ErrorMap_t> errorMap;

	if (timeStepCount != -1)
	{
		// Try the lesson and extract the output
		std::unique_ptr<NeuralNetworkIO<float>> outputVector = tryLesson(neuralNetwork, activationOrder, startTime, timeStepCount, outputValuesInTime, netInputValuesInTime);
		errorMap = getErrormapFromOutputVector(*outputVector, neuralNetwork);
	}
	else
		errorMap.reset(new ErrorMap_t());

	return errorMap;
}

std::unique_ptr<ErrorMap_t> AbstractTeachingLesson::getErrormapFromOutputVector(NeuralNetworkIO<float>& outputVector, NeuralNetwork &neuralNetwork)
{
	// Get the teachingInput
	NeuralNetworkIO<float>* teachingInput = getTeachingInput(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction());

	// Create the errorMap
	std::unique_ptr<ErrorMap_t> errorMap(new ErrorMap_t());

	// Calculate the error values (expected value - real value)
	for (NeuralNetworkIO<float>::iterator teachingInputValue = teachingInput->begin(); teachingInputValue != teachingInput->end(); teachingInputValue++)
	{
		if (outputVector.count(teachingInputValue->first) != 0)
		{
			for (int i = 0; i < teachingInputValue->second.size(); i++)
			{
				(*errorMap)[teachingInputValue->first][static_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[i])] = teachingInputValue->second[i] - outputVector.at(teachingInputValue->first)[i];
			}
		}
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
	std::unique_ptr<ErrorMap_t> errorMap = getErrormap(neuralNetwork, activationOrder, 0, getMaxTimeStep() + 1);

	float specificError = 0;

	for (ErrorMap_t::iterator errorValues = errorMap->begin(); errorValues != errorMap->end(); errorValues++)
	{
		// Add the square of every errorValue in the errorVector
		for (std::map<StandardNeuron*, float>::iterator errorValue = errorValues->second.begin(); errorValue != errorValues->second.end(); errorValue++)
		{
			specificError += pow(errorValue->second, 2);
		}

		// Divide the specific error by two
		specificError /= 2;
	}
	
	return specificError;
}

std::unique_ptr<ErrorMap_t> AbstractTeachingLesson::getTeachingInputMap(NeuralNetwork &neuralNetwork)
{
	std::unique_ptr<ErrorMap_t> teachingInputMap(new ErrorMap_t());
	NeuralNetworkIO<float>* teachingInput = getTeachingInput(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction());
	for (NeuralNetworkIO<float>::iterator teachingInputsInTimeStep = teachingInput->begin(); teachingInputsInTimeStep != teachingInput->end(); teachingInputsInTimeStep++)
	{
		(*teachingInputMap)[teachingInputsInTimeStep->first] = std::map<StandardNeuron*, float>();
		std::vector<float>::iterator teachingInputValue = teachingInputsInTimeStep->second.begin();
		for (std::vector<StandardNeuron*>::iterator outputNeuron = neuralNetwork.getNetworkTopology()->getOutputNeurons()->begin(); outputNeuron != neuralNetwork.getNetworkTopology()->getOutputNeurons()->end() && teachingInputValue != teachingInputsInTimeStep->second.end(); outputNeuron++, teachingInputValue++)
		{
			(*teachingInputMap)[teachingInputsInTimeStep->first][*outputNeuron] = *teachingInputValue;
		}
	}

	return  teachingInputMap;
}