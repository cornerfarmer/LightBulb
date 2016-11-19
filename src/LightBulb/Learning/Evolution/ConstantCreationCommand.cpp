// Includes
#include "Learning/Evolution/ConstantCreationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

namespace LightBulb
{
	ConstantCreationCommand::ConstantCreationCommand(int individualCount_)
		: AbstractCreationCommand()
	{
		individualCount = individualCount_;
	}

	void ConstantCreationCommand::execute(AbstractEvolutionWorld& world, std::vector<AbstractIndividual*>& notUsedIndividuals)
	{
		// Calculate the amount of individuals we have to create
		int individualsToCreate = individualCount - world.getPopulationSize();
		// Create them
		for (int i = 0; i < individualsToCreate; i++)
		{
			std::unique_ptr<AbstractIndividual> newIndividual(world.addNewIndividual(false));

			AbstractIndividual* individualToAdd = getUnusedIndividual(*newIndividual.get(), notUsedIndividuals, false);
			individualToAdd->setEvolutionSource(Creation);

			world.addExistingIndividual(individualToAdd);
		}
	}

	AbstractCloneable* ConstantCreationCommand::clone() const
	{
		return new ConstantCreationCommand(*this);
	}

}