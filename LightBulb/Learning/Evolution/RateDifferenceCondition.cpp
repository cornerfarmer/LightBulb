// Includes
#include "Learning/Evolution/RateDifferenceCondition.hpp"
// Library includes
#include <iostream>
#include <iomanip>

bool RateDifferenceCondition::evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	if (lastBestRate != -1) {
		// Determine if the difference between the current score and the last one is lower then the allowed difference
		bool result = (highscore->front().first >= lastBestRate && highscore->front().first - lastBestRate < difference);
		
		// If the difference is to small increase the counter
		if (result)
		{
			counter++;
			// Only set the result to true if the counter is high enough
			result = counter >= count;
		}
		else
			counter = 0;

		if (enableDebugOutput)
		{
			if (result)
				std::cout << "rateDifferenceCondition is true: " << std::fixed << std::setprecision(7) << lastBestRate << " - " << std::fixed << std::setprecision(7) << highscore->front().first << " < " << std::fixed << std::setprecision(7) << difference << std::endl;
			else
				std::cout << "rateDifferenceCondition is false: " << std::fixed << std::setprecision(7) << lastBestRate << " - " << std::fixed << std::setprecision(7) << highscore->front().first << " > " << std::fixed << std::setprecision(7) << difference << std::endl;
		}

		// Remember the best score for the next generation
		lastBestRate = highscore->front().first;
		return result;
	} else {
		// Remember the best score for the next generation
		lastBestRate = highscore->front().first;
		return false;
	}
}


RateDifferenceCondition::RateDifferenceCondition(double difference_, int count_, bool enableDebugOutput_)
	: AbstractExitCondition(enableDebugOutput_)
{
	difference = difference_;
	lastBestRate = -1;
	counter = 0;
	count = count_;
}

void RateDifferenceCondition::setCount(int newCount)
{
	count = newCount;
}
