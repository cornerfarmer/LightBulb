#include "gtest/gtest.h"
#include <Learning/Evolution/SharedSamplingCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Mocks/MockCombiningStrategy.hpp>

using namespace LightBulb;

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
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	
	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(parasiteWorld);

	CombiningStrategyResults prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractEvolutionObject*> parasiteObjects;
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(parasiteObjects));

	auto& result = sharedSamplingCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}

TEST_F(SharedSamplingCombiningStrategyTest, executeEmptyParasiteWorld)
{
	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));

	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(parasiteWorld);

	CombiningStrategyResults prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractEvolutionObject*> parasiteObjects;
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(parasiteObjects));

	auto& result = sharedSamplingCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}


TEST_F(SharedSamplingCombiningStrategyTest, executeSingleWorld)
{
	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	
	EXPECT_THROW(sharedSamplingCombiningStrategy->execute(world), std::invalid_argument);
}

TEST_F(SharedSamplingCombiningStrategyTest, executeTwoWorlds)
{
	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(parasiteWorld);

	CombiningStrategyResults prevResults;
	prevResults[&object4][&object1][0] = true;
	prevResults[&object4][&object2][0] = true;
	prevResults[&object5][&object1][0] = true;
	prevResults[&object6][&object3][0] = true;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	std::vector<AbstractEvolutionObject*> parasiteObjects({ &object4 , &object5, &object6 });

	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(parasiteObjects));

	{
		testing::InSequence s;
		EXPECT_CALL(world, compareObjects(testing::Ref(object1), testing::Ref(object4), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareObjects(testing::Ref(object1), testing::Ref(object6), 0)).WillOnce(testing::Return(-1));
		EXPECT_CALL(world, compareObjects(testing::Ref(object2), testing::Ref(object4), 0)).WillOnce(testing::Return(-1));
		EXPECT_CALL(world, compareObjects(testing::Ref(object2), testing::Ref(object6), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareObjects(testing::Ref(object3), testing::Ref(object4), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareObjects(testing::Ref(object3), testing::Ref(object6), 0)).WillOnce(testing::Return(1));
	}
	
	auto& result = sharedSamplingCombiningStrategy->execute(world);

	EXPECT_EQ(5, result.size());
	EXPECT_EQ(2, result[&object1].size());
	EXPECT_EQ(2, result[&object2].size());
	EXPECT_EQ(2, result[&object3].size());
	EXPECT_EQ(3, result[&object4].size());
	EXPECT_EQ(3, result[&object6].size());

}
