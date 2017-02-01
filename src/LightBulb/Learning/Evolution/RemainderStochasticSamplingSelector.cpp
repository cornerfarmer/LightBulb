// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/RemainderStochasticSamplingSelector.hpp"
#include "LightBulb/Function/SelectionFunction/RouletteWheelSelectionFunction.hpp"
//Library includes
#include <algorithm>

namespace LightBulb
{
	void RemainderStochasticSamplingSelector::select(bool recombination, int individualCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		double totalFitness = 0;

		// Go through all not selected individuals
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			totalFitness += entry->first;
		}

		std::vector<double> secondChance;

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			int selectionCount = entry->first / totalFitness * individualCount;
			for (int i = 0; i < selectionCount; i++)
			{
				if (recombination)
					addIndividualToRecombination(*entry->second);
				else
					addIndividualToMutate(*entry->second);
			}
			if (withReplacement) {
				if (totalFitness != 0)
				{
					secondChance.push_back(entry->first / totalFitness * individualCount - selectionCount);
				}
				else
				{
					secondChance.push_back(0);
				}
			}
			else
				secondChance.push_back(entry->first);
		}

		while ((recombination && getRecombinationSelection().size() < individualCount) || (!recombination && getMutationSelection().size() < individualCount))
		{
			if (recombination)
				addIndividualToRecombination(*highscore[selectionFunction->execute(secondChance)].second);
			else
				addIndividualToMutate(*highscore[selectionFunction->execute(secondChance)].second);
		}
	}

	void RemainderStochasticSamplingSelector::selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		select(false, mutationCount, highscore);
	}

	void RemainderStochasticSamplingSelector::selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		select(true, recombinationCount * 2, highscore);
		random_shuffle(getRecombinationSelection().begin(), getRecombinationSelection().end());
	}

	RemainderStochasticSamplingSelector::RemainderStochasticSamplingSelector(bool withReplacement_, AbstractSelectionFunction* selectionFunction_)
	{
		withReplacement = withReplacement_;
		selectionFunction.reset(selectionFunction_ ? selectionFunction_ : new RouletteWheelSelectionFunction());
	}

	RemainderStochasticSamplingSelector::RemainderStochasticSamplingSelector(const RemainderStochasticSamplingSelector& other)
		:AbstractMutationSelector(other), AbstractRecombinationSelector(other)
	{
		withReplacement = other.withReplacement;
		selectionFunction.reset(dynamic_cast<AbstractSelectionFunction*>(other.selectionFunction->clone()));
	}

	RemainderStochasticSamplingSelector::RemainderStochasticSamplingSelector(RemainderStochasticSamplingSelector&& other) noexcept
		: RemainderStochasticSamplingSelector()
	{
		swap(*this, other);
	}

	RemainderStochasticSamplingSelector& RemainderStochasticSamplingSelector::operator=(RemainderStochasticSamplingSelector other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(RemainderStochasticSamplingSelector& lhs, RemainderStochasticSamplingSelector& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractMutationSelector&>(lhs), static_cast<AbstractMutationSelector&>(rhs));
		swap(static_cast<AbstractRecombinationSelector&>(lhs), static_cast<AbstractRecombinationSelector&>(rhs));
		swap(lhs.selectionFunction, rhs.selectionFunction);
		swap(lhs.withReplacement, rhs.withReplacement);
	}

	void RemainderStochasticSamplingSelector::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		selectionFunction->setRandomGenerator(randomGenerator_);
	}

	AbstractCloneable* RemainderStochasticSamplingSelector::clone() const
	{
		return new RemainderStochasticSamplingSelector(*this);
	}
}