// Includes
#include "Learning\ConstantCreationCommand.hpp"
#include "Learning\EvolutionWorldInterface.hpp"


ConstantCreationCommand::ConstantCreationCommand(int objectCount_)
{
	objectCount = objectCount_;
}

void ConstantCreationCommand::execute(EvolutionWorldInterface& world)
{
	for (int i = 0; i < objectCount - world.getEvolutionObjectCount(); i++)
	{
		world.addNewObject();
	}
}