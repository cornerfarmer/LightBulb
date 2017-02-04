#include "LightBulbExamplePrec.hpp"
#include "BackpropagationXorExample.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "LightBulb/Teaching/TeachingInput.hpp"
#include "LightBulb/Teaching/TeachingLessonBooleanInput.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/ResilientLearningRate.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/FeedForwardNetworkTopologyPreferenceGroup.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentLearningRule.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentLearningRulePreferenceGroup.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

using namespace LightBulb;

BackpropagationXorExample::BackpropagationXorExample()
{
	FeedForwardNetworkTopologyOptions networkTopologyOptions;
	networkTopologyOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	networkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	networkTopologyOptions.neuronsPerLayerCount[0] = 2;
	networkTopologyOptions.neuronsPerLayerCount[1] = 3;
	networkTopologyOptions.neuronsPerLayerCount[2] = 1;
	addPreferenceGroup(new FeedForwardNetworkTopologyPreferenceGroup(networkTopologyOptions));

	GradientDescentLearningRuleOptions options;
	options.maxTotalErrorValue = 4;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.001f;
	options.maxTries = 1000;
	SimpleGradientDescentOptions simpleGradientDescentOptions;
	simpleGradientDescentOptions.learningRate = 0.12345;
	ResilientLearningRateOptions resilientLearningRateOptions;
	addPreferenceGroup(new GradientDescentLearningRulePreferenceGroup(options, simpleGradientDescentOptions, resilientLearningRateOptions));
}

AbstractLearningRule* BackpropagationXorExample::createLearningRate()
{
	teacher.reset(new Teacher());
	for (int i = 0; i < 2; i += 1)
	{
		for (int l = 0; l < 2; l += 1)
		{
			std::vector<double> teachingPattern(2);
			TeachingInput<bool>* teachingInput = new TeachingInput<bool>(1);

			teachingPattern[0] = i;
			teachingPattern[1] = l;
			(*teachingInput).set(0, (i != l));
			teacher->addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
		}
	}
	
	GradientDescentLearningRuleOptions options = createOptions<GradientDescentLearningRuleOptions, GradientDescentLearningRulePreferenceGroup>();
	options.teacher = teacher.get();
	fillDefaultLearningRuleOptions(options);

	return new GradientDescentLearningRule(options);
}


AbstractNeuralNetwork* BackpropagationXorExample::createNeuralNetwork()
{
	FeedForwardNetworkTopologyOptions options = createOptions<FeedForwardNetworkTopologyOptions, FeedForwardNetworkTopologyPreferenceGroup>();
	FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

	return new NeuralNetwork(networkTopology);
}


std::string BackpropagationXorExample::getOriginalName() const
{
	return "Backpropagation xor example";
}

std::string BackpropagationXorExample::getDescription() const
{
	return "Trains a network to simulate the xor function!";
}


LightBulb::AbstractTrainingPlan* BackpropagationXorExample::createNewFromSameType() const
{
	return new BackpropagationXorExample();
}


std::string BackpropagationXorExample::getLearningRuleName() const
{
	return GradientDescentLearningRule::getName();
}
