// Includes
#include "Teaching/TeachingLessonBooleanInput.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
// Library includes
#include <exception>
#include "NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	TeachingLessonBooleanInput::TeachingLessonBooleanInput(std::vector<double> teachingPattern_, NeuralNetworkIO<bool>* teachingInput_)
	{
		teachingInput.reset(teachingInput_);
		teachingPattern = teachingPattern_;
		teachingInputLinear.reset(new NeuralNetworkIO<double>(teachingInput_->getDimension()));
	}

	const NeuralNetworkIO<double>& TeachingLessonBooleanInput::getTeachingInput(const AbstractActivationFunction& activationFunction) const
	{
		// Check if the neuralNetwork has a boolean acitvationFunction in all outputNeurons
		if (!activationFunction.hasAMaxAndMinimum())
			throw std::invalid_argument("The activationFunction of the outputNeurons is linear, but your teaching input is boolean.");


		// Go through all  teaching input values
		for (unsigned int i = 0; i < teachingInput->getDimension(); i++)
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

	NeuralNetworkIO<bool>& TeachingLessonBooleanInput::getBooleanTeachingInput() const
	{
		return *teachingInput.get();
	}

	const std::vector<double>& TeachingLessonBooleanInput::getTeachingPattern() const
	{
		return teachingPattern;
	}
	
}