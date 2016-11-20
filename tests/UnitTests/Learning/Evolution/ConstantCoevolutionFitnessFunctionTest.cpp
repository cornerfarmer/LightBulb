#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Mocks/MockMutationSelector.hpp>
#include <Learning/Evolution/CoevolutionLearningRule.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>
#include <Learning/Evolution/ConstantCoevolutionFitnessFunction.hpp>
#include <Mocks/MockIndividual.hpp>
#include <array>

using testing::Expectation;
using namespace LightBulb;

class ConstantCoevolutionFitnessFunctionTest : public testing::Test {
public:
	ConstantCoevolutionFitnessFunction* constantCoevolutionFitnessFunction;
	std::array<MockIndividual*, 3> individuals;

	void SetUp() {
		constantCoevolutionFitnessFunction = new ConstantCoevolutionFitnessFunction();
		individuals[0] = new MockIndividual();
		individuals[1] = new MockIndividual();
		individuals[2] = new MockIndividual();
	}

	virtual ~ConstantCoevolutionFitnessFunctionTest()
	{
		delete constantCoevolutionFitnessFunction;
		delete individuals[0];
		delete individuals[1]; 
		delete individuals[2];
	}
};

TEST_F(ConstantCoevolutionFitnessFunctionTest, start)
{
	CombiningStrategyResults results;

	results[individuals[0]][individuals[1]][0] = true;
	results[individuals[1]][individuals[0]][0] = false;

	results[individuals[1]][individuals[2]][0] = true;
	results[individuals[2]][individuals[1]][0] = false;

	results[individuals[0]][individuals[2]][0] = true;
	results[individuals[2]][individuals[0]][0] = false;

	auto fitnessValues = constantCoevolutionFitnessFunction->execute(results);

	EXPECT_EQ(2, (*fitnessValues)[individuals[0]]);
	EXPECT_EQ(1, (*fitnessValues)[individuals[1]]);
	EXPECT_EQ(0, (*fitnessValues)[individuals[2]]);
}
