#include "gtest/gtest.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
#include <Mocks/MockRandomFunction.hpp>
#include <Mocks/MockSelectionFunction.hpp>

class RemainderStochasticSamplingSelectorTest : public testing::Test {
public:
	RemainderStochasticSamplingSelector* remainderStochasticSamplingSelector;
	MockSelectionFunction* selectionFunction;

	void SetUp() {
		remainderStochasticSamplingSelector = new RemainderStochasticSamplingSelector(false);
		selectionFunction = new MockSelectionFunction();
		remainderStochasticSamplingSelector->setRandomFunction(selectionFunction);
	}

	virtual ~RemainderStochasticSamplingSelectorTest()
	{
		delete remainderStochasticSamplingSelector;
	}
};

TEST_F(RemainderStochasticSamplingSelectorTest, executeMutationSelection)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(8, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(2, new MockEvolutionObject()));

	std::vector<double> secondChance;
	EXPECT_CALL(*selectionFunction, execute(testing::_)).WillRepeatedly(testing::DoAll(testing::SaveArg<0>(&secondChance), testing::Return(1)));

	std::map<AbstractEvolutionObject*, int> counter;
	remainderStochasticSamplingSelector->executeMutationSelection(3, &highscore, &counter);
	std::vector<AbstractEvolutionObject*>* selectedObjects = remainderStochasticSamplingSelector->getMutationSelection();

	EXPECT_EQ(2, secondChance.size());
	EXPECT_EQ(8, secondChance[0]);
	EXPECT_EQ(2, secondChance[1]);

	EXPECT_EQ(3, selectedObjects->size());
	EXPECT_EQ(highscore[0].second, selectedObjects->at(0));
	EXPECT_EQ(highscore[0].second, selectedObjects->at(1));
	EXPECT_EQ(highscore[1].second, selectedObjects->at(2));

	EXPECT_EQ(2, counter.size());
	EXPECT_EQ(2, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
}
