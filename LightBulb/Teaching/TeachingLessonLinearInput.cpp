// Includes
#include "Teaching/TeachingLessonLinearInput.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"



TeachingLessonLinearInput::TeachingLessonLinearInput(std::vector<std::vector<double>> teachingPattern_, NeuralNetworkIO<double>* teachingInput_)
{
	teachingInput.reset(teachingInput_);
	teachingPattern = teachingPattern_;
}

NeuralNetworkIO<double>* TeachingLessonLinearInput::getTeachingInput(AbstractActivationFunction* activationFunction)
{
	return teachingInput.get();
}

std::vector<std::vector<double>>* TeachingLessonLinearInput::getTeachingPattern()
{
	return &teachingPattern;
}

AbstractTeachingLesson* TeachingLessonLinearInput::unfold()
{
	// Create a new teaching input
	NeuralNetworkIO<double>* unfoldedTeachingInput = new NeuralNetworkIO<double>(teachingInput->getDimension());
	// Copy the teaching input
	unfoldedTeachingInput->set(0, teachingInput->back().second);
	// Create new teaching lesson with the unfolded teaching pattern and the just created unfolded teaching input
	return new TeachingLessonLinearInput(unfoldTeachingPattern(), unfoldedTeachingInput);
}

std::vector<std::vector<double>> TeachingLessonLinearInput::unfoldTeachingPattern()
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

int TeachingLessonLinearInput::getMaxTimeStep()
{
	return teachingInput->getMaxTimeStep();
}

