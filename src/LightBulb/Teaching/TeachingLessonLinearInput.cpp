// Includes
#include "LightBulb/Teaching/TeachingLessonLinearInput.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

namespace LightBulb
{

	TeachingLessonLinearInput::TeachingLessonLinearInput(Vector<>* teachingPattern_, TeachingInput<>* teachingInput_)
	{
		teachingInput.reset(teachingInput_);
		teachingPattern.reset(teachingPattern_);
	}

	TeachingLessonLinearInput::TeachingLessonLinearInput(const std::shared_ptr<Vector<>>& teachingPattern_, const std::shared_ptr<TeachingInput<>>& teachingInput_)
	{
		teachingPattern = teachingPattern_;
		teachingInput = teachingInput_;
	}

	const TeachingInput<>& TeachingLessonLinearInput::getTeachingInput(const AbstractActivationFunction& activationFunction) const
	{
		return *teachingInput.get();
	}

	const Vector<>& TeachingLessonLinearInput::getTeachingPattern() const
	{
		return *teachingPattern.get();
	}

}