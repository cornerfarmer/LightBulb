// Includes
#include "Learning/Evolution/ConstantCreationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"


ConstantCreationCommand::ConstantCreationCommand(int objectCount_)
	: AbstractCreationCommand()
{
	objectCount = objectCount_;
}

void ConstantCreationCommand::execute(AbstractEvolutionWorld& world)
{
	// Calculate the amount of objects we have to create
	int objectsToCreate = objectCount - world.getPopulationSize();
	// Create them
	for (int i = 0; i < objectsToCreate; i++)
	{
		world.addNewObject();
	}
}

void ConstantCreationCommand::setObjectCount(int newObjectCount)
{
	objectCount = newObjectCount;
}
