#include "Performance/NetworkPerformanceTests.hpp"
#include "Examples/BackpropagationXorExample.hpp"
#include "Examples/RBFNetworkBiggerExample.hpp"
#include <iostream>


int main()
{
	doRBFNetworkBiggerExample();
	std::cin.get();
	return 0;
}
