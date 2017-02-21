#include <LightBulb/Teaching/TeachingLessonLinearInput.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockActivationOrder.hpp>
#include <Mocks/MockFeedForwardNetworkTopology.hpp>
#include <Mocks/MockNetworkTopology.hpp>
#include <Mocks/MockActivationFunction.hpp>
#include <Eigen/Dense>
#include "Mocks/MockNeuronDescription.hpp"
#include <LightBulb/Function/InputFunction/AbstractInputFunction.hpp>

using namespace LightBulb;

class TeachingLessonLinearInputTest : public testing::Test {
public:
	TeachingLessonLinearInput* teachingLesson;
	TeachingInput<>* teachingInput;
	Vector<>* teachingPattern;
	MockNeuralNetwork* neuralNetwork;
	MockNetworkTopology* networkTopology;
	MockActivationOrder* activationOrder;
	MockActivationFunction* activationFunction;
	MockNeuronDescription* neuronDescription;
	Vector<> neuralNetworkOutput;
	void SetUp() {
		neuralNetwork = new MockNeuralNetwork();
		networkTopology = new MockNetworkTopology();
		activationOrder = new MockActivationOrder();
		neuronDescription = new MockNeuronDescription();
		activationFunction = new MockActivationFunction();
		EXPECT_CALL(*neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(*networkTopology));
		EXPECT_CALL(*networkTopology, getOutputNeuronDescription()).WillRepeatedly(testing::ReturnRef(*neuronDescription));
		EXPECT_CALL(*neuronDescription, getActivationFunction()).WillRepeatedly(testing::ReturnRef(*activationFunction));

		teachingInput = new TeachingInput<>(3);
		teachingInput->set(0, 1);
		teachingInput->set(1, 2);
		teachingInput->set(2, 3);
		teachingPattern = new Vector<>(2);
		teachingPattern->getEigenValueForEditing()[0] = 9;
		teachingPattern->getEigenValueForEditing()[1] = 8;
		teachingLesson = new TeachingLessonLinearInput(teachingPattern, teachingInput);
	}

	void setUpNeuralNetworkCalculateCall()
	{
		neuralNetworkOutput.getEigenValueForEditing().resize(3);
		neuralNetworkOutput.getEigenValueForEditing()(0) = -1;
		neuralNetworkOutput.getEigenValueForEditing()(1) = -1;
		neuralNetworkOutput.getEigenValueForEditing()(2) = -1;
		EXPECT_CALL(*neuralNetwork, calculateWithoutOutputCopy(testing::Ref(*teachingPattern), testing::Ref(*activationOrder), true)).WillOnce(testing::ReturnRef(neuralNetworkOutput));
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
	EXPECT_EQ(*teachingPattern, teachingLesson->getTeachingPattern());
}

TEST_F(TeachingLessonLinearInputTest, tryLesson)
{
	setUpNeuralNetworkCalculateCall();
	const Vector<>& returnedValue = teachingLesson->tryLesson(*neuralNetwork, *activationOrder);
	EXPECT_EQ(neuralNetworkOutput.getEigenValue().size(), returnedValue.getEigenValue().size());
	EXPECT_EQ(neuralNetworkOutput.getEigenValue()[0], returnedValue.getEigenValue()[0]);
	EXPECT_EQ(neuralNetworkOutput.getEigenValue()[1], returnedValue.getEigenValue()[1]);
	EXPECT_EQ(neuralNetworkOutput.getEigenValue()[2], returnedValue.getEigenValue()[2]);
}

TEST_F(TeachingLessonLinearInputTest, getErrormap)
{
	setUpNeuralNetworkCalculateCall();
	Vector<> expected(3);
	expected.getEigenValueForEditing()[0] = 2;
	expected.getEigenValueForEditing()[1] = 3;
	expected.getEigenValueForEditing()[2] = 4;
	const Vector<>& returnedValue = teachingLesson->getErrorVector(*neuralNetwork, *activationOrder);
	EXPECT_EQ(expected.getEigenValue()[0], returnedValue.getEigenValue()[0]);
	EXPECT_EQ(expected.getEigenValue()[1], returnedValue.getEigenValue()[1]);
	EXPECT_EQ(expected.getEigenValue()[2], returnedValue.getEigenValue()[2]);
}

TEST_F(TeachingLessonLinearInputTest, getSpecificError)
{
	setUpNeuralNetworkCalculateCall();
	auto returnedValue = teachingLesson->getSpecificError(*neuralNetwork, *activationOrder);
	EXPECT_EQ(14.5, returnedValue);
}
