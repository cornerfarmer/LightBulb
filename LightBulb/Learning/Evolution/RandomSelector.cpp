// Includes
#include <Learning/Evolution/RandomSelector.hpp>
//Library includes

namespace LightBulb
{
	void RandomSelector::selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		for (int i = 0; i < mutationCount; i++)
		{
			addObjectToMutate(*highscore[randomFunction->execute(highscore.size())].second);
		}
	}

	void RandomSelector::selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		for (int i = 0; i < recombinationCount * 2; i++)
		{
			addObjectToRecombination(*highscore[randomFunction->execute(highscore.size())].second);
		}
	}

	RandomSelector::RandomSelector(AbstractRandomFunction* randomFunction_)
	{
		randomFunction.reset(randomFunction_);
	}

	void RandomSelector::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		randomFunction->setRandomGenerator(randomGenerator_);
	}
}