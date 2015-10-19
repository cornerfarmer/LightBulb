// Includes
#include "Learning/Evolution/RateDifferenceCondition.hpp"
// Library includes
#include <iostream>
#include <iomanip>

bool RateDifferenceCondition::evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	if (lastBestRate != -1) {
		bool result = (highscore->front().first >= lastBestRate && highscore->front().first - lastBestRate < differnce);
		
		if (result)
		{
			counter++;
			result = counter >= count;
		}
		else
			counter = 0;

		if (enableDebugOutput)
		{
			if (result)
				std::cout << "rateDifferenceCondition is true: " << std::fixed << std::setprecision(7) << lastBestRate << " - " << std::fixed << std::setprecision(7) << highscore->front().first << " < " << std::fixed << std::setprecision(7) << differnce << std::endl;
			else
				std::cout << "rateDifferenceCondition is false: " << std::fixed << std::setprecision(7) << lastBestRate << " - " << std::fixed << std::setprecision(7) << highscore->front().first << " > " << std::fixed << std::setprecision(7) << differnce << std::endl;
		}

		lastBestRate = highscore->front().first;
		return result;
	} else {
		lastBestRate = highscore->front().first;
		return false;
	}
}


RateDifferenceCondition::RateDifferenceCondition(double differnce_, int count_, bool enableDebugOutput_)
	: AbstractExitCondition(enableDebugOutput_)
{
	differnce = differnce_;
	lastBestRate = -1;
	counter = 0;
	count = count_;
}

void RateDifferenceCondition::setCount(int newCount)
{
	count = newCount;
}
