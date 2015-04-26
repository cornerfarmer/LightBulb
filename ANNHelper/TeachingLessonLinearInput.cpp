#include "TeachingLessonLinearInput.hpp"
#include "NeuralNetwork.hpp"

TeachingLessonLinearInput::~TeachingLessonLinearInput()
{
	delete(teachingInput);
	delete(teachingPattern);
}

TeachingLessonLinearInput::TeachingLessonLinearInput(std::vector<float>* teachingPattern_, std::vector<float>* teachingInput_)
{
	teachingInput = teachingInput_;
	teachingPattern = teachingPattern_;
}

std::vector<float>* TeachingLessonLinearInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	return teachingInput;
}

std::vector<float>* TeachingLessonLinearInput::getTeachingPattern()
{
	return teachingPattern;
}