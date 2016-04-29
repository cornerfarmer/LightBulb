#include "gtest/gtest.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>

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
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(3, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(2, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(1, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(0, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(-1, new MockEvolutionObject()));

	std::map<AbstractEvolutionObject*, int> counter;
	bestReuseSelector->executeReuseSelection(3, &highscore, &counter);
	std::vector<AbstractEvolutionObject*>* selectedObjects = bestReuseSelector->getReuseSelection();

	EXPECT_EQ(3, selectedObjects->size());
	EXPECT_EQ(highscore[0].second, selectedObjects->at(0));
	EXPECT_EQ(highscore[1].second, selectedObjects->at(1));
	EXPECT_EQ(highscore[2].second, selectedObjects->at(2));

	EXPECT_EQ(3, counter.size());
	EXPECT_EQ(1, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
	EXPECT_EQ(1, counter[highscore[2].second]);
}
