#include <LightBulb/Teaching/TeachingLessonBooleanInput.hpp>
#include <Mocks/MockActivationOrder.hpp>
#include <Mocks/MockActivationFunction.hpp>

using namespace LightBulb;

class TeachingLessonBooleanInputTest : public testing::Test {
public:
	TeachingLessonBooleanInput* teachingLesson;
	TeachingInput<char>* teachingInput;
	Vector<>* teachingPattern;

	void SetUp() {
		teachingInput = new TeachingInput<char>(3);
		teachingInput->set(0, true);
		teachingInput->set(1, false);
		teachingInput->set(2, false);
		teachingPattern = new Vector<>(2);
		teachingPattern->getEigenValueForEditing()[0] = 9;
		teachingPattern->getEigenValueForEditing()[1] = 8;
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

	TeachingInput<> expected(teachingInput->getDimension());
	expected.set(0, 42);
	expected.set(1, -3);
	expected.set(2, -3);
	EXPECT_EQ(expected, teachingLesson->getTeachingInput(*activationFunction));
}

TEST_F(TeachingLessonBooleanInputTest, getTeachingPattern)
{
	EXPECT_EQ(*teachingPattern, teachingLesson->getTeachingPattern());
}
