#include "TeachingLessonLinearInput.hpp"
#include "NeuralNetworkIO.hpp"
#include "NeuralNetwork.hpp"

TeachingLessonLinearInput::TeachingLessonLinearInput(NeuralNetworkIO<float>* teachingPattern_, NeuralNetworkIO<float>* teachingInput_)
{
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
	NeuralNetworkIO<float>* unfoldedTeachingInput = new NeuralNetworkIO<float>();
	(*unfoldedTeachingInput)[0] = teachingInput->rbegin()->second;
	TeachingLessonLinearInput* unfoldedTeachingLesson = new TeachingLessonLinearInput(teachingPattern->unfold(), unfoldedTeachingInput);
	return unfoldedTeachingLesson;
}

int TeachingLessonLinearInput::getMaxTimeStep()
{
	return teachingInput->rbegin()->first;
}