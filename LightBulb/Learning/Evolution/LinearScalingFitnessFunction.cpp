// Includes
#include "Learning/Evolution/LinearScalingFitnessFunction.hpp"
// Library includes
#include <stdexcept>
#include <algorithm>

namespace LightBulb
{
	LinearScalingFitnessFunction::LinearScalingFitnessFunction(double proportionalScaling_, double base_, bool useDynamicScaling_)
	{
		if (proportionalScaling < 0)
			throw std::invalid_argument("ProportionalScaling has to be positive!");
		proportionalScaling = proportionalScaling_;
		base = base_;
		useDynamicScaling = useDynamicScaling_;
	}

	void LinearScalingFitnessFunction::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
	{
		if (useDynamicScaling)
		{
			if (highscore->size() > 0)
				base = highscore->front().first;

			for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
			{
				base = std::min(base, entry->first);
			}
		}

		for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
		{
			entry->first = entry->first * proportionalScaling + base;
		}
	}
}
