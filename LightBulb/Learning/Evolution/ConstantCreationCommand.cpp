// Includes
#include "Learning/Evolution/ConstantCreationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>


ConstantCreationCommand::ConstantCreationCommand(int objectCount_)
	: AbstractCreationCommand()
{
	objectCount = objectCount_;
}

void ConstantCreationCommand::execute(AbstractEvolutionWorld& world, std::vector<AbstractEvolutionObject*>* notUsedObjects)
{
	// Calculate the amount of objects we have to create
	int objectsToCreate = objectCount - world.getPopulationSize();
	// Create them
	for (int i = 0; i < objectsToCreate; i++)
	{
		std::unique_ptr<AbstractEvolutionObject> newObject(world.addNewObject(false));

		world.getEvolutionObjects()->push_back(getUnusedObject(newObject.get(), notUsedObjects, false));
	}
}

void ConstantCreationCommand::setObjectCount(int newObjectCount)
{
	objectCount = newObjectCount;
}
