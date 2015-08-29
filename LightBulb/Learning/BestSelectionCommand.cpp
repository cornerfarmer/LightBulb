// Includes
#include "Learning\BestSelectionCommand.hpp"
#include "Learning\EvolutionWorldInterface.hpp"

BestSelectionCommand::BestSelectionCommand(int objectCount_)
{
	objectCount = objectCount_;
}

void BestSelectionCommand::execute(EvolutionWorldInterface& world)
{
	int objectsToRemove = world.getEvolutionObjectCount() - objectCount;
	for (int i = 0; i < objectsToRemove; i++)
	{
		EvolutionObjectInterface* badest = 0;
		for (int o = 0; o < world.getEvolutionObjectCount(); o++)
		{
			if (badest == 0 || world.isBetterThan(badest, world.getEvolutionObject(o)))
				badest = world.getEvolutionObject(o);
		}
		world.removeEvolutionObject(badest);
	}
}
