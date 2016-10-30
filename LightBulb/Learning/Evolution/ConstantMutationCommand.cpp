// Includes
#include "Learning/Evolution/ConstantMutationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes

namespace LightBulb
{
	ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, int objectCount_)
		: AbstractMutationCommand(mutationAlgorithm_, mutationSelector_)
	{
		setMutationCount(objectCount_);
	}

	ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, double mutationPercentage_)
		: AbstractMutationCommand(mutationAlgorithm_, mutationSelector_)
	{
		setMutationPercentage(mutationPercentage_);
	}


	void ConstantMutationCommand::select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter)
	{
		int objectCount = this->objectCount;
		// Calculate a temporary static object count if the percentage value is used
		if (objectCount == 0)
			objectCount = (int)(highscore.size() * mutationPercentage);

		mutationSelector->executeMutationSelection(objectCount, highscore, counter);

		mutationAlgorithm->initialize(highscore);
	}

	AbstractCloneable* ConstantMutationCommand::clone() const
	{
		return new ConstantMutationCommand(*this);
	}

	void ConstantMutationCommand::setMutationPercentage(double newMutationPercentage)
	{
		objectCount = 0;
		mutationPercentage = newMutationPercentage;
	}

	void ConstantMutationCommand::setMutationCount(double newMutationCount)
	{
		mutationPercentage = 0;
		objectCount = newMutationCount;
	}
}