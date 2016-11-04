#include "gtest/gtest.h"
#include <Teaching/TeachingLessonLinearInput.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockActivationOrder.hpp>
#include <Mocks/MockFeedForwardNetworkTopology.hpp>
#include <Mocks/MockNetworkTopology.hpp>
#include <Mocks/MockActivationFunction.hpp>
#include <EigenSrc/Dense>
#include "Mocks/MockNeuronDescription.hpp"

using namespace LightBulb;

class TeachingLessonLinearInputTest : public testing::Test {
public:
	TeachingLessonLinearInput* teachingLesson;
	NeuralNetworkIO<double>* teachingInput;
	std::vector<double> teachingPattern;
	MockNeuralNetwork* neuralNetwork;
	MockNetworkTopology* networkTopology;
	MockActivationOrder* activationOrder;
	MockActivationFunction* activationFunction;
	MockNeuronDescription* neuronDescription;
	std::vector<double> neuralNetworkOutput;
	void SetUp() {
		neuralNetwork = new MockNeuralNetwork();
		networkTopology = new MockNetworkTopology();
		activationOrder = new MockActivationOrder();
		neuronDescription = new MockNeuronDescription();
		activationFunction = new MockActivationFunction();
		EXPECT_CALL(*neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(*networkTopology));
		EXPECT_CALL(*networkTopology, getOutputNeuronDescription()).WillRepeatedly(testing::ReturnRef(*neuronDescription));
		EXPECT_CALL(*neuronDescription, getActivationFunction()).WillRepeatedly(testing::ReturnRef(*activationFunction));

		teachingInput = new NeuralNetworkIO<double>(3);
		teachingInput->set(0, 1);
		teachingInput->set(1, 2);
		teachingInput->set(2, 3);
		teachingPattern.resize(2);
		teachingPattern[0] = 9;
		teachingPattern[1] = 8;
		teachingLesson = new TeachingLessonLinearInput(teachingPattern, teachingInput);
	}

	void setUpNeuralNetworkCalculateCall()
	{
		neuralNetworkOutput.resize(3, -1);
		EXPECT_CALL(*neuralNetwork, calculate(teachingPattern, testing::_, testing::Ref(*activationOrder), true)).WillOnce(testing::SetArgReferee<1>(neuralNetworkOutput));
	}

	virtual ~TeachingLessonLinearInputTest()
	{
		delete teachingLesson;
		delete neuralNetwork;
		delete activationOrder;
		delete networkTopology;
	}
};

TEST_F(TeachingLessonLinearInputTest, getTeachingInput)
{
	EXPECT_EQ(*teachingInput, teachingLesson->getTeachingInput(*activationFunction));
}

TEST_F(TeachingLessonLinearInputTest, getTeachingPattern)
{
	EXPECT_EQ(teachingPattern, teachingLesson->getTeachingPattern());
}

TEST_F(TeachingLessonLinearInputTest, tryLesson)
{
	setUpNeuralNetworkCalculateCall();
	auto returnedValue = teachingLesson->tryLesson(*neuralNetwork, *activationOrder);
	EXPECT_EQ(neuralNetworkOutput, returnedValue);
}

TEST_F(TeachingLessonLinearInputTest, getErrormapFromOutputVector)
{
	std::vector<double> output(3, 1);
	Eigen::VectorXd expected(3);
	expected[0] = 0;
	expected[1] = 1;
	expected[2] = 2;
	auto returnedValue = teachingLesson->getErrorVectorFromOutputVector(output, *neuralNetwork);
	EXPECT_EQ(expected, *returnedValue.get());
}

TEST_F(TeachingLessonLinearInputTest, getErrormap)
{
	setUpNeuralNetworkCalculateCall();
	Eigen::VectorXd expected(3);
	expected[0] = 2;
	expected[1] = 3;
	expected[2] = 4;
	auto returnedValue = teachingLesson->getErrorVector(*neuralNetwork, *activationOrder);
	EXPECT_EQ(expected[0], (*returnedValue.get())[0]);
	EXPECT_EQ(expected[1], (*returnedValue.get())[1]);
	EXPECT_EQ(expected[2], (*returnedValue.get())[2]);
}

TEST_F(TeachingLessonLinearInputTest, getSpecificError)
{
	setUpNeuralNetworkCalculateCall();
	auto returnedValue = teachingLesson->getSpecificError(*neuralNetwork, *activationOrder);
	EXPECT_EQ(14.5, returnedValue);
}
