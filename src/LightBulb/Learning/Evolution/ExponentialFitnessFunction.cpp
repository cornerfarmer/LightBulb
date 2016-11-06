// Includes
#include "Learning/Evolution/ExponentialFitnessFunction.hpp"
// Library includes
#include <stdexcept>
#include <math.h>

namespace LightBulb
{
	ExponentialFitnessFunction::ExponentialFitnessFunction(double exponent_, double proportionalScaling_, double base_)
	{
		if (proportionalScaling < 0)
			throw std::invalid_argument("ProportionalScaling has to be positive!");
		exponent = exponent_;
		proportionalScaling = proportionalScaling_;
		base = base_;
	}

	void ExponentialFitnessFunction::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			entry->first = pow(entry->first * proportionalScaling + base, exponent);
		}
	}

	AbstractFitnessFunction* ExponentialFitnessFunction::clone() const
	{
		return new ExponentialFitnessFunction(*this);
	}
}
