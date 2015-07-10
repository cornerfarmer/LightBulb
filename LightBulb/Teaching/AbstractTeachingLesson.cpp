// Includes
#include "Teaching\AbstractTeachingLesson.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"

std::unique_ptr<NeuralNetworkIO<double>> AbstractTeachingLesson::tryLesson(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime)
{
	// Let the network calculate
	return neuralNetwork.calculate(*getTeachingPattern(), activationOrder, startTime, timeStepCount, outputValuesInTime, netInputValuesInTime);
}

std::unique_ptr<ErrorMap_t> AbstractTeachingLesson::getErrormap(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime)
{
	std::unique_ptr<ErrorMap_t> errorMap;

	if (timeStepCount != -1)
	{
		// Try the lesson and extract the output
		std::unique_ptr<NeuralNetworkIO<double>> outputVector = tryLesson(neuralNetwork, activationOrder, startTime, timeStepCount, outputValuesInTime, netInputValuesInTime);
		errorMap = getErrormapFromOutputVector(*outputVector, neuralNetwork);
	}
	else
		errorMap.reset(new ErrorMap_t());

	return errorMap;
}

std::unique_ptr<ErrorMap_t> AbstractTeachingLesson::getErrormapFromOutputVector(NeuralNetworkIO<double>& outputVector, NeuralNetwork &neuralNetwork)
{
	// Get the teachingInput
	NeuralNetworkIO<double>* teachingInput = getTeachingInput(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction());

	// Create the errorMap
	std::unique_ptr<ErrorMap_t> errorMap(new ErrorMap_t());

	// Calculate the error values (expected value - real value)
	for (auto teachingInputValue = teachingInput->begin(); teachingInputValue != teachingInput->end(); teachingInputValue++)
	{
		if (outputVector.count(teachingInputValue->first) != 0)
		{
			for (unsigned int i = 0; i < teachingInputValue->second.size(); i++)
			{
				(*errorMap)[teachingInputValue->first][static_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[i])] = teachingInputValue->second[i] - outputVector.at(teachingInputValue->first)[i];
			}
		}
	}

	return errorMap;
}

double AbstractTeachingLesson::getEuclidienDistance(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	return 0;
}

double AbstractTeachingLesson::getRMS(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	return 0;
}

double AbstractTeachingLesson::getSpecificError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	// Calculate the errorVector
	std::unique_ptr<ErrorMap_t> errorMap = getErrormap(neuralNetwork, activationOrder, 0, getMaxTimeStep() + 1);

	double specificError = 0;

	for (auto errorValues = errorMap->begin(); errorValues != errorMap->end(); errorValues++)
	{
		// Add the square of every errorValue in the errorVector
		for (auto errorValue = errorValues->second.begin(); errorValue != errorValues->second.end(); errorValue++)
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
	NeuralNetworkIO<double>* teachingInput = getTeachingInput(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction());
	for (auto teachingInputsInTimeStep = teachingInput->begin(); teachingInputsInTimeStep != teachingInput->end(); teachingInputsInTimeStep++)
	{
		(*teachingInputMap)[teachingInputsInTimeStep->first] = std::map<StandardNeuron*, double>();
		std::vector<double>::iterator teachingInputValue = teachingInputsInTimeStep->second.begin();
		for (auto outputNeuron = neuralNetwork.getNetworkTopology()->getOutputNeurons()->begin(); outputNeuron != neuralNetwork.getNetworkTopology()->getOutputNeurons()->end() && teachingInputValue != teachingInputsInTimeStep->second.end(); outputNeuron++, teachingInputValue++)
		{
			(*teachingInputMap)[teachingInputsInTimeStep->first][*outputNeuron] = *teachingInputValue;
		}
	}

	return  teachingInputMap;
}