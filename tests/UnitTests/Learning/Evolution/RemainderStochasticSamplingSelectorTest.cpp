#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
#include <Mocks/MockSelectionFunction.hpp>

using namespace LightBulb;

class RemainderStochasticSamplingSelectorTest : public testing::Test {
public:
	RemainderStochasticSamplingSelector* remainderStochasticSamplingSelector;
	MockSelectionFunction* selectionFunction;

	void createSelector(bool withReplacement) {
		selectionFunction = new MockSelectionFunction();
		remainderStochasticSamplingSelector = new RemainderStochasticSamplingSelector(withReplacement, selectionFunction);
	}

	virtual ~RemainderStochasticSamplingSelectorTest()
	{
		delete remainderStochasticSamplingSelector;
	}
};

TEST_F(RemainderStochasticSamplingSelectorTest, executeMutationSelectionWithoutReplacement)
{
	createSelector(false);

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(8, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));

	std::vector<double> secondChance;
	EXPECT_CALL(*selectionFunction, execute(testing::_)).WillRepeatedly(DoAll(testing::SaveArg<0>(&secondChance), testing::Return(1)));

	std::map<AbstractIndividual*, int> counter;
	remainderStochasticSamplingSelector->executeMutationSelection(3, highscore, counter);
	std::vector<AbstractIndividual*>& selectedIndividuals = remainderStochasticSamplingSelector->getMutationSelection();

	EXPECT_EQ(2, secondChance.size());
	EXPECT_EQ(8, secondChance[0]);
	EXPECT_EQ(2, secondChance[1]);

	EXPECT_EQ(3, selectedIndividuals.size());
	EXPECT_EQ(highscore[0].second, selectedIndividuals[0]);
	EXPECT_EQ(highscore[0].second, selectedIndividuals[1]);
	EXPECT_EQ(highscore[1].second, selectedIndividuals[2]);

	EXPECT_EQ(2, counter.size());
	EXPECT_EQ(2, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
}


TEST_F(RemainderStochasticSamplingSelectorTest, executeMutationSelectionWithReplacement)
{
	createSelector(true);

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(8, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));

	std::vector<double> secondChance;
	EXPECT_CALL(*selectionFunction, execute(testing::_)).WillRepeatedly(DoAll(testing::SaveArg<0>(&secondChance), testing::Return(1)));

	std::map<AbstractIndividual*, int> counter;
	remainderStochasticSamplingSelector->executeMutationSelection(3, highscore, counter);
	std::vector<AbstractIndividual*>& selectedIndividuals = remainderStochasticSamplingSelector->getMutationSelection();

	EXPECT_EQ(2, secondChance.size());
	EXPECT_NEAR(0.4, secondChance[0], 0.001);
	EXPECT_NEAR(0.6, secondChance[1], 0.001);

	EXPECT_EQ(3, selectedIndividuals.size());
	EXPECT_EQ(highscore[0].second, selectedIndividuals[0]);
	EXPECT_EQ(highscore[0].second, selectedIndividuals[1]);
	EXPECT_EQ(highscore[1].second, selectedIndividuals[2]);

	EXPECT_EQ(2, counter.size());
	EXPECT_EQ(2, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
}
