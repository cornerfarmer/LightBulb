#include <Mocks/MockMutationSelector.hpp>
#include <LightBulb/Learning/Evolution/CoevolutionLearningRule.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>
#include <LightBulb/Learning/Evolution/SharedCoevolutionFitnessFunction.hpp>
#include <Mocks/MockIndividual.hpp>
#include <array>
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

using namespace LightBulb;
using testing::Expectation;

class SharedCoevolutionFitnessFunctionTest : public testing::Test {
public:
	SharedCoevolutionFitnessFunction* sharedCoevolutionFitnessFunction;
	std::array<MockIndividual*, 3> individuals;

	void SetUp() {
		sharedCoevolutionFitnessFunction = new SharedCoevolutionFitnessFunction();
		individuals[0] = new MockIndividual();
		individuals[1] = new MockIndividual();
		individuals[2] = new MockIndividual();
	}

	virtual ~SharedCoevolutionFitnessFunctionTest()
	{
		delete sharedCoevolutionFitnessFunction;
		delete individuals[0];
		delete individuals[1]; 
		delete individuals[2];
	}
};

TEST_F(SharedCoevolutionFitnessFunctionTest, start)
{
	CombiningStrategyResults results;

	//results[individuals[0]][individuals[1]][0] = true;
	//results[individuals[1]][individuals[0]][0] = false;

	//results[individuals[1]][individuals[2]][0] = true;
	//results[individuals[2]][individuals[1]][0] = false;

	//results[individuals[0]][individuals[2]][0] = true;
	//results[individuals[2]][individuals[0]][0] = false;

	auto fitnessValues = sharedCoevolutionFitnessFunction->execute(results);

	EXPECT_EQ(1.5, (*fitnessValues)[individuals[0]]);
	EXPECT_EQ(0.5, (*fitnessValues)[individuals[1]]);
	EXPECT_EQ(0, (*fitnessValues)[individuals[2]]);
}
