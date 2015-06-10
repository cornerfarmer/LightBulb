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
	TeachingLessonLinearInput* unfoldedTeachingLesson = new TeachingLessonLinearInput(teachingPattern->unfold(), new NeuralNetworkIO<float>(*teachingInput));
	return unfoldedTeachingLesson;
}