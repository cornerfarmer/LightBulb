#include "gtest/gtest.h"
#include <Learning/Supervised/GradientDescentLearningRule.hpp>
#include <Mocks/MockActivationOrder.hpp>
#include <Mocks/MockActivationFunction.hpp>
#include <NeuralNetwork/NeuralNetworkIO.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <Function/ActivationFunction/FermiFunction.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <Learning/AbstractLearningResult.hpp>
#include "Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/ResilientLearningRate.hpp"

using namespace LightBulb;

class GradientDescentLearningRuleTest : public testing::Test {
public:
	GradientDescentLearningRule* gradientDescentLearningRule;
	NeuralNetwork* neuralNetwork;
	Teacher* teacher;
	void SetUp() {
		FeedForwardNetworkTopologyOptions FeedForwardNetworkTopologyOptions;
		FeedForwardNetworkTopologyOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[0] = 2;
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[1] = 2;
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[2] = 1;

		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(FeedForwardNetworkTopologyOptions);

		neuralNetwork = new NeuralNetwork(networkTopology);

		teacher = new Teacher();
		for (int i = 0; i < 2; i += 1)
		{
			for (int l = 0; l < 2; l += 1)
			{
				std::vector<double> teachingPattern(2);
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);

				teachingPattern[0] = i;
				teachingPattern[1] = l;
				(*teachingInput).set(0, (i != l));
				teacher->addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
			}
		}
	}
	
	GradientDescentLearningRuleOptions getDefaultOptions()
	{
		GradientDescentLearningRuleOptions options;
		options.maxIterationsPerTry = 1000000;
		options.totalErrorGoal = 0.001f;
		options.seed = 1;

		return options;
	}

	void assertTrainedNeuralNetwork()
	{
		TopologicalOrder topologicalOrder;

		std::vector<double>* input = new std::vector<double>(2);
		(*input)[0] = 1;
		(*input)[1] = 0;
		std::vector<double>* output = new std::vector<double>(1);

		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(1, (*output)[0], 0.04);

		(*input)[0] = 1;
		(*input)[1] = 1;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(0, (*output)[0], 0.04);

		(*input)[0] = 0;
		(*input)[1] = 1;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(1, (*output)[0], 0.04);

		(*input)[0] = 0;
		(*input)[1] = 0;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(0, (*output)[0], 0.04);
	}

	virtual ~GradientDescentLearningRuleTest()
	{
		delete gradientDescentLearningRule;
		delete neuralNetwork;
		delete teacher;
	}
};

TEST_F(GradientDescentLearningRuleTest, doLearning)
{
	SimpleGradientDescentOptions gradientDescentOptions;
	gradientDescentOptions.learningRate = 0.1;

	GradientDescentLearningRuleOptions options = getDefaultOptions();
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;
	options.gradientDescentAlgorithm = new SimpleGradientDescent(gradientDescentOptions);

	gradientDescentLearningRule = new GradientDescentLearningRule(options);

	EXPECT_EQ(true, gradientDescentLearningRule->start()->succeeded);

	assertTrainedNeuralNetwork();
}

TEST_F(GradientDescentLearningRuleTest, doLearningWithResilientLearningRate)
{
	ResilientLearningRateOptions resilientLearningRateOptions;

	GradientDescentLearningRuleOptions options = getDefaultOptions();
	options.maxIterationsPerTry = 1000;
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;
	options.offlineLearning = true;
	options.gradientDescentAlgorithm = new ResilientLearningRate(resilientLearningRateOptions);

	gradientDescentLearningRule = new GradientDescentLearningRule(options);

	EXPECT_EQ(true, gradientDescentLearningRule->start()->succeeded);

	assertTrainedNeuralNetwork();
}

TEST_F(GradientDescentLearningRuleTest, doLearningWithMomentum)
{
	SimpleGradientDescentOptions gradientDescentOptions;
	gradientDescentOptions.learningRate = 0.1;
	gradientDescentOptions.momentum = 0.8;

	GradientDescentLearningRuleOptions options = getDefaultOptions();
	options.maxIterationsPerTry = 10000;
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;
	options.gradientDescentAlgorithm = new SimpleGradientDescent(gradientDescentOptions);

	gradientDescentLearningRule = new GradientDescentLearningRule(options);

	EXPECT_EQ(true, gradientDescentLearningRule->start()->succeeded);

	assertTrainedNeuralNetwork();
}