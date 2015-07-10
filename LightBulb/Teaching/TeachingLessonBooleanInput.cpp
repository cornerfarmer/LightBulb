// Includes
#include "Teaching\TeachingLessonBooleanInput.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"
// Library includes
#include <exception>

TeachingLessonBooleanInput::TeachingLessonBooleanInput(NeuralNetworkIO<double>* teachingPattern_, NeuralNetworkIO<bool>* teachingInput_)
{
	// Check if all given options are correct
	if (!teachingPattern_)
		throw std::invalid_argument("The given teachingPattern is not valid");
	if (!teachingInput_)
		throw std::invalid_argument("The given teachingInput is not valid");

	teachingInput = std::unique_ptr<NeuralNetworkIO<bool>>(teachingInput_);	
	teachingPattern = std::unique_ptr<NeuralNetworkIO<double>>(teachingPattern_);
	teachingInputLinear = std::unique_ptr<NeuralNetworkIO<double>>(new NeuralNetworkIO<double>());
}

NeuralNetworkIO<double>* TeachingLessonBooleanInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	// Check if the neuralNetwork has a boolean acitvationFunction in all outputNeurons
	if (!activationFunction->hasAMaxAndMinimum())
		throw std::invalid_argument("The activationFunction of the outputNeurons is linear, but your teaching input is boolean.");


	// Go through all  teaching input values
	for (auto teachingInputAtTime = teachingInput->begin(); teachingInputAtTime != teachingInput->end(); teachingInputAtTime++)
	{
		(*teachingInputLinear)[teachingInputAtTime->first] = std::vector<double>(teachingInputAtTime->second.size());
		// Go through all  teaching input values
		for (unsigned int i = 0; i < teachingInputAtTime->second.size(); i++)
		{
			// If the boolean value is true, set the maximum of the activationFunction, else the minimum
			if (teachingInputAtTime->second[i])
				(*teachingInputLinear)[teachingInputAtTime->first][i] = activationFunction->getMaximum();
			else
				(*teachingInputLinear)[teachingInputAtTime->first][i] = activationFunction->getMinimum();
		}
	}

	// Return the vector with double values
	return teachingInputLinear.get();
}

NeuralNetworkIO<double>* TeachingLessonBooleanInput::getTeachingPattern()
{
	return teachingPattern.get();
}

AbstractTeachingLesson* TeachingLessonBooleanInput::unfold()
{
	// Create a new teaching input
	NeuralNetworkIO<bool>* unfoldedTeachingInput = new NeuralNetworkIO<bool>();
	// Copy the teaching input
	(*unfoldedTeachingInput)[0] = teachingInput->rbegin()->second;
	// Create new teaching lesson with the unfolded teaching pattern and the just created unfolded teaching input
	TeachingLessonBooleanInput* unfoldedTeachingLesson = new TeachingLessonBooleanInput(teachingPattern->unfold(), unfoldedTeachingInput);
	return unfoldedTeachingLesson;
}

int TeachingLessonBooleanInput::getMaxTimeStep()
{
	return teachingInput->rbegin()->first;
}