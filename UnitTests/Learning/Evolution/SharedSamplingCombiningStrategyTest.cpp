#include "gtest/gtest.h"
#include <Learning/Evolution/SharedSamplingCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Mocks/MockCombiningStrategy.hpp>

class SharedSamplingCombiningStrategyTest : public testing::Test {
public:
	SharedSamplingCombiningStrategy* sharedSamplingCombiningStrategy;

	MockCoevolutionWorld world;
	MockEvolutionObject object1, object2, object3, object4, object5, object6;

	void SetUp()
	{
		sharedSamplingCombiningStrategy = new SharedSamplingCombiningStrategy(2);
	}

	virtual ~SharedSamplingCombiningStrategyTest()
	{
		delete sharedSamplingCombiningStrategy;
	}
};

TEST_F(SharedSamplingCombiningStrategyTest, executeTwoEmptyWorlds)
{
	std::vector<AbstractEvolutionObject*> objects;
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));
	
	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::Return(&otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(&parasiteWorld);

	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::Return(&prevResults));

	std::vector<AbstractEvolutionObject*> parasiteObjects;
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::Return(&parasiteObjects));

	auto result = sharedSamplingCombiningStrategy->execute(&world);

	EXPECT_EQ(0, result->size());
}

TEST_F(SharedSamplingCombiningStrategyTest, executeEmptyParasiteWorld)
{
	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));

	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::Return(&otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(&parasiteWorld);

	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::Return(&prevResults));

	std::vector<AbstractEvolutionObject*> parasiteObjects;
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::Return(&parasiteObjects));

	auto result = sharedSamplingCombiningStrategy->execute(&world);

	EXPECT_EQ(0, result->size());
}


TEST_F(SharedSamplingCombiningStrategyTest, executeSingleWorld)
{
	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));
	
	EXPECT_THROW(sharedSamplingCombiningStrategy->execute(&world), std::invalid_argument);
}

TEST_F(SharedSamplingCombiningStrategyTest, executeTwoWorlds)
{
	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::Return(&otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(&parasiteWorld);

	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> prevResults;
	prevResults[&object4][&object1] = true;
	prevResults[&object4][&object2] = true;
	prevResults[&object5][&object1] = true;
	prevResults[&object6][&object3] = true;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::Return(&prevResults));

	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	std::vector<AbstractEvolutionObject*> parasiteObjects({ &object4 , &object5, &object6 });

	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::Return(&parasiteObjects));

	{
		testing::InSequence s;
		EXPECT_CALL(world, compareObjects(&object1, &object4)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareObjects(&object1, &object6)).WillOnce(testing::Return(-1));
		EXPECT_CALL(world, compareObjects(&object2, &object4)).WillOnce(testing::Return(-1));
		EXPECT_CALL(world, compareObjects(&object2, &object6)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareObjects(&object3, &object4)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareObjects(&object3, &object6)).WillOnce(testing::Return(1));
	}
	
	auto result = sharedSamplingCombiningStrategy->execute(&world);

	EXPECT_EQ(5, result->size());
	EXPECT_EQ(2, (*result)[&object1].size());
	EXPECT_EQ(2, (*result)[&object2].size());
	EXPECT_EQ(2, (*result)[&object3].size());
	EXPECT_EQ(3, (*result)[&object4].size());
	EXPECT_EQ(3, (*result)[&object6].size());

}
