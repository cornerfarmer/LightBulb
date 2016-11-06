// Includes
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
#include <Function/SelectionFunction/RouletteWheelSelectionFunction.hpp>
//Library includes
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

namespace LightBulb
{
	void RemainderStochasticSamplingSelector::select(bool recombination, int objectCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		double totalFitness = 0;

		// Go through all not selected objects
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			totalFitness += entry->first;
		}

		std::vector<double> secondChance;

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			int selectionCount = entry->first / totalFitness * objectCount;
			for (int i = 0; i < selectionCount; i++)
			{
				if (recombination)
					addObjectToRecombination(*entry->second);
				else
					addObjectToMutate(*entry->second);
			}
			if (withReplacement) {
				if (totalFitness != 0)
				{
					secondChance.push_back(entry->first / totalFitness * objectCount - selectionCount);
				}
				else
				{
					secondChance.push_back(0);
				}
			}
			else
				secondChance.push_back(entry->first);
		}

		while ((recombination && getRecombinationSelection().size() < objectCount) || (!recombination && getMutationSelection().size() < objectCount))
		{
			if (recombination)
				addObjectToRecombination(*highscore[randomFunction->execute(secondChance)].second);
			else
				addObjectToMutate(*highscore[randomFunction->execute(secondChance)].second);
		}
	}

	void RemainderStochasticSamplingSelector::selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		select(false, mutationCount, highscore);
	}

	void RemainderStochasticSamplingSelector::selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		select(true, recombinationCount * 2, highscore);
		random_shuffle(getRecombinationSelection().begin(), getRecombinationSelection().end());
	}

	RemainderStochasticSamplingSelector::RemainderStochasticSamplingSelector(bool withReplacement_)
	{
		withReplacement = withReplacement_;
		setRandomFunction(new RouletteWheelSelectionFunction());
	}

	RemainderStochasticSamplingSelector::RemainderStochasticSamplingSelector(const RemainderStochasticSamplingSelector& other)
		:AbstractMutationSelector(other), AbstractRecombinationSelector(other)
	{
		withReplacement = other.withReplacement;
		randomFunction.reset(dynamic_cast<AbstractSelectionFunction*>(other.randomFunction->clone()));
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
		swap(lhs.randomFunction, rhs.randomFunction);
		swap(lhs.withReplacement, rhs.withReplacement);
	}

	void RemainderStochasticSamplingSelector::setRandomFunction(AbstractSelectionFunction* randomFunction_)
	{
		randomFunction.reset(randomFunction_);
	}

	void RemainderStochasticSamplingSelector::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		randomFunction->setRandomGenerator(randomGenerator_);
	}

	AbstractCloneable* RemainderStochasticSamplingSelector::clone() const
	{
		return new RemainderStochasticSamplingSelector(*this);
	}
}