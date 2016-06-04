#include "TCProblemBackpropagationExample.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Learning/BackpropagationLearningRule.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <Function/FermiFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <TrainingPlans/DoublePreference.hpp>

#define PREFERENCE_LEARNINGRATE "Learning rate"
#define PREFERENCE_MOMENTUM "Momentum"

TCProblemBackpropagationExample::TCProblemBackpropagationExample()
{
	addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE, 0.1, 0.0001, 2));
	addPreference(new DoublePreference(PREFERENCE_MOMENTUM, 0, 0, 1));
}

AbstractLearningRule* TCProblemBackpropagationExample::createLearningRate()
{
	teacher.reset(new TCProblemTeacher());

	BackpropagationLearningRuleOptions options;
	options.maxTotalErrorValue = 4;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.001f;
	options.maxTries = 1000;
	options.weightDecayFac = 0;
	options.learningRate = getDoublePreference(PREFERENCE_LEARNINGRATE);
	options.momentum = getDoublePreference(PREFERENCE_MOMENTUM);
	options.resilientLearningRate = false;
	options.teacher = teacher.get();
	fillDefaultLearningRuleOptions(&options);

	return new BackpropagationLearningRule(options);
}


AbstractNeuralNetwork* TCProblemBackpropagationExample::createNeuralNetwork()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0] = 16;
	layeredNetworkOptions.neuronsPerLayerCount[1] = 16;
	layeredNetworkOptions.neuronsPerLayerCount[2] = 1;

	LayeredNetwork* layeredNetwork = new LayeredNetwork(layeredNetworkOptions);

	return new NeuralNetwork(layeredNetwork);
}


std::string TCProblemBackpropagationExample::getDefaultName()
{
	return "TC-problem backpropagation example";
}

std::string TCProblemBackpropagationExample::getDescription()
{
	return "Teaches a network how to distinguish Ts and Cs with the help of backpropagation.";
}


AbstractTrainingPlan* TCProblemBackpropagationExample::getCopy()
{
	return new TCProblemBackpropagationExample();
}

int TCProblemBackpropagationExample::getRequiredInputSize()
{
	return 16;
}

int TCProblemBackpropagationExample::getRequiredOutputSize()
{
	return 1;
}

std::string TCProblemBackpropagationExample::getLearningRuleName()
{
	return BackpropagationLearningRule::getName();
}
