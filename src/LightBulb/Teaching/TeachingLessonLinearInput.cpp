// Includes
#include "LightBulb/Teaching/TeachingLessonLinearInput.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

namespace LightBulb
{

	TeachingLessonLinearInput::TeachingLessonLinearInput(std::vector<double> teachingPattern_, TeachingInput<double>* teachingInput_)
	{
		teachingInput.reset(teachingInput_);
		teachingPattern = teachingPattern_;
	}

	const TeachingInput<double>& TeachingLessonLinearInput::getTeachingInput(const AbstractActivationFunction& activationFunction) const
	{
		return *teachingInput.get();
	}

	const std::vector<double>& TeachingLessonLinearInput::getTeachingPattern() const
	{
		return teachingPattern;
	}

}