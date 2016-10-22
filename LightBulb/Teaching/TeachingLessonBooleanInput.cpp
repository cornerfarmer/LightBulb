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
	TeachingLessonBooleanInput::TeachingLessonBooleanInput(std::vector<std::vector<double>> teachingPattern_, NeuralNetworkIO<bool>* teachingInput_)
	{
		teachingInput.reset(teachingInput_);
		teachingPattern = teachingPattern_;
		teachingInputLinear = std::unique_ptr<NeuralNetworkIO<double>>(new NeuralNetworkIO<double>(teachingInput_->getDimension()));
	}

	const NeuralNetworkIO<double>& TeachingLessonBooleanInput::getTeachingInput(const AbstractActivationFunction& activationFunction) const
	{
		// Check if the neuralNetwork has a boolean acitvationFunction in all outputNeurons
		if (!activationFunction.hasAMaxAndMinimum())
			throw std::invalid_argument("The activationFunction of the outputNeurons is linear, but your teaching input is boolean.");


		// Go through all  teaching input values
		for (int timestep = 0; timestep < teachingInput->size(); timestep++)
		{
			if (teachingInput->existsTimestep(timestep))
			{
				// Go through all  teaching input values
				for (unsigned int i = 0; i < teachingInput->getDimension(); i++)
				{
					if (teachingInput->exists(timestep, i))
					{
						// If the boolean value is true, set the maximum of the activationFunction, else the minimum
						if (teachingInput->get(timestep, i))
							teachingInputLinear->set(timestep, i, activationFunction.getMaximum());
						else
							teachingInputLinear->set(timestep, i, activationFunction.getMinimum());
					}
				}
			}
		}

		// Return the vector with double values
		return *teachingInputLinear.get();
	}

	NeuralNetworkIO<bool>& TeachingLessonBooleanInput::getBooleanTeachingInput() const
	{
		return *teachingInput.get();
	}

	const std::vector<std::vector<double>>& TeachingLessonBooleanInput::getTeachingPattern() const
	{
		return teachingPattern;
	}
	
	AbstractTeachingLesson* TeachingLessonBooleanInput::unfold() const
	{
		// Create a new teaching input
		NeuralNetworkIO<bool>* unfoldedTeachingInput = new NeuralNetworkIO<bool>(teachingInput->getDimension());
		// Copy the teaching input
		unfoldedTeachingInput->set(0, teachingInput->back().second);
		// Create new teaching lesson with the unfolded teaching pattern and the just created unfolded teaching input
		return new TeachingLessonBooleanInput(unfoldTeachingPattern(), unfoldedTeachingInput);
	}

	std::vector<std::vector<double>> TeachingLessonBooleanInput::unfoldTeachingPattern() const
	{
		std::vector<std::vector<double>> unfoldededTeachingPattern(1);
		for (int t = 0; t < teachingPattern.size(); t++)
		{
			for (int i = 0; i < teachingPattern[t].size(); i++)
			{
				unfoldededTeachingPattern[0].push_back(teachingPattern[t][i]);
			}
		}
		return unfoldededTeachingPattern;
	}

	int TeachingLessonBooleanInput::getMaxTimeStep() const
	{
		return teachingInput->getMaxTimeStep();
	}

}