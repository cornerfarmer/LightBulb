#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <Learning/Evolution/StochasticUniversalSamplingSelector.hpp>
#include <Mocks/MockSelectionFunction.hpp>

using namespace LightBulb;

class StochasticUniversalSamplingSelectorTest : public testing::Test {
public:
	StochasticUniversalSamplingSelector* stochasticUniversalSamplingSelector;
	MockSelectionFunction* selectionFunction;

	void SetUp() {
		selectionFunction = new MockSelectionFunction();
		stochasticUniversalSamplingSelector = new StochasticUniversalSamplingSelector(selectionFunction);
	}

	virtual ~StochasticUniversalSamplingSelectorTest()
	{
		delete stochasticUniversalSamplingSelector;
	}
};

TEST_F(StochasticUniversalSamplingSelectorTest, executeMutationSelection)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(8, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));

	std::vector<double> probabilities;
	std::vector<int> selected({0, 0, 1});
	EXPECT_CALL(*selectionFunction, execute(testing::_, 3)).WillRepeatedly(DoAll(testing::SaveArg<0>(&probabilities), testing::Return(selected)));

	std::map<AbstractIndividual*, int> counter;
	stochasticUniversalSamplingSelector->executeMutationSelection(3, highscore, counter);
	std::vector<AbstractIndividual*>& selectedIndividuals = stochasticUniversalSamplingSelector->getMutationSelection();

	EXPECT_EQ(2, probabilities.size());
	EXPECT_EQ(8, probabilities[0]);
	EXPECT_EQ(2, probabilities[1]);

	EXPECT_EQ(3, selectedIndividuals.size());
	EXPECT_EQ(highscore[0].second, selectedIndividuals[0]);
	EXPECT_EQ(highscore[0].second, selectedIndividuals[1]);
	EXPECT_EQ(highscore[1].second, selectedIndividuals[2]);

	EXPECT_EQ(2, counter.size());
	EXPECT_EQ(2, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
}


TEST_F(StochasticUniversalSamplingSelectorTest, executeRecombinationSelection)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(8, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));

	std::vector<double> probabilities;
	std::vector<int> selected({ 0, 0, 0, 0, 1, 1 });
	EXPECT_CALL(*selectionFunction, execute(testing::_, 6)).WillRepeatedly(DoAll(testing::SaveArg<0>(&probabilities), testing::Return(selected)));

	std::map<AbstractIndividual*, int> counter;
	stochasticUniversalSamplingSelector->executeRecombinationSelection(3, highscore, counter);
	std::vector<AbstractIndividual*>& selectedIndividuals = stochasticUniversalSamplingSelector->getRecombinationSelection();

	EXPECT_EQ(2, probabilities.size());
	EXPECT_EQ(8, probabilities[0]);
	EXPECT_EQ(2, probabilities[1]);

	EXPECT_EQ(6, selectedIndividuals.size());
	int count0 = 0, count1 = 0;
	for (auto selectedIndividual = selectedIndividuals.begin(); selectedIndividual != selectedIndividuals.end(); selectedIndividual++)
	{
		if (*selectedIndividual == highscore[0].second)
			count0++;
		else if (*selectedIndividual == highscore[1].second)
			count1++;
	}
	EXPECT_EQ(4, count0);
	EXPECT_EQ(2, count1);

	EXPECT_EQ(2, counter.size());
	EXPECT_EQ(4, counter[highscore[0].second]);
	EXPECT_EQ(2, counter[highscore[1].second]);
}
