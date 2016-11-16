#include "TCProblemBackpropagationExample.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Learning/Supervised/GradientDescentLearningRule.hpp>
#include <NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <Function/ActivationFunction/FermiFunction.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <TrainingPlans/Preferences/DoublePreference.hpp>
#include "Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"

using namespace LightBulb;

#define PREFERENCE_LEARNINGRATE "Learning rate"
#define PREFERENCE_MOMENTUM "Momentum"

TCProblemBackpropagationExample::TCProblemBackpropagationExample()
{
	addPreference(new DoublePreference(PREFERENCE_LEARNINGRATE, 0.1, 0.0001, 2));
	addPreference(new DoublePreference(PREFERENCE_MOMENTUM, 0, 0, 1));
}

AbstractLearningRule* TCProblemBackpropagationExample::createLearningRate()
{
	teacher.reset(new TCProblemTeacher(true));

	SimpleGradientDescentOptions gradientDescentOptions;
	gradientDescentOptions.learningRate = getDoublePreference(PREFERENCE_LEARNINGRATE);
	gradientDescentOptions.momentum = getDoublePreference(PREFERENCE_MOMENTUM);

	GradientDescentLearningRuleOptions options;
	options.maxTotalErrorValue = 4;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.001f;
	options.maxTries = 1000;
	options.gradientDescentAlgorithm = new SimpleGradientDescent(gradientDescentOptions);
	options.teacher = teacher.get();
	fillDefaultLearningRuleOptions(options);

	return new GradientDescentLearningRule(options);
}


AbstractNeuralNetwork* TCProblemBackpropagationExample::createNeuralNetwork()
{
	FeedForwardNetworkTopologyOptions networkTopologyOptions;
	networkTopologyOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	networkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	networkTopologyOptions.neuronsPerLayerCount[0] = 16;
	networkTopologyOptions.neuronsPerLayerCount[1] = 16;
	networkTopologyOptions.neuronsPerLayerCount[2] = 1;

	FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(networkTopologyOptions);

	return new NeuralNetwork(networkTopology);
}


std::string TCProblemBackpropagationExample::getOriginalName() const
{
	return "TC-problem backpropagation example";
}

std::string TCProblemBackpropagationExample::getDescription() const
{
	return "Teaches a network how to distinguish Ts and Cs with the help of backpropagation.";
}


AbstractTrainingPlan* TCProblemBackpropagationExample::createNewFromSameType() const
{
	return new TCProblemBackpropagationExample();
}

std::string TCProblemBackpropagationExample::getLearningRuleName() const
{
	return GradientDescentLearningRule::getName();
}
