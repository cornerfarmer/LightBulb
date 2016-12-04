#include "gtest/gtest.h"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/BestSelectionCommand.hpp>

using namespace LightBulb;

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
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(3, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));
	highscore.push_back(std::make_pair(1, new MockIndividual()));
	MockIndividual* notUsedIndividual1 = new MockIndividual(), *notUsedIndividual2 = new MockIndividual();
	highscore.push_back(std::make_pair(0, notUsedIndividual1));
	highscore.push_back(std::make_pair(-1, notUsedIndividual2));

	std::vector<AbstractIndividual*> notUsedIndividuals;

	std::vector<AbstractIndividual*> individuals;
	bestSelectionCommand->execute(highscore, individuals, notUsedIndividuals);

	EXPECT_EQ(3, individuals.size());
	EXPECT_EQ(highscore[0].second, individuals[0]);
	EXPECT_EQ(highscore[1].second, individuals[1]);
	EXPECT_EQ(highscore[2].second, individuals[2]);

	EXPECT_EQ(2, notUsedIndividuals.size());
	EXPECT_EQ(notUsedIndividual1, notUsedIndividuals[0]);
	EXPECT_EQ(notUsedIndividual2, notUsedIndividuals[1]);
}
