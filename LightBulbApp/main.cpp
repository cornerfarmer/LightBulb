#include "Performance/NetworkPerformanceTests.hpp"
#include "Examples/BackpropagationXorExample.hpp"
#include "Examples/RBFNetworkBiggerExample.hpp"
#include "Examples/EvolutionExample.hpp"
#include "Examples/FunctionEvolutionExample.hpp"
#include "Examples/NetworkEvolutionExample.hpp"
#include "Examples/TeachedEvolutionExample.hpp"
#include "Examples/TicTacToeEvolutionExample.hpp"
#include <iostream>


int main()
{
	doFunctionEvolutionExample();
	std::cin.get();
	return 0;
}
