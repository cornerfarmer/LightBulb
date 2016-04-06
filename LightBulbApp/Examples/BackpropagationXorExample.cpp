#include "BackpropagationXorExample.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Learning/BackpropagationLearningRule.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <Function/FermiFunction.hpp>
#include <Neuron/NeuronDescription.hpp>


void BackpropagationXorExample::initializeLearningRate()
{
	BackpropagationLearningRuleOptions options;
	options.maxTotalErrorValue = 4;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.001f;
	options.maxTries = 1000;
	options.weightDecayFac = 0;
	options.learningRate = 0.1;
	options.momentum = 0;
	options.resilientLearningRate = false;
	options.logger = logger;
	learningRule.reset(new BackpropagationLearningRule(options));

	teacher.reset(new Teacher());
	for (int i = 0; i < 2; i += 1)
	{
		for (int l = 0; l < 2; l += 1)
		{
			std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(2));
			NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);

			teachingPattern[0][0] = i;
			teachingPattern[0][1] = l;
			(*teachingInput).set(0, 0, (i != l));
			teacher->addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
		}
	}

}

void BackpropagationXorExample::run(bool initial)
{
	if (initial)
	{
		initializeLearningRate();
		bool success = learningRule->start(*network, *teacher);
	} 
	else
	{
		learningRule->resume();
	}

	if (isPausing())
		pausingFinished();
	else
		finished();
}

AbstractNeuralNetwork* BackpropagationXorExample::createNeuralNetwork()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0] = 2;
	layeredNetworkOptions.neuronsPerLayerCount[1] = 2;
	layeredNetworkOptions.neuronsPerLayerCount[2] = 1;

	LayeredNetwork* layeredNetwork = new LayeredNetwork(layeredNetworkOptions);

	return new NeuralNetwork(layeredNetwork);
}

void BackpropagationXorExample::tryToPause()
{
	learningRule->sendPauseRequest();
}

std::string BackpropagationXorExample::getName()
{
	return "Backpropagation xor example";
}

std::string BackpropagationXorExample::getDescription()
{
	return "Trains a network to simulate the xor function!";
}

std::string BackpropagationXorExample::getLearningRateName()
{
	return "Backpropagation";
}

AbstractTrainingPlan* BackpropagationXorExample::getCopy()
{
	return new BackpropagationXorExample();
}

void BackpropagationXorExample::setLogger(AbstractLogger* newLogger)
{
	AbstractTrainingPlan::setLogger(newLogger);
	if (learningRule.get()) {
		learningRule->setLogger(newLogger);
	}
}

int BackpropagationXorExample::getRequiredInputSize()
{
	return 2;
}

int BackpropagationXorExample::getRequiredOutputSize()
{
	return 1;
}
