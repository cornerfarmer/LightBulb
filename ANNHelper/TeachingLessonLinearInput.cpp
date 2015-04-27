#include "TeachingLessonLinearInput.hpp"
#include "NeuralNetwork.hpp"

TeachingLessonLinearInput::TeachingLessonLinearInput(std::vector<float>* teachingPattern_, std::vector<float>* teachingInput_)
{
	teachingInput = std::unique_ptr<std::vector<float>>(teachingInput_);
	teachingPattern = std::unique_ptr<std::vector<float>>(teachingPattern_);
}

std::vector<float>* TeachingLessonLinearInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	return teachingInput.get();
}

std::vector<float>* TeachingLessonLinearInput::getTeachingPattern()
{
	return teachingPattern.get();
}