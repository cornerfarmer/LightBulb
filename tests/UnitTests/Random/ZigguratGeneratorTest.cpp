#include "LightBulb/Random/ZigguratGenerator.hpp"
#include "gtest/gtest.h"

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
	EXPECT_NEAR(-0.596595168, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(-0.124876395, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(-0.262766212, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(1.19164324, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(0.310975045, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(0.481335849, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(0.905268431, zigguratGenerator.randDouble(), 0.00001);
	EXPECT_NEAR(-0.0836875141, zigguratGenerator.randDouble(), 0.00001);
}

TEST_P(ZigguratGeneratorTest, randMultipleDouble)
{
	ZigguratGenerator zigguratGenerator(42);

	if (GetParam())
		zigguratGenerator.setCalculatorType(CT_GPU);
	const Vector<>& numbers = zigguratGenerator.randMultipleDouble(10);
	EXPECT_NEAR(0.00946542, numbers.getEigenValue()[0], 0.00001);
	EXPECT_NEAR(-1.22748, numbers.getEigenValue()[1], 0.00001);
	EXPECT_NEAR(-0.596595168, numbers.getEigenValue()[2], 0.00001);
	EXPECT_NEAR(-0.124876395, numbers.getEigenValue()[3], 0.00001);
	EXPECT_NEAR(-0.262766212, numbers.getEigenValue()[4], 0.00001);
	EXPECT_NEAR(1.19164324, numbers.getEigenValue()[5], 0.00001);
	EXPECT_NEAR(0.310975045, numbers.getEigenValue()[6], 0.00001);
	EXPECT_NEAR(0.481335849, numbers.getEigenValue()[7], 0.00001);
	EXPECT_NEAR(0.905268431, numbers.getEigenValue()[8], 0.00001);
	EXPECT_NEAR(-0.0836875141, numbers.getEigenValue()[9], 0.00001);
}

