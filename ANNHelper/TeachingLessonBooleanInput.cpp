#include "TeachingLessonBooleanInput.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractActivationFunction.hpp"
#include "NeuralNetworkIO.hpp"
#include <exception>

TeachingLessonBooleanInput::TeachingLessonBooleanInput(NeuralNetworkIO<float>* teachingPattern_, NeuralNetworkIO<bool>* teachingInput_)
{
	teachingInput = std::unique_ptr<NeuralNetworkIO<bool>>(teachingInput_);	
	teachingPattern = std::unique_ptr<NeuralNetworkIO<float>>(teachingPattern_);
	teachingInputLinear = std::unique_ptr<NeuralNetworkIO<float>>(new NeuralNetworkIO<float>());
}

NeuralNetworkIO<float>* TeachingLessonBooleanInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	// Check if the neuralNetwork has a boolean acitvationFunction in all outputNeurons
	if (activationFunction->isLinear())
		throw std::invalid_argument("The activationFunction of the outputNeurons is linear, but your teaching input is boolean.");


		// Go through all  teaching input values
	for (NeuralNetworkIO<bool>::iterator teachingInputAtTime = teachingInput->begin(); teachingInputAtTime != teachingInput->end(); teachingInputAtTime++)
	{
		(*teachingInputLinear)[teachingInputAtTime->first] = std::vector<float>(teachingInputAtTime->second.size());
		// Go through all  teaching input values
		for (int i = 0; i < teachingInputAtTime->second.size(); i++)
		{
			// If the boolean value is true, set the maximum of the activationFunction, else the minimum
			if (teachingInputAtTime->second[i])
				(*teachingInputLinear)[teachingInputAtTime->first][i] = activationFunction->getMaximum();
			else
				(*teachingInputLinear)[teachingInputAtTime->first][i] = activationFunction->getMinimum();
		}
	}

	// Return the vector with float values
	return teachingInputLinear.get();
}

NeuralNetworkIO<float>* TeachingLessonBooleanInput::getTeachingPattern()
{
	return teachingPattern.get();
}

AbstractTeachingLesson* TeachingLessonBooleanInput::unfold()
{
	NeuralNetworkIO<bool>* unfoldedTeachingInput = new NeuralNetworkIO<bool>();
	(*unfoldedTeachingInput)[0] = teachingInput->rbegin()->second;
	TeachingLessonBooleanInput* unfoldedTeachingLesson = new TeachingLessonBooleanInput(teachingPattern->unfold(), unfoldedTeachingInput);
	return unfoldedTeachingLesson;
}

int TeachingLessonBooleanInput::getMaxTimeStep()
{
	return teachingInput->rbegin()->first;
}