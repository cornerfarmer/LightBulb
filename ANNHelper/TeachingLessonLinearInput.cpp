#include "TeachingLessonLinearInput.hpp"
#include "NeuralNetworkIO.hpp"
#include "NeuralNetwork.hpp"

TeachingLessonLinearInput::TeachingLessonLinearInput(NeuralNetworkIO* teachingPattern_, std::vector<float>* teachingInput_)
{
	teachingInput = std::unique_ptr<std::vector<float>>(teachingInput_);
	teachingPattern = std::unique_ptr<NeuralNetworkIO>(teachingPattern_);
}

std::vector<float>* TeachingLessonLinearInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	return teachingInput.get();
}

NeuralNetworkIO* TeachingLessonLinearInput::getTeachingPattern()
{
	return teachingPattern.get();
}