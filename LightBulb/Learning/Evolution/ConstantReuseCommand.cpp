// Includes
#include "Learning/Evolution/ConstantReuseCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes

namespace LightBulb
{
	ConstantReuseCommand::ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, int objectCount_)
		: AbstractReuseCommand(reuseSelector_)
	{
		setReuseCount(objectCount_);
	}

	ConstantReuseCommand::ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, double reusePercentage_)
		: AbstractReuseCommand(reuseSelector_)
	{
		setReusePercentage(reusePercentage_);
	}

	void ConstantReuseCommand::select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter)
	{
		int objectCount = this->objectCount;
		// Calculate a temporary static object count if the percentage value is used
		if (objectCount == 0)
			objectCount = (int)(highscore.size() * reusePercentage);

		reuseSelector->executeReuseSelection(objectCount, highscore, counter);
	}

	void ConstantReuseCommand::setReusePercentage(double newReusePercentage)
	{
		objectCount = 0;
		reusePercentage = newReusePercentage;
	}

	void ConstantReuseCommand::setReuseCount(double newReuseCount)
	{
		reusePercentage = 0;
		objectCount = newReuseCount;
	}
}