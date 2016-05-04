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
	MockEvolutionObject* notUsedObject1 = new MockEvolutionObject(), *notUsedObject2 = new MockEvolutionObject();
	highscore.push_back(std::make_pair(0, notUsedObject1));
	highscore.push_back(std::make_pair(-1, notUsedObject2));

	std::vector<AbstractEvolutionObject*> notUsedObjects;

	std::vector<AbstractEvolutionObject*> objects;
	bestSelectionCommand->execute(&highscore, &objects, &notUsedObjects);

	EXPECT_EQ(3, objects.size());
	EXPECT_EQ(highscore[0].second, objects[0]);
	EXPECT_EQ(highscore[1].second, objects[1]);
	EXPECT_EQ(highscore[2].second, objects[2]);

	EXPECT_EQ(2, notUsedObjects.size());
	EXPECT_EQ(notUsedObject1, notUsedObjects[0]);
	EXPECT_EQ(notUsedObject2, notUsedObjects[1]);
}
