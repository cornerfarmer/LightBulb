#include "gtest/gtest.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/TeachingEvolutionWorld.hpp>
#include <Learning/Evolution/TeachedEvolutionObject.hpp>
#include <Mocks/MockTeacher.hpp>
#include <Mocks/MockNeuronDescriptionFactory.hpp>

class TeachedEvolutionTest : public testing::Test {
public:
	TeachingEvolutionWorld* teachingEvolutionWorld;
	MockTeacher teacher;
	LayeredNetworkOptions options;
	void SetUp() {
		
		options.descriptionFactory = new MockNeuronDescriptionFactory();
		options.neuronsPerLayerCount.push_back(2);
		options.neuronsPerLayerCount.push_back(1);
		teachingEvolutionWorld = new TeachingEvolutionWorld(&teacher, options);
	}

	virtual ~TeachedEvolutionTest()
	{
		//delete teachingEvolutionWorld;
	}
};

TEST_F(TeachedEvolutionTest, doSimulationStep)
{
	AbstractEvolutionObject* evolutionObject = teachingEvolutionWorld->addNewObject(true);

	EXPECT_CALL(teacher, getTotalError(testing::Ref(*evolutionObject->getNeuralNetwork()), testing::_)).WillOnce(testing::Return(5));

	teachingEvolutionWorld->doSimulationStep();

	EXPECT_EQ(-5, teachingEvolutionWorld->getScore(evolutionObject));
}
