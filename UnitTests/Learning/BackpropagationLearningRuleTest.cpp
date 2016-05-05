#include "gtest/gtest.h"
#include <Learning/BackpropagationLearningRule.hpp>
#include <Mocks/MockActivationOrder.hpp>
#include <Mocks/MockActivationFunction.hpp>
#include <NeuralNetwork/NeuralNetworkIO.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Function/FermiFunction.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>

class BackpropagationLearningRuleTest : public testing::Test {
public:
	BackpropagationLearningRule* backpropagationLearningRule;
	NeuralNetwork* neuralNetwork;
	Teacher* teacher;
	void SetUp() {
		LayeredNetworkOptions layeredNetworkOptions;
		layeredNetworkOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
		layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
		layeredNetworkOptions.neuronsPerLayerCount[0] = 2;
		layeredNetworkOptions.neuronsPerLayerCount[1] = 2;
		layeredNetworkOptions.neuronsPerLayerCount[2] = 1;

		LayeredNetwork* layeredNetwork = new LayeredNetwork(layeredNetworkOptions);

		neuralNetwork = new NeuralNetwork(layeredNetwork);

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
	
	BackpropagationLearningRuleOptions getDefaultOptions()
	{
		BackpropagationLearningRuleOptions options;
		options.maxIterationsPerTry = 1000000;
		options.totalErrorGoal = 0.001f;
		options.learningRate = 0.1;

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
		EXPECT_NEAR(1, (*output)[0], 0.03);

		(*input)[0] = 1;
		(*input)[1] = 1;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(0, (*output)[0], 0.03);

		(*input)[0] = 0;
		(*input)[1] = 1;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(1, (*output)[0], 0.03);

		(*input)[0] = 0;
		(*input)[1] = 0;
		neuralNetwork->calculate(*input, *output, topologicalOrder);
		EXPECT_NEAR(0, (*output)[0], 0.03);
	}

	virtual ~BackpropagationLearningRuleTest()
	{
		delete backpropagationLearningRule;
		delete neuralNetwork;
		delete teacher;
	}
};

TEST_F(BackpropagationLearningRuleTest, doLearning)
{
	BackpropagationLearningRuleOptions options = getDefaultOptions();
	options.weightDecayFac = 0;
	options.momentum = false;
	options.resilientLearningRate = false;
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;

	backpropagationLearningRule = new BackpropagationLearningRule(options);

	EXPECT_EQ(true, backpropagationLearningRule->start());

	assertTrainedNeuralNetwork();
}

TEST_F(BackpropagationLearningRuleTest, doLearningWithResilientLearningRate)
{
	BackpropagationLearningRuleOptions options = getDefaultOptions();
	options.maxIterationsPerTry = 1000;
	options.weightDecayFac = 0;
	options.momentum = false;
	options.resilientLearningRate = true;
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;

	backpropagationLearningRule = new BackpropagationLearningRule(options);

	EXPECT_EQ(true, backpropagationLearningRule->start());

	assertTrainedNeuralNetwork();
}

TEST_F(BackpropagationLearningRuleTest, doLearningWithMomentum)
{
	srand(1);
	BackpropagationLearningRuleOptions options = getDefaultOptions();
	options.maxIterationsPerTry = 1000;
	options.weightDecayFac = 0;
	options.momentum = 0.7;
	options.resilientLearningRate = true;
	options.neuralNetwork = neuralNetwork;
	options.teacher = teacher;

	backpropagationLearningRule = new BackpropagationLearningRule(options);

	EXPECT_EQ(true, backpropagationLearningRule->start());

	assertTrainedNeuralNetwork();
}