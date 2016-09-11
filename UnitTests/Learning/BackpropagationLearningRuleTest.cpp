#include "gtest/gtest.h"
#include <Learning/Supervised/GradientDecentLearningRule.hpp>
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
#include "Learning/Supervised/GradientDecentAlgorithms/SimpleGradientDecent.hpp"
#include "Learning/Supervised/GradientDecentAlgorithms/ResilientLearningRate.hpp"

using namespace LightBulb;

class GradientDecentLearningRuleTest : public testing::Test {
public:
	GradientDecentLearningRule* gradientDecentLearningRule;
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
				std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(2));
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);

				teachingPattern[0][0] = i;
				teachingPattern[0][1] = l;
				(*teachingInput).set(0, 0, (i != l));
				teacher->addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
			}
		}
	}
	
	GradientDecentLearningRuleOptions getDefaultOptions()
	{
		GradientDecentLearningRuleOptions options;
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

	virtual ~GradientDecentLearningRuleTest()
	{
		delete gradientDecentLearningRule;
		delete neuralNetwork;
		delete teacher;
	}
};

TEST_F(GradientDecentLearningRuleTest, doLearning)
{
	SimpleGradientDecentOptions gradientDecentOptions;
	gradientDecentOptions.learningRate = 0.1;

	GradientDecentLearningRuleOptions options = getDefaultOptions();
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;
	options.gradientDecentAlgorithm = new SimpleGradientDecent(gradientDecentOptions);

	gradientDecentLearningRule = new GradientDecentLearningRule(options);

	EXPECT_EQ(true, gradientDecentLearningRule->start()->succeeded);

	assertTrainedNeuralNetwork();
}

TEST_F(GradientDecentLearningRuleTest, doLearningWithResilientLearningRate)
{
	ResilientLearningRateOptions resilientLearningRateOptions;

	GradientDecentLearningRuleOptions options = getDefaultOptions();
	options.maxIterationsPerTry = 1000;
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;
	options.offlineLearning = true;
	options.gradientDecentAlgorithm = new ResilientLearningRate(resilientLearningRateOptions);

	gradientDecentLearningRule = new GradientDecentLearningRule(options);

	EXPECT_EQ(true, gradientDecentLearningRule->start()->succeeded);

	assertTrainedNeuralNetwork();
}

TEST_F(GradientDecentLearningRuleTest, doLearningWithMomentum)
{
	SimpleGradientDecentOptions gradientDecentOptions;
	gradientDecentOptions.learningRate = 0.1;
	gradientDecentOptions.momentum = 0.8;

	GradientDecentLearningRuleOptions options = getDefaultOptions();
	options.maxIterationsPerTry = 10000;
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;
	options.gradientDecentAlgorithm = new SimpleGradientDecent(gradientDecentOptions);

	gradientDecentLearningRule = new GradientDecentLearningRule(options);

	EXPECT_EQ(true, gradientDecentLearningRule->start()->succeeded);

	assertTrainedNeuralNetwork();
}