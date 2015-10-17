// Includes
#include "Learning/Evolution/ConstantCreationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"


ConstantCreationCommand::ConstantCreationCommand(int objectCount_, bool enableDebugOutput_)
	: AbstractCreationCommand(enableDebugOutput_)
{
	objectCount = objectCount_;
}

void ConstantCreationCommand::execute(AbstractEvolutionWorld& world)
{
	int objectsToCreate = objectCount - world.getEvolutionObjects()->size();
	for (int i = 0; i < objectsToCreate; i++)
	{
		world.addNewObject();
	}
}

void ConstantCreationCommand::setObjectCount(int newObjectCount)
{
	objectCount = newObjectCount;
}
