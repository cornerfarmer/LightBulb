#include "gtest/gtest.h"
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Mocks/MockActivationOrder.hpp>
#include <Mocks/MockActivationFunction.hpp>

class TeachingLessonBooleanInputTest : public testing::Test {
public:
	TeachingLessonBooleanInput* teachingLesson;
	NeuralNetworkIO<bool>* teachingInput;
	std::vector<std::vector<double>> teachingPattern;

	void SetUp() {
		teachingInput = new NeuralNetworkIO<bool>(3);
		teachingInput->set(0, 0, true);
		teachingInput->set(0, 1, false);
		teachingInput->set(0, 2, false);
		teachingInput->set(1, 0, false);
		teachingInput->set(1, 2, true);
		teachingInput->set(2, 0, true);
		teachingInput->set(2, 1, false);
		teachingInput->set(2, 2, true);
		teachingPattern.resize(3, std::vector<double>(2));
		teachingPattern[0][0] = 9;
		teachingPattern[0][1] = 8;
		teachingPattern[1][0] = 7;
		teachingPattern[1][1] = 6;
		teachingPattern[2][0] = 5;
		teachingPattern[2][1] = 4;
		teachingLesson = new TeachingLessonBooleanInput(teachingPattern, teachingInput);
	}

	virtual ~TeachingLessonBooleanInputTest()
	{
		delete teachingLesson;
	}
};

TEST_F(TeachingLessonBooleanInputTest, getTeachingInput)
{
	MockActivationFunction* activationFunction = new MockActivationFunction();
	EXPECT_CALL(*activationFunction, hasAMaxAndMinimum()).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(*activationFunction, getMaximum()).WillRepeatedly(testing::Return(42));
	EXPECT_CALL(*activationFunction, getMinimum()).WillRepeatedly(testing::Return(-3));

	NeuralNetworkIO<double> expected(teachingInput->getDimension());
	expected.set(0, 0, 42);
	expected.set(0, 1, -3);
	expected.set(0, 2, -3);
	expected.set(1, 0, -3);
	expected.set(1, 2, 42);
	expected.set(2, 0, 42);
	expected.set(2, 1, -3);
	expected.set(2, 2, 42);
	EXPECT_EQ(expected, *teachingLesson->getTeachingInput(activationFunction));
}

TEST_F(TeachingLessonBooleanInputTest, getTeachingPattern)
{
	EXPECT_EQ(teachingPattern, *teachingLesson->getTeachingPattern());
}

TEST_F(TeachingLessonBooleanInputTest, unfold)
{
	std::unique_ptr<TeachingLessonBooleanInput> unfoldedTeachingLesson(static_cast<TeachingLessonBooleanInput*>(teachingLesson->unfold()));

	NeuralNetworkIO<bool> expectedTeachingInput(3);
	expectedTeachingInput.set(0, 0, true);
	expectedTeachingInput.set(0, 1, false);
	expectedTeachingInput.set(0, 2, true);
	EXPECT_EQ(expectedTeachingInput, *unfoldedTeachingLesson->getBooleanTeachingInput());

	std::vector<std::vector<double>> expectedTeachingPattern(1, std::vector<double>(6));
	expectedTeachingPattern[0][0] = 9;
	expectedTeachingPattern[0][1] = 8;
	expectedTeachingPattern[0][2] = 7;
	expectedTeachingPattern[0][3] = 6;
	expectedTeachingPattern[0][4] = 5;
	expectedTeachingPattern[0][5] = 4;
	EXPECT_EQ(expectedTeachingPattern, *unfoldedTeachingLesson->getTeachingPattern());
}

TEST_F(TeachingLessonBooleanInputTest, getMaxTimeStep)
{
	EXPECT_EQ(2, teachingLesson->getMaxTimeStep());
}
