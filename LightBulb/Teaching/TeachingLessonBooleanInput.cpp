// Includes
#include "Teaching/TeachingLessonBooleanInput.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
// Library includes
#include <exception>

TeachingLessonBooleanInput::TeachingLessonBooleanInput(std::vector<std::vector<double>> teachingPattern_, NeuralNetworkIO<bool>* teachingInput_, bool calcStrictError_)
{
	teachingInput.reset(teachingInput_);
	teachingPattern = teachingPattern_;
	calcStrictError = calcStrictError_;
	teachingInputLinear = std::unique_ptr<NeuralNetworkIO<double>>(new NeuralNetworkIO<double>(teachingInput_->getDimension()));
}

NeuralNetworkIO<double>* TeachingLessonBooleanInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	// Check if the neuralNetwork has a boolean acitvationFunction in all outputNeurons
	if (!activationFunction->hasAMaxAndMinimum())
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
						teachingInputLinear->set(timestep, i, activationFunction->getMaximum());
					else
						teachingInputLinear->set(timestep, i, activationFunction->getMinimum());
				}
			}
		}
	}

	// Return the vector with double values
	return teachingInputLinear.get();
}

NeuralNetworkIO<bool>* TeachingLessonBooleanInput::getBooleanTeachingInput()
{
	return teachingInput.get();
}

std::vector<std::vector<double>>* TeachingLessonBooleanInput::getTeachingPattern()
{
	return &teachingPattern;
}

std::unique_ptr<ErrorMap_t> TeachingLessonBooleanInput::getErrormapFromOutputVector(std::vector<std::vector<double>>& outputVector, AbstractNeuralNetwork& neuralNetwork)
{
	if (calcStrictError)
		return AbstractTeachingLesson::getErrormapFromOutputVector(outputVector, neuralNetwork);
	else
	{
		// Create the errorMap
		std::unique_ptr<ErrorMap_t> errorMap(new ErrorMap_t(teachingInput->getMaxTimeStep() + 1, Eigen::VectorXd(teachingInput->getDimension())));
		auto activationFunction = neuralNetwork.getNetworkTopology()->getOutputActivationFunction();

		double half = (activationFunction->getMaximum() - activationFunction->getMinimum()) / 2;
		double middle = half + activationFunction->getMinimum();

		// Calculate the error values (expected value - real value)
		for (int timestep = 0; timestep < teachingInput->size(); timestep++)
		{
			(*errorMap)[timestep].setZero();
			if (teachingInput->existsTimestep(timestep))
			{
				for (unsigned int i = 0; i < teachingInput->getDimension(); i++)
				{
					if (teachingInput->exists(timestep, i))
					{
						if (teachingInput->get(timestep, i))
						{
							if (outputVector[timestep][i] > middle + half / 2)
								(*errorMap)[timestep][i] = 0;
							else
								(*errorMap)[timestep][i] = activationFunction->getMaximum() - outputVector[timestep][i];
						}
						else
						{
							if (outputVector[timestep][i] < middle - half / 2)
								(*errorMap)[timestep][i] = 0;
							else
								(*errorMap)[timestep][i] = activationFunction->getMinimum() - outputVector[timestep][i];
						}
					}
				}
			}
		}

		/*auto realMap = AbstractTeachingLesson::getErrormapFromOutputVector(outputVector, neuralNetwork);

		if (*realMap != *errorMap)
		errorMap.release();*/

		return errorMap;
	}
}

AbstractTeachingLesson* TeachingLessonBooleanInput::unfold()
{
	// Create a new teaching input
	NeuralNetworkIO<bool>* unfoldedTeachingInput = new NeuralNetworkIO<bool>(teachingInput->getDimension());
	// Copy the teaching input
	unfoldedTeachingInput->set(0, teachingInput->back().second);
	// Create new teaching lesson with the unfolded teaching pattern and the just created unfolded teaching input
	return new TeachingLessonBooleanInput(unfoldTeachingPattern(), unfoldedTeachingInput);
}

std::vector<std::vector<double>> TeachingLessonBooleanInput::unfoldTeachingPattern()
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

int TeachingLessonBooleanInput::getMaxTimeStep()
{
	return teachingInput->getMaxTimeStep();
}

