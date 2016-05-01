#include "gtest/gtest.h"
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>

class RateDifferenceConditionTest : public testing::Test {
public:
	RateDifferenceCondition* rateDifferenceCondition;

	void SetUp() {
		rateDifferenceCondition = new RateDifferenceCondition(0.1, 2);
	}

	virtual ~RateDifferenceConditionTest()
	{
		delete rateDifferenceCondition;
	}
};

TEST_F(RateDifferenceConditionTest, evaluateWithEmptyHighscore)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(0, (AbstractEvolutionObject*)NULL));
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
}


TEST_F(RateDifferenceConditionTest, evaluatePositive)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(5, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(3, (AbstractEvolutionObject*)NULL));
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
	highscore[0].first += 0.05;
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
	highscore[0].first += 0.09;
	EXPECT_EQ(true, rateDifferenceCondition->evaluate(&highscore, NULL));
}


TEST_F(RateDifferenceConditionTest, evaluateReset)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(5, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(3, (AbstractEvolutionObject*)NULL));
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
	highscore[0].first = 7;
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));

	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
	EXPECT_EQ(true, rateDifferenceCondition->evaluate(&highscore, NULL));
}

TEST_F(RateDifferenceConditionTest, evaluateResetWithLowerValue)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(5, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(3, (AbstractEvolutionObject*)NULL));
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
	highscore[0].first -= 0.05;
	EXPECT_EQ(false, rateDifferenceCondition->evaluate(&highscore, NULL));
}