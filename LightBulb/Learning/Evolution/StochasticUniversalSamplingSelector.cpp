// Includes
#include <Learning/Evolution/StochasticUniversalSamplingSelector.hpp>
#include <Function/SelectionFunction/RouletteWheelSelectionFunction.hpp>
//Library includes
#include <algorithm>

namespace LightBulb
{
	void StochasticUniversalSamplingSelector::select(bool recombine, int objectCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
	{
		std::vector<double> probabilities;
		probabilities.reserve(highscore->size());

		for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
		{
			probabilities.push_back(entry->first);
		}

		std::vector<int> selectedIndices = randomFunction->execute(probabilities, objectCount);
		int mutationSequenceIndex = 0;
		for (auto selectedIndex = selectedIndices.begin(); selectedIndex != selectedIndices.end(); selectedIndex++, mutationSequenceIndex++)
		{
			if (recombine)
				addObjectToRecombination((*highscore)[*selectedIndex].second);
			else
				addObjectToMutate((*highscore)[*selectedIndex].second);
		}
	}

	void StochasticUniversalSamplingSelector::selectForMutation(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
	{
		select(false, mutationCount, highscore);
	}

	void StochasticUniversalSamplingSelector::selectForRecombination(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
	{
		select(true, recombinationCount * 2, highscore);
		std::random_shuffle(getRecombinationSelection()->begin(), getRecombinationSelection()->end());
	}


	StochasticUniversalSamplingSelector::StochasticUniversalSamplingSelector()
	{
		setRandomFunction(new RouletteWheelSelectionFunction());
	}

	void StochasticUniversalSamplingSelector::setRandomFunction(AbstractSelectionFunction* randomFunction_)
	{
		randomFunction.reset(randomFunction_);
	}


	void StochasticUniversalSamplingSelector::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		randomFunction->setRandomGenerator(*AbstractMutationSelector::randomGenerator);
	}
}