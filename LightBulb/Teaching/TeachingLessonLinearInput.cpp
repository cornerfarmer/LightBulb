// Includes
#include "Teaching/TeachingLessonLinearInput.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

TeachingLessonLinearInput::TeachingLessonLinearInput(NeuralNetworkIO<double>* teachingPattern_, NeuralNetworkIO<double>* teachingInput_)
{
	// Check if all given options are correct
	if (!teachingPattern_)
		throw std::invalid_argument("The given teachingPattern is not valid");
	if (!teachingInput_)
		throw std::invalid_argument("The given teachingInput is not valid");

	teachingInput = std::unique_ptr<NeuralNetworkIO<double>>(teachingInput_);
	teachingPattern = std::unique_ptr<NeuralNetworkIO<double>>(teachingPattern_);
}

NeuralNetworkIO<double>* TeachingLessonLinearInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	return teachingInput.get();
}

NeuralNetworkIO<double>* TeachingLessonLinearInput::getTeachingPattern()
{
	return teachingPattern.get();
}

AbstractTeachingLesson* TeachingLessonLinearInput::unfold()
{
	// Create a new teaching input
	NeuralNetworkIO<double>* unfoldedTeachingInput = new NeuralNetworkIO<double>(teachingInput->getDimension());
	// Copy the teaching input
	(*unfoldedTeachingInput).set(0, teachingInput->rbegin()->second);
	// Create new teaching lesson with the unfolded teaching pattern and the just created unfolded teaching input
	TeachingLessonLinearInput* unfoldedTeachingLesson = new TeachingLessonLinearInput(teachingPattern->unfold(), unfoldedTeachingInput);
	return unfoldedTeachingLesson;
}

int TeachingLessonLinearInput::getMaxTimeStep()
{
	return teachingInput->getMaxTimeStep();
}