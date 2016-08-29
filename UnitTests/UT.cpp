#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Function/IdentityFunction.cpp"


int main(int argc, char** argv)
{
	::testing::InitGoogleMock(&argc, argv);
	RUN_ALL_TESTS();
}