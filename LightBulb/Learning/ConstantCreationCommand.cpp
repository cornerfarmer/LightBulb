// Includes
#include "Learning\ConstantCreationCommand.hpp"
#include "Learning\EvolutionWorldInterface.hpp"


ConstantCreationCommand::ConstantCreationCommand(int objectCount_)
{
	objectCount = objectCount_;
}

void ConstantCreationCommand::execute(EvolutionWorldInterface& world)
{
	int objectsToCreate = objectCount - world.getEvolutionObjects()->size();
	for (int i = 0; i < objectsToCreate; i++)
	{
		world.addNewObject();
	}
}