// Includes
#include "Learning/Evolution/StandardDeviationFitnessFunction.hpp"
// Library includes
#include <stdexcept>
#include <math.h>

namespace LightBulb
{
	StandardDeviationFitnessFunction::StandardDeviationFitnessFunction(double deviationFac_)
	{
		deviationFac = deviationFac_;
	}

	void StandardDeviationFitnessFunction::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		double average = 0;

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			average += entry->first;
		}

		average /= highscore.size();

		double standardDeviation = 0;

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			standardDeviation += pow(entry->first - average, 2.0);
		}

		standardDeviation /= highscore.size();
		standardDeviation = sqrt(standardDeviation);

		if (average < deviationFac * standardDeviation)
			throw std::logic_error("Your chosen deviationFac is too big");

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			entry->first = entry->first - (average - deviationFac * standardDeviation);
		}
	}

	AbstractFitnessFunction* StandardDeviationFitnessFunction::clone() const
	{
		return new StandardDeviationFitnessFunction(*this);
	}
}
