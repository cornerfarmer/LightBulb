#include "gtest/gtest.h"
#include <Teaching/TeachingLessonLinearInput.hpp>

class TeachingLessonLinearInputTest : public testing::Test {
public:
	TeachingLessonLinearInput* teachingLesson;
	NeuralNetworkIO<double>* teachingInput;
	std::vector<std::vector<double>> teachingPattern;
	void SetUp() {
		teachingInput = new NeuralNetworkIO<double>(3);
		teachingInput->set(0, 0, 1);
		teachingInput->set(0, 1, 2);
		teachingInput->set(0, 2, 3);
		teachingInput->set(1, 0, 4);
		teachingInput->set(1, 1, 5);
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

	virtual ~TeachingLessonLinearInputTest()
	{
		delete teachingLesson;
	}
};

TEST_F(TeachingLessonLinearInputTest, getTeachingInput)
{
	EXPECT_EQ(teachingLesson->getTeachingInput(NULL), teachingInput);
}

TEST_F(TeachingLessonLinearInputTest, getTeachingPattern)
{
	EXPECT_EQ(*teachingLesson->getTeachingPattern(), teachingPattern);
}

TEST_F(TeachingLessonLinearInputTest, unfold)
{
	std::unique_ptr<AbstractTeachingLesson> unfoldedTeachingLesson(teachingLesson->unfold());

	NeuralNetworkIO<double> expectedTeachingInput(3);
	expectedTeachingInput.set(0, 0, 7);
	expectedTeachingInput.set(0, 1, 8);
	expectedTeachingInput.set(0, 2, 9);
	EXPECT_EQ(*unfoldedTeachingLesson->getTeachingInput(NULL), expectedTeachingInput);

	std::vector<std::vector<double>> expectedTeachingPattern(1, std::vector<double>(6));
	expectedTeachingPattern[0][0] = 9;
	expectedTeachingPattern[0][1] = 8;
	expectedTeachingPattern[0][2] = 7;
	expectedTeachingPattern[0][3] = 6;
	expectedTeachingPattern[0][4] = 5;
	expectedTeachingPattern[0][5] = 4;
	EXPECT_EQ(*unfoldedTeachingLesson->getTeachingPattern(), expectedTeachingPattern);
}

TEST_F(TeachingLessonLinearInputTest, getMaxTimeStep)
{
	EXPECT_EQ(teachingLesson->getMaxTimeStep(), 2);
}