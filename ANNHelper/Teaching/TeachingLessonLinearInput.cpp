#include "Teaching\TeachingLessonLinearInput.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"

TeachingLessonLinearInput::TeachingLessonLinearInput(NeuralNetworkIO<float>* teachingPattern_, NeuralNetworkIO<float>* teachingInput_)
{
	// Check if all given options are correct
	if (!teachingPattern_)
		throw std::invalid_argument("The given teachingPattern is not valid");
	if (!teachingInput_)
		throw std::invalid_argument("The given teachingInput is not valid");

	teachingInput = std::unique_ptr<NeuralNetworkIO<float>>(teachingInput_);
	teachingPattern = std::unique_ptr<NeuralNetworkIO<float>>(teachingPattern_);
}

NeuralNetworkIO<float>* TeachingLessonLinearInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	return teachingInput.get();
}

NeuralNetworkIO<float>* TeachingLessonLinearInput::getTeachingPattern()
{
	return teachingPattern.get();
}

AbstractTeachingLesson* TeachingLessonLinearInput::unfold()
{
	// Create a new teaching input
	NeuralNetworkIO<float>* unfoldedTeachingInput = new NeuralNetworkIO<float>();
	// Copy the teaching input
	(*unfoldedTeachingInput)[0] = teachingInput->rbegin()->second;
	// Create new teaching lesson with the unfolded teaching pattern and the just created unfolded teaching input
	TeachingLessonLinearInput* unfoldedTeachingLesson = new TeachingLessonLinearInput(teachingPattern->unfold(), unfoldedTeachingInput);
	return unfoldedTeachingLesson;
}

int TeachingLessonLinearInput::getMaxTimeStep()
{
	return teachingInput->rbegin()->first;
}