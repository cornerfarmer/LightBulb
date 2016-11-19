#include "gtest/gtest.h"
#include <Mocks/MockTestableEvolutionWorld.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

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

	MockIndividual individual1, individual2, individual3;
	std::vector<AbstractIndividual*> individuals({ &individual1, &individual2, &individual3 });
	EXPECT_CALL(*evolutionWorld, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));

	EXPECT_CALL(*evolutionWorld, getScore(testing::Ref(individual1))).WillRepeatedly(testing::Return(1));
	EXPECT_CALL(*evolutionWorld, getScore(testing::Ref(individual2))).WillRepeatedly(testing::Return(5));
	EXPECT_CALL(*evolutionWorld, getScore(testing::Ref(individual3))).WillRepeatedly(testing::Return(-2));

	auto highscore = evolutionWorld->getHighscoreList();

	EXPECT_EQ(3, highscore.size());
	EXPECT_EQ(5, highscore[0].first);
	EXPECT_EQ(&individual2, highscore[0].second);
	EXPECT_EQ(1, highscore[1].first);
	EXPECT_EQ(&individual1, highscore[1].second);
	EXPECT_EQ(-2, highscore[2].first);
	EXPECT_EQ(&individual3, highscore[2].second);
}
