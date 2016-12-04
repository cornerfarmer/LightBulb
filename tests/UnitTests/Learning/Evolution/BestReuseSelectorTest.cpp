#include "gtest/gtest.h"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/BestReuseSelector.hpp>

using namespace LightBulb;

class BestReuseSelectorTest : public testing::Test {
public:
	BestReuseSelector* bestReuseSelector;

	void SetUp() {
		bestReuseSelector = new BestReuseSelector();
	}

	virtual ~BestReuseSelectorTest()
	{
		delete bestReuseSelector;
	}
};

TEST_F(BestReuseSelectorTest, executeReuseSelection)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(3, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));
	highscore.push_back(std::make_pair(1, new MockIndividual()));
	highscore.push_back(std::make_pair(0, new MockIndividual()));
	highscore.push_back(std::make_pair(-1, new MockIndividual()));

	std::map<AbstractIndividual*, int> counter;
	bestReuseSelector->executeReuseSelection(3, highscore, counter);
	const std::vector<AbstractIndividual*>& selectedIndividuals = bestReuseSelector->getReuseSelection();

	EXPECT_EQ(3, selectedIndividuals.size());
	EXPECT_EQ(highscore[0].second, selectedIndividuals[0]);
	EXPECT_EQ(highscore[1].second, selectedIndividuals[1]);
	EXPECT_EQ(highscore[2].second, selectedIndividuals[2]);

	EXPECT_EQ(3, counter.size());
	EXPECT_EQ(1, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
	EXPECT_EQ(1, counter[highscore[2].second]);
}
