// Includes
#include "Learning/Evolution/ConstantCreationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

namespace LightBulb
{
	ConstantCreationCommand::ConstantCreationCommand(int objectCount_)
		: AbstractCreationCommand()
	{
		objectCount = objectCount_;
	}

	void ConstantCreationCommand::execute(AbstractEvolutionWorld& world, std::vector<AbstractEvolutionObject*>& notUsedObjects)
	{
		// Calculate the amount of objects we have to create
		int objectsToCreate = objectCount - world.getPopulationSize();
		// Create them
		for (int i = 0; i < objectsToCreate; i++)
		{
			std::unique_ptr<AbstractEvolutionObject> newObject(world.addNewObject(false));

			AbstractEvolutionObject* objectToAdd = getUnusedObject(*newObject.get(), notUsedObjects, false);
			objectToAdd->setEvolutionSource(Creation);

			world.addExistingObject(objectToAdd);
		}
	}

	AbstractCloneable* ConstantCreationCommand::clone() const
	{
		return new ConstantCreationCommand(*this);
	}

}