#include "gtest/gtest.h"
#include "LightBulb/Random/ZigguratGenerator.hpp"

using namespace LightBulb;

class ZigguratGeneratorTest : public testing::TestWithParam<bool> {

};

INSTANTIATE_TEST_CASE_P(ZigguratGeneratorMultDev, ZigguratGeneratorTest, testing::Bool());

TEST_P(ZigguratGeneratorTest, randDouble)
{
	ZigguratGenerator zigguratGenerator(42);

	if (GetParam())
		zigguratGenerator.setCalculatorType(CT_GPU);
	
	EXPECT_NEAR(0.00946542, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(-1.22748, zigguratGenerator.randDouble(), 0.00001);
}
