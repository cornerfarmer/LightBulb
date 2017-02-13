// Includes
#include "LightBulb/Teaching/TeachingLessonBooleanInput.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
// Library includes
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	TeachingLessonBooleanInput::TeachingLessonBooleanInput(Vector<>* teachingPattern_, TeachingInput<char>* teachingInput_)
	{
		teachingInput.reset(teachingInput_);
		teachingPattern.reset(teachingPattern_);
		teachingInputLinear.reset(new TeachingInput<>(teachingInput_->getValues().getEigenValue().size()));
	}

	const TeachingInput<>& TeachingLessonBooleanInput::getTeachingInput(const AbstractActivationFunction& activationFunction) const
	{
		// Check if the neuralNetwork has a boolean acitvationFunction in all outputNeurons
		if (!activationFunction.hasAMaxAndMinimum())
			throw std::invalid_argument("The activationFunction of the outputNeurons is linear, but your teaching input is boolean.");


		// Go through all  teaching input values
		for (unsigned int i = 0; i < teachingInput->getValues().getEigenValue().size(); i++)
		{
			if (teachingInput->exists(i))
			{
				// If the boolean value is true, set the maximum of the activationFunction, else the minimum
				if (teachingInput->get(i))
					teachingInputLinear->set(i, activationFunction.getMaximum());
				else
					teachingInputLinear->set(i, activationFunction.getMinimum());
			}
		}

		// Return the vector with double values
		return *teachingInputLinear.get();
	}

	TeachingInput<char>& TeachingLessonBooleanInput::getBooleanTeachingInput() const
	{
		return *teachingInput.get();
	}

	const Vector<>& TeachingLessonBooleanInput::getTeachingPattern() const
	{
		return *teachingPattern.get();
	}
	
}