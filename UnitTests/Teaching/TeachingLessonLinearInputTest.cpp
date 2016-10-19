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
	std::vector<std::vector<double>> teachingPattern;
	MockNeuralNetwork* neuralNetwork;
	MockNetworkTopology* networkTopology;
	MockActivationOrder* activationOrder;
	MockActivationFunction* activationFunction;
	MockNeuronDescription* neuronDescription;
	std::vector<std::vector<double>> neuralNetworkOutput;
	void SetUp() {
		neuralNetwork = new MockNeuralNetwork();
		networkTopology = new MockNetworkTopology();
		activationOrder = new MockActivationOrder();
		neuronDescription = new MockNeuronDescription();
		activationFunction = new MockActivationFunction();
		EXPECT_CALL(*neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::Return(networkTopology));
		EXPECT_CALL(*networkTopology, getOutputNeuronDescription()).WillRepeatedly(testing::Return(neuronDescription));
		EXPECT_CALL(*neuronDescription, getActivationFunction()).WillRepeatedly(testing::Return(activationFunction));

		teachingInput = new NeuralNetworkIO<double>(3);
		teachingInput->set(0, 0, 1);
		teachingInput->set(0, 1, 2);
		teachingInput->set(0, 2, 3);
		teachingInput->set(1, 0, 4);
		teachingInput->set(1, 2, 6);
		teachingInput->set(2, 0, 7);
		teachingInput->set(2, 1, 8);
		teachingInput->set(2, 2, 9);
		teachingPattern.resize(3, std::vector<double>(2));
		teachingPattern[0][0] = 9;
		teachingPattern[0][1] = 8;
		teachingPattern[1][0] = 7;
		teachingPattern[1][1] = 6;
		teachingPattern[2][0] = 5;
		teachingPattern[2][1] = 4;
		teachingLesson = new TeachingLessonLinearInput(teachingPattern, teachingInput);
	}

	void setUpNeuralNetworkCalculateCall()
	{
		neuralNetworkOutput.resize(3, std::vector<double>(3, -1));
		EXPECT_CALL(*neuralNetwork, calculate(teachingPattern, testing::_, testing::Ref(*activationOrder), 0, -1, nullptr, nullptr, testing::_)).WillOnce(testing::SetArgReferee<1>(neuralNetworkOutput));
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
	EXPECT_EQ(teachingInput, teachingLesson->getTeachingInput(nullptr));
}

TEST_F(TeachingLessonLinearInputTest, getTeachingPattern)
{
	EXPECT_EQ(teachingPattern, *teachingLesson->getTeachingPattern());
}

TEST_F(TeachingLessonLinearInputTest, unfold)
{
	std::unique_ptr<AbstractTeachingLesson> unfoldedTeachingLesson(teachingLesson->unfold());

	NeuralNetworkIO<double> expectedTeachingInput(3);
	expectedTeachingInput.set(0, 0, 7);
	expectedTeachingInput.set(0, 1, 8);
	expectedTeachingInput.set(0, 2, 9);
	EXPECT_EQ(*unfoldedTeachingLesson->getTeachingInput(nullptr), expectedTeachingInput);

	std::vector<std::vector<double>> expectedTeachingPattern(1, std::vector<double>(6));
	expectedTeachingPattern[0][0] = 9;
	expectedTeachingPattern[0][1] = 8;
	expectedTeachingPattern[0][2] = 7;
	expectedTeachingPattern[0][3] = 6;
	expectedTeachingPattern[0][4] = 5;
	expectedTeachingPattern[0][5] = 4;
	EXPECT_EQ(expectedTeachingPattern, *unfoldedTeachingLesson->getTeachingPattern());
}

TEST_F(TeachingLessonLinearInputTest, getMaxTimeStep)
{
	EXPECT_EQ(2, teachingLesson->getMaxTimeStep());
}

TEST_F(TeachingLessonLinearInputTest, tryLesson)
{
	setUpNeuralNetworkCalculateCall();
	auto returnedValue = teachingLesson->tryLesson(*neuralNetwork, *activationOrder);
	EXPECT_EQ(neuralNetworkOutput, returnedValue);
}

TEST_F(TeachingLessonLinearInputTest, getErrormapFromOutputVector)
{
	std::vector<std::vector<double>> output(3, std::vector<double>(3, 1));
	ErrorMap_t expected(3, Eigen::VectorXd(3));
	expected[0][0] = 0;
	expected[0][1] = 1;
	expected[0][2] = 2;
	expected[1][0] = 3;
	expected[1][1] = 0;
	expected[1][2] = 5;
	expected[2][0] = 6;
	expected[2][1] = 7;
	expected[2][2] = 8;
	auto returnedValue = teachingLesson->getErrormapFromOutputVector(output, *neuralNetwork);
	EXPECT_EQ(expected, *returnedValue.get());
}

TEST_F(TeachingLessonLinearInputTest, getErrormap)
{
	setUpNeuralNetworkCalculateCall();
	ErrorMap_t expected(3, Eigen::VectorXd(3));
	expected[0][0] = 2;
	expected[0][1] = 3;
	expected[0][2] = 4;
	expected[1][0] = 5;
	expected[1][1] = 0;
	expected[1][2] = 7;
	expected[2][0] = 8;
	expected[2][1] = 9;
	expected[2][2] = 10;
	auto returnedValue = teachingLesson->getErrormap(*neuralNetwork, *activationOrder);
	ASSERT_TRUE(expected[0].isApprox((*returnedValue.get())[0]));
	ASSERT_TRUE(expected[1].isApprox((*returnedValue.get())[1]));
	ASSERT_TRUE(expected[2].isApprox((*returnedValue.get())[2]));
}

TEST_F(TeachingLessonLinearInputTest, getSpecificError)
{
	setUpNeuralNetworkCalculateCall();
	auto returnedValue = teachingLesson->getSpecificError(*neuralNetwork, *activationOrder);
	EXPECT_EQ(174, returnedValue);
}
