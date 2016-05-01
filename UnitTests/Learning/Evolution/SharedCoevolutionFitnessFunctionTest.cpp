#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Mocks/MockmutationSelector.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>
#include <Learning/Evolution/SharedCoevolutionFitnessFunction.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <array>

using testing::Expectation;

class SharedCoevolutionFitnessFunctionTest : public testing::Test {
public:
	SharedCoevolutionFitnessFunction* sharedCoevolutionFitnessFunction;
	std::array<MockEvolutionObject*, 3> objects;

	void SetUp() {
		sharedCoevolutionFitnessFunction = new SharedCoevolutionFitnessFunction();
		objects[0] = new MockEvolutionObject();
		objects[1] = new MockEvolutionObject();
		objects[2] = new MockEvolutionObject();
	}

	virtual ~SharedCoevolutionFitnessFunctionTest()
	{
		delete sharedCoevolutionFitnessFunction;
		delete objects[0];
		delete objects[1]; 
		delete objects[2];
	}
};

TEST_F(SharedCoevolutionFitnessFunctionTest, start)
{
	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> results;

	results[objects[0]][objects[1]] = true;
	results[objects[1]][objects[0]] = false;

	results[objects[1]][objects[2]] = true;
	results[objects[2]][objects[1]] = false;

	results[objects[0]][objects[2]] = true;
	results[objects[2]][objects[0]] = false;

	auto fitnessValues = sharedCoevolutionFitnessFunction->execute(results);

	EXPECT_EQ(1.5, fitnessValues[objects[0]]);
	EXPECT_EQ(0.5, fitnessValues[objects[1]]);
	EXPECT_EQ(0, fitnessValues[objects[2]]);
}
