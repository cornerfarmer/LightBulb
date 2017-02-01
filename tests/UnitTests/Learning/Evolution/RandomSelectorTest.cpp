#include "UnitTestsPrec.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/RandomSelector.hpp>
#include <Mocks/MockRandomFunction.hpp>

using namespace LightBulb;

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
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(3, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));
	highscore.push_back(std::make_pair(1, new MockIndividual()));
	highscore.push_back(std::make_pair(0, new MockIndividual()));
	highscore.push_back(std::make_pair(-1, new MockIndividual()));

	{
		testing::InSequence s;
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(4));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(2));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(3));
	}

	std::map<AbstractIndividual*, int> counter;
	randomSelector->executeMutationSelection(3, highscore, counter);
	std::vector<AbstractIndividual*>& selectedIndividuals = randomSelector->getMutationSelection();

	EXPECT_EQ(3, selectedIndividuals.size());
	EXPECT_EQ(highscore[4].second, selectedIndividuals[0]);
	EXPECT_EQ(highscore[2].second, selectedIndividuals[1]);
	EXPECT_EQ(highscore[3].second, selectedIndividuals[2]);

	EXPECT_EQ(3, counter.size());
	EXPECT_EQ(1, counter[highscore[4].second]);
	EXPECT_EQ(1, counter[highscore[2].second]);
	EXPECT_EQ(1, counter[highscore[3].second]);
}



TEST_F(RandomSelectorTest, executeRecombinationSelection)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(3, new MockIndividual()));
	highscore.push_back(std::make_pair(2, new MockIndividual()));
	highscore.push_back(std::make_pair(1, new MockIndividual()));
	highscore.push_back(std::make_pair(0, new MockIndividual()));
	highscore.push_back(std::make_pair(-1, new MockIndividual()));

	{
		testing::InSequence s;
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(3));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(1));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(2));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(0));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(2));
		EXPECT_CALL(*randomFunction, execute(5)).WillOnce(testing::Return(4));
	}

	std::map<AbstractIndividual*, int> counter;
	randomSelector->executeRecombinationSelection(3, highscore, counter);
	std::vector<AbstractIndividual*>& selectedIndividuals = randomSelector->getRecombinationSelection();

	EXPECT_EQ(6, selectedIndividuals.size());
	EXPECT_EQ(highscore[3].second, selectedIndividuals[0]);
	EXPECT_EQ(highscore[1].second, selectedIndividuals[1]);
	EXPECT_EQ(highscore[2].second, selectedIndividuals[2]);
	EXPECT_EQ(highscore[0].second, selectedIndividuals[3]);
	EXPECT_EQ(highscore[2].second, selectedIndividuals[4]);
	EXPECT_EQ(highscore[4].second, selectedIndividuals[5]);

	EXPECT_EQ(5, counter.size());
	EXPECT_EQ(1, counter[highscore[3].second]);
	EXPECT_EQ(1, counter[highscore[1].second]);
	EXPECT_EQ(2, counter[highscore[2].second]);
	EXPECT_EQ(1, counter[highscore[0].second]);
	EXPECT_EQ(1, counter[highscore[4].second]);
}
