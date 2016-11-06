// Includes
#include <Learning/Evolution/StochasticUniversalSamplingSelector.hpp>
#include <Function/SelectionFunction/RouletteWheelSelectionFunction.hpp>
//Library includes
#include <algorithm>

namespace LightBulb
{
	void StochasticUniversalSamplingSelector::select(bool recombine, int objectCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		std::vector<double> probabilities;
		probabilities.reserve(highscore.size());

		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			probabilities.push_back(entry->first);
		}

		std::vector<int> selectedIndices = randomFunction->execute(probabilities, objectCount);
		int mutationSequenceIndex = 0;
		for (auto selectedIndex = selectedIndices.begin(); selectedIndex != selectedIndices.end(); selectedIndex++, mutationSequenceIndex++)
		{
			if (recombine)
				addObjectToRecombination(*highscore[*selectedIndex].second);
			else
				addObjectToMutate(*highscore[*selectedIndex].second);
		}
	}

	void StochasticUniversalSamplingSelector::selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		select(false, mutationCount, highscore);
	}

	void StochasticUniversalSamplingSelector::selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		select(true, recombinationCount * 2, highscore);
		random_shuffle(getRecombinationSelection().begin(), getRecombinationSelection().end());
	}


	StochasticUniversalSamplingSelector::StochasticUniversalSamplingSelector()
	{
		setRandomFunction(new RouletteWheelSelectionFunction());
	}

	StochasticUniversalSamplingSelector::StochasticUniversalSamplingSelector(const StochasticUniversalSamplingSelector& other)
		:AbstractMutationSelector(other), AbstractRecombinationSelector(other)
	{
		randomFunction.reset(dynamic_cast<AbstractSelectionFunction*>(other.randomFunction->clone()));
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
		swap(lhs.randomFunction, rhs.randomFunction);
	}
	
	void StochasticUniversalSamplingSelector::setRandomFunction(AbstractSelectionFunction* randomFunction_)
	{
		randomFunction.reset(randomFunction_);
	}


	void StochasticUniversalSamplingSelector::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		randomFunction->setRandomGenerator(randomGenerator_);
	}

	AbstractCloneable* StochasticUniversalSamplingSelector::clone() const
	{
		return new StochasticUniversalSamplingSelector(*this);
	}
}
