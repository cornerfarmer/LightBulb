#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/StochasticUniversalSamplingSelector.hpp>
#include <Mocks/MockSelectionFunction.hpp>

using namespace LightBulb;

class StochasticUniversalSamplingSelectorTest : public testing::Test {
public:
	StochasticUniversalSamplingSelector* stochasticUniversalSamplingSelector;
	MockSelectionFunction* selectionFunction;

	void SetUp() {
		stochasticUniversalSamplingSelector = new StochasticUniversalSamplingSelector();
		selectionFunction = new MockSelectionFunction();
		stochasticUniversalSamplingSelector->setRandomFunction(selectionFunction);
	}

	virtual ~StochasticUniversalSamplingSelectorTest()
	{
		delete stochasticUniversalSamplingSelector;
	}
};

TEST_F(StochasticUniversalSamplingSelectorTest, executeMutationSelection)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(8, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(2, new MockEvolutionObject()));

	std::vector<double> probabilities;
	std::vector<int> selected({0, 0, 1});
	EXPECT_CALL(*selectionFunction, execute(testing::_, 3)).WillRepeatedly(testing::DoAll(testing::SaveArg<0>(&probabilities), testing::Return(selected)));

	std::map<AbstractEvolutionObject*, int> counter;
	stochasticUniversalSamplingSelector->executeMutationSelection(3, &highscore, &counter);
	std::vector<AbstractEvolutionObject*>* selectedObjects = stochasticUniversalSamplingSelector->getMutationSelection();

	EXPECT_EQ(2, probabilities.size());
	EXPECT_EQ(8, probabilities[0]);
	EXPECT_EQ(2, probabilities[1]);

	EXPECT_EQ(3, selectedObjects->size());
	EXPECT_EQ(highscore[0].second, selectedObjects->at(0));
	EXPECT_EQ(highscore[0].second, selectedObjects->at(1));
	EXPECT_EQ(highscore[1].second, selectedObjects->at(2));

	EXPECT_EQ(2, counter.size());
	EXPECT_EQ(2, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
}


TEST_F(StochasticUniversalSamplingSelectorTest, executeRecombinationSelection)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(8, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(2, new MockEvolutionObject()));

	std::vector<double> probabilities;
	std::vector<int> selected({ 0, 0, 0, 0, 1, 1 });
	EXPECT_CALL(*selectionFunction, execute(testing::_, 6)).WillRepeatedly(testing::DoAll(testing::SaveArg<0>(&probabilities), testing::Return(selected)));

	std::map<AbstractEvolutionObject*, int> counter;
	stochasticUniversalSamplingSelector->executeRecombinationSelection(3, &highscore, &counter);
	std::vector<AbstractEvolutionObject*>* selectedObjects = stochasticUniversalSamplingSelector->getRecombinationSelection();

	EXPECT_EQ(2, probabilities.size());
	EXPECT_EQ(8, probabilities[0]);
	EXPECT_EQ(2, probabilities[1]);

	EXPECT_EQ(6, selectedObjects->size());
	int count0 = 0, count1 = 0;
	for (auto selectedObject = selectedObjects->begin(); selectedObject != selectedObjects->end(); selectedObject++)
	{
		if (*selectedObject == highscore[0].second)
			count0++;
		else if (*selectedObject == highscore[1].second)
			count1++;
	}
	EXPECT_EQ(4, count0);
	EXPECT_EQ(2, count1);

	EXPECT_EQ(2, counter.size());
	EXPECT_EQ(4, counter[highscore[0].second]);
	EXPECT_EQ(2, counter[highscore[1].second]);
}
