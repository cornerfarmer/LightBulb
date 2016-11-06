// Includes
#include "Learning/Evolution/PositiveMakerFitnessFunction.hpp"
// Library includes
#include <stdexcept>
#include <algorithm>

namespace LightBulb
{
	PositiveMakerFitnessFunction::PositiveMakerFitnessFunction(double constant_)
	{
		constant = constant_;
	}

	void PositiveMakerFitnessFunction::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		//double minFitness = highscore->back().first;

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			entry->first = std::max(0.0, entry->first + constant);
		}

	}

	AbstractFitnessFunction* PositiveMakerFitnessFunction::clone() const
	{
		return new PositiveMakerFitnessFunction(*this);
	}
}
