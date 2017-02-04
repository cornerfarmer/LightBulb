// Includes
#include "LightBulb/Learning/Evolution/RandomSelector.hpp"
#include "LightBulb/Function/RandomFunction/AbstractRandomFunction.hpp"

//Library includes

namespace LightBulb
{
	void RandomSelector::selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		for (int i = 0; i < mutationCount; i++)
		{
			addIndividualToMutate(*highscore[randomFunction->execute(highscore.size())].second);
		}
	}

	void RandomSelector::selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		for (int i = 0; i < recombinationCount * 2; i++)
		{
			addIndividualToRecombination(*highscore[randomFunction->execute(highscore.size())].second);
		}
	}

	RandomSelector::RandomSelector(AbstractRandomFunction* randomFunction_)
	{
		randomFunction.reset(randomFunction_);
	}

	RandomSelector::RandomSelector(const RandomSelector& other)
		:AbstractMutationSelector(other),AbstractRecombinationSelector(other)
	{
		randomFunction.reset(dynamic_cast<AbstractRandomFunction*>(other.randomFunction->clone()));
	}

	RandomSelector::RandomSelector(RandomSelector&& other) noexcept
		: RandomSelector()
	{
		swap(*this, other);
	}

	RandomSelector& RandomSelector::operator=(RandomSelector other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(RandomSelector& lhs, RandomSelector& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractMutationSelector&>(lhs), static_cast<AbstractMutationSelector&>(rhs));
		swap(static_cast<AbstractRecombinationSelector&>(lhs), static_cast<AbstractRecombinationSelector&>(rhs));
		swap(lhs.randomFunction, rhs.randomFunction);
	}

	void RandomSelector::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		randomFunction->setRandomGenerator(randomGenerator_);
	}

	AbstractCloneable* RandomSelector::clone() const
	{
		return new RandomSelector(*this);
	}
}
