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

	EXPECT_EQ(selectedObjects->size(), 3);
	EXPECT_EQ(selectedObjects->at(0), highscore[0].second);
	EXPECT_EQ(selectedObjects->at(1), highscore[1].second);
	EXPECT_EQ(selectedObjects->at(2), highscore[2].second);

	EXPECT_EQ(counter.size(), 3);
	EXPECT_EQ(counter[highscore[0].second], 1);
	EXPECT_EQ(counter[highscore[1].second], 1);
	EXPECT_EQ(counter[highscore[2].second], 1);
}
