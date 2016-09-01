#include "gtest/gtest.h"
#include <Mocks/MockActivationFunction.hpp>
#include <NeuralNetwork/NeuralNetworkIO.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/Teacher.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <NetworkTopology/RBFNetwork.hpp>
#include <Teaching/TeachingLessonLinearInput.hpp>
#include <Learning/Supervised/RBFInterpolationLearningRule.hpp>
#include <ClusterAnalysis/KMeansRBFNeuronPlacer.hpp>
#include <Learning/AbstractLearningResult.hpp>

class RBFInterpolationLearningRuleTest : public testing::Test {
public:
	RBFInterpolationLearningRule* rbfInterpolationLearningRule;
	NeuralNetwork* neuralNetwork;
	Teacher* teacher;
	void SetUp() {
		RBFNetwork* rbfNetwork = new RBFNetwork(2, 32, 1);

		neuralNetwork = new NeuralNetwork(rbfNetwork);

		teacher = new Teacher();
		for (int i = 0; i <= 20; i += 1)
		{
			for (int l = 0; l <= 20; l += 1)
			{
				std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(2));
				NeuralNetworkIO<double>* teachingInput = new NeuralNetworkIO<double>(1);

				teachingPattern[0][0] = i;
				teachingPattern[0][1] = l;
				(*teachingInput).set(0, 0, (i > l));

				teacher->addTeachingLesson(new TeachingLessonLinearInput(teachingPattern, teachingInput));
			}
		}
	}
	
	RBFInterpolationLearningRuleOptions getDefaultOptions()
	{
		RBFInterpolationLearningRuleOptions options;
		options.offlineLearning = true;
		options.totalErrorGoal = 6;
		options.maxTotalErrorValue = 10;
		options.maxTries = 1;
		options.neuronPlacer = new KMeansRBFNeuronPlacer();
		options.neuralNetwork = neuralNetwork;
		options.teacher = teacher;
		options.seed = 3;

		return options;
	}

	void assertTrainedNeuralNetwork()
	{
		TopologicalOrder topologicalOrder;

		std::vector<double>* input = new std::vector<double>(2);
		(*input)[0] = 5;
		(*input)[1] = 0;
		std::vector<double>* output = new std::vector<double>(1);

		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(1, (*output)[0], 0.05);

		(*input)[0] = 0;
		(*input)[1] = 5;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(0, (*output)[0], 0.05);

		(*input)[0] = 10;
		(*input)[1] = 7;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(1, (*output)[0], 0.08);

		(*input)[0] = 16;
		(*input)[1] = 20;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(0, (*output)[0], 0.08);
	}

	virtual ~RBFInterpolationLearningRuleTest()
	{
		delete rbfInterpolationLearningRule;
		delete neuralNetwork;
		delete teacher;
	}
};

TEST_F(RBFInterpolationLearningRuleTest, doLearning)
 {
	RBFInterpolationLearningRuleOptions options = getDefaultOptions();

	rbfInterpolationLearningRule = new RBFInterpolationLearningRule(options);

	EXPECT_EQ(true, rbfInterpolationLearningRule->start()->succeeded);

	assertTrainedNeuralNetwork();
}
