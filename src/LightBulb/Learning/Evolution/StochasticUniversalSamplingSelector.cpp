// Includes
#include "LightBulb/Learning/Evolution/StochasticUniversalSamplingSelector.hpp"
#include "LightBulb/Function/SelectionFunction/RouletteWheelSelectionFunction.hpp"
//Library includes
#include <algorithm>

namespace LightBulb
{
	void StochasticUniversalSamplingSelector::select(bool recombine, int individualCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		std::vector<double> probabilities;
		probabilities.reserve(highscore.size());

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			probabilities.push_back(entry->first);
		}

		std::vector<int> selectedIndices = selectionFunction->execute(probabilities, individualCount);
		int mutationSequenceIndex = 0;
		for (auto selectedIndex = selectedIndices.begin(); selectedIndex != selectedIndices.end(); selectedIndex++, mutationSequenceIndex++)
		{
			if (recombine)
				addIndividualToRecombination(*highscore[*selectedIndex].second);
			else
				addIndividualToMutate(*highscore[*selectedIndex].second);
		}
	}

	void StochasticUniversalSamplingSelector::selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		select(false, mutationCount, highscore);
	}

	void StochasticUniversalSamplingSelector::selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		select(true, recombinationCount * 2, highscore);
		random_shuffle(getRecombinationSelection().begin(), getRecombinationSelection().end());
	}


	StochasticUniversalSamplingSelector::StochasticUniversalSamplingSelector(AbstractSelectionFunction* selectionFunction_)
	{
		selectionFunction.reset(selectionFunction_ ? selectionFunction_ : new RouletteWheelSelectionFunction());
	}

	StochasticUniversalSamplingSelector::StochasticUniversalSamplingSelector(const StochasticUniversalSamplingSelector& other)
		:AbstractMutationSelector(other), AbstractRecombinationSelector(other)
	{
		selectionFunction.reset(dynamic_cast<AbstractSelectionFunction*>(other.selectionFunction->clone()));
	}

	StochasticUniversalSamplingSelector::StochasticUniversalSamplingSelector(StochasticUniversalSamplingSelector&& other) noexcept
		: StochasticUniversalSamplingSelector()
	{
		swap(*this, other);
	}

	StochasticUniversalSamplingSelector& StochasticUniversalSamplingSelector::operator=(StochasticUniversalSamplingSelector other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(StochasticUniversalSamplingSelector& lhs, StochasticUniversalSamplingSelector& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractMutationSelector&>(lhs), static_cast<AbstractMutationSelector&>(rhs));
		swap(static_cast<AbstractRecombinationSelector&>(lhs), static_cast<AbstractRecombinationSelector&>(rhs));
		swap(lhs.selectionFunction, rhs.selectionFunction);
	}

	void StochasticUniversalSamplingSelector::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		selectionFunction->setRandomGenerator(randomGenerator_);
	}

	AbstractCloneable* StochasticUniversalSamplingSelector::clone() const
	{
		return new StochasticUniversalSamplingSelector(*this);
	}
}
