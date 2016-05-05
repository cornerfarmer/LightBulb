#include "gtest/gtest.h"
#include <Mocks/MockTestableEvolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>

class AbstractEvolutionWorldTest : public testing::Test {
public:
	MockTestableEvolutionWorld* evolutionWorld;

	void SetUp() {
		evolutionWorld = new MockTestableEvolutionWorld();
	}

	virtual ~AbstractEvolutionWorldTest()
	{
		delete evolutionWorld;
	}
};

TEST_F(AbstractEvolutionWorldTest, getHighscoreList)
{
	EXPECT_CALL(*evolutionWorld, getPopulationSize()).WillRepeatedly(testing::Return(3));

	MockEvolutionObject object1, object2, object3;
	std::vector<AbstractEvolutionObject*> objects({ &object1, &object2, &object3 });
	EXPECT_CALL(*evolutionWorld, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));

	EXPECT_CALL(*evolutionWorld, getScore(&object1)).WillRepeatedly(testing::Return(1));
	EXPECT_CALL(*evolutionWorld, getScore(&object2)).WillRepeatedly(testing::Return(5));
	EXPECT_CALL(*evolutionWorld, getScore(&object3)).WillRepeatedly(testing::Return(-2));

	auto highscore = evolutionWorld->getHighscoreList();

	EXPECT_EQ(3, highscore->size());
	EXPECT_EQ(5, (*highscore)[0].first);
	EXPECT_EQ(&object2, (*highscore)[0].second);
	EXPECT_EQ(1, (*highscore)[1].first);
	EXPECT_EQ(&object1, (*highscore)[1].second);
	EXPECT_EQ(-2, (*highscore)[2].first);
	EXPECT_EQ(&object3, (*highscore)[2].second);
}
