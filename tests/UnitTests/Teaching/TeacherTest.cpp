#include <LightBulb/Teaching/Teacher.hpp>
#include <Mocks/MockTeachingLesson.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockActivationOrder.hpp>

using namespace LightBulb;

class TeacherTest : public testing::Test {
public:
	Teacher* teacher;
	MockTeachingLesson* teachingLesson1;
	MockTeachingLesson* teachingLesson2;
	MockTeachingLesson* testingLesson1;
	MockTeachingLesson* testingLesson2;
	void SetUp() {
		teachingLesson1 = new MockTeachingLesson();
		teachingLesson2 = new MockTeachingLesson();
		testingLesson1 = new MockTeachingLesson();
		testingLesson2 = new MockTeachingLesson();

		teacher = new Teacher();

		teacher->addTestingLesson(testingLesson1);
		teacher->addTestingLesson(testingLesson2);
		teacher->addTeachingLesson(teachingLesson1);
		teacher->addTeachingLesson(teachingLesson2);
	}

	virtual ~TeacherTest()
	{
		delete teacher;
	}
};

TEST_F(TeacherTest, getTeachingLessons)
{
	EXPECT_EQ(2, teacher->getTeachingLessons().size());
	EXPECT_EQ(teachingLesson1, teacher->getTeachingLessons().at(0).get());
	EXPECT_EQ(teachingLesson2, teacher->getTeachingLessons().at(1).get());
}

TEST_F(TeacherTest, getTestingLessons)
{
	EXPECT_EQ(2, teacher->getTestingLessons().size());
	EXPECT_EQ(testingLesson1, teacher->getTestingLessons().at(0).get());
	EXPECT_EQ(testingLesson2, teacher->getTestingLessons().at(1).get());
}

TEST_F(TeacherTest, getTotalError)
{
	MockNeuralNetwork* neuralNetwork = new MockNeuralNetwork();
	MockActivationOrder* activationOrder = new MockActivationOrder();

	EXPECT_CALL(*teachingLesson1, getSpecificError(testing::Ref(*neuralNetwork), testing::Ref(*activationOrder), false)).WillOnce(testing::Return(5));
	EXPECT_CALL(*teachingLesson2, getSpecificError(testing::Ref(*neuralNetwork), testing::Ref(*activationOrder), false)).WillOnce(testing::Return(-8));
	EXPECT_CALL(*testingLesson1, getSpecificError(testing::Ref(*neuralNetwork), testing::Ref(*activationOrder), false)).WillOnce(testing::Return(2));
	EXPECT_CALL(*testingLesson2, getSpecificError(testing::Ref(*neuralNetwork), testing::Ref(*activationOrder), false)).WillOnce(testing::Return(42));

	EXPECT_EQ(41, teacher->getTotalError(*neuralNetwork, *activationOrder));
}
