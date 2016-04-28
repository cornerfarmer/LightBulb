#include "gtest/gtest.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>

class BestSelectionCommandTest : public testing::Test {
public:
	BestSelectionCommand* bestSelectionCommand;

	void SetUp() {
		bestSelectionCommand = new BestSelectionCommand(3);
	}

	virtual ~BestSelectionCommandTest()
	{
		delete bestSelectionCommand;
	}
};

TEST_F(BestSelectionCommandTest, executeReuseSelection)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(3, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(2, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(1, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(0, new MockEvolutionObject()));
	highscore.push_back(std::make_pair(-1, new MockEvolutionObject()));

	std::vector<AbstractEvolutionObject*> notUsedObjects;

	std::vector<AbstractEvolutionObject*> objects;
	bestSelectionCommand->execute(&highscore, &objects, &notUsedObjects);

	EXPECT_EQ(objects.size(), 3);
	EXPECT_EQ(objects[0], highscore[0].second);
	EXPECT_EQ(objects[1], highscore[1].second);
	EXPECT_EQ(objects[2], highscore[2].second);

	EXPECT_EQ(notUsedObjects.size(), 2);
	EXPECT_EQ(notUsedObjects[0], highscore[3].second);
	EXPECT_EQ(notUsedObjects[1], highscore[4].second);
}
