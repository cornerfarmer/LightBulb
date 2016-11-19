// Includes
#include "Learning/Evolution/PerfectIndividualFoundCondition.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
// Library includes
#include <iostream>
#include <iomanip>
#include "EvolutionLearningRule.hpp"
#include "AbstractCoevolutionEnvironment.hpp"

namespace LightBulb
{
	bool PerfectIndividualFoundCondition::evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule)
	{
		if (highscore.size() > 0)
		{
			const AbstractCoevolutionEnvironment& coevolutionEnvironment = static_cast<const AbstractCoevolutionEnvironment&>(static_cast<const EvolutionLearningRule&>(learningRule).getEnvironment());
			if (coevolutionEnvironment.isParasiteEnvironment() && perfectIndividualExists(coevolutionEnvironment.getCombiningStrategy()))
			{
				counter++;
				if (counter >= count)
					return true;
			}
			else
			{
				counter = 0;
			}
			return false;
		}
		else
		{
			return false;
		}
	}

	AbstractCloneable* PerfectIndividualFoundCondition::clone() const
	{
		return new PerfectIndividualFoundCondition(*this);
	}

	bool PerfectIndividualFoundCondition::perfectIndividualExists(const AbstractCombiningStrategy& combiningStrategy) const
	{
		auto results = combiningStrategy.getPrevResults();
		std::map<AbstractIndividual*, bool> defeatedIndividuals;

		for (auto resultsPerIndividual = results.begin(); resultsPerIndividual != results.end(); resultsPerIndividual++)
		{
			for (auto resultsPerCombination = resultsPerIndividual->second.begin(); resultsPerCombination != resultsPerIndividual->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					defeatedIndividuals[resultsPerCombination->first] |= result->second;
				}
			}
		}

		for (auto defeatedIndividual = defeatedIndividuals.begin(); defeatedIndividual != defeatedIndividuals.end(); defeatedIndividual++)
		{
			if (!defeatedIndividual->second)
				return true;
		}
		return false;
	}

	PerfectIndividualFoundCondition::PerfectIndividualFoundCondition(int count_)
		: AbstractExitCondition()
	{
		counter = 0;
		count = count_;
	}

}