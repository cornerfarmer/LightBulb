#include "gtest/gtest.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <Mocks/MockRandomFunction.hpp>

class RandomSelectorTest : public testing::Test {
public:
	RandomSelector* randomSelector;
	MockRandomFunction* randomFunction;
	void SetUp() {
		randomFunction = new MockRandomFunction();
		randomSelector = new RandomSelector(randomFunction);
	}

	virtual ~RandomSelectorTest()
	{
		delete randomSelector;
	}
};

TEST_F(RandomSelectorTest, executeMutationSelection)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(3, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(2, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(1, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(0, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(-1, new MockEvolutionObject()));

	{
		testing::InSequence s;
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(4));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(2));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(3));
	}

	std::map<AbstractEvolutionObject*, int> counter;
	randomSelector->executeMutationSelection(3, &highscore, &counter);
	std::vector<AbstractEvolutionObject*>* selectedObjects = randomSelector->getMutationSelection();

	EXPECT_EQ(3, selectedObjects->size());
	EXPECT_EQ(highscore[4].second, selectedObjects->at(0));
	EXPECT_EQ(highscore[2].second, selectedObjects->at(1));
	EXPECT_EQ(highscore[3].second, selectedObjects->at(2));

	EXPECT_EQ(3, counter.size());
	EXPECT_EQ(1, counter[highscore[4].second]);
	EXPECT_EQ(1, counter[highscore[2].second]);
	EXPECT_EQ(1, counter[highscore[3].second]);
}



TEST_F(RandomSelectorTest, executeRecombinationSelection)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(3, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(2, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(1, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(0, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(-1, new MockEvolutionObject()));

	{
		testing::InSequence s;
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(4));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(2));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(3));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(1));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(3));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(5));
	}

	std::map<AbstractEvolutionObject*, int> counter;
	randomSelector->executeRecombinationSelection(3, &highscore, &counter);
	std::vector<AbstractEvolutionObject*>* selectedObjects = randomSelector->getRecombinationSelection();

	EXPECT_EQ(6, selectedObjects->size());
	EXPECT_EQ(highscore[4].second, selectedObjects->at(0));
	EXPECT_EQ(highscore[2].second, selectedObjects->at(1));
	EXPECT_EQ(highscore[3].second, selectedObjects->at(2));
	EXPECT_EQ(highscore[1].second, selectedObjects->at(3));
	EXPECT_EQ(highscore[3].second, selectedObjects->at(4));
	EXPECT_EQ(highscore[5].second, selectedObjects->at(5));

	EXPECT_EQ(5, counter.size());
	EXPECT_EQ(1, counter[highscore[4].second]);
	EXPECT_EQ(1, counter[highscore[2].second]);
	EXPECT_EQ(2, counter[highscore[3].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
	EXPECT_EQ(1, counter[highscore[5].second]);
}