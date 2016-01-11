#include "gtest/gtest.h"
#include "Function/IdentityFunction.cpp"

TEST(testFunction, IdentityFunctionTest)
{
	IdentityFunction f;
	EXPECT_EQ(100.0, f.execute(100));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::getchar(); 
}