#pragma once

#ifndef _ABSTRACTCREATIONCOMMAND_H_
#define _ABSTRACTCREATIONCOMMAND_H_

// Includes
#include "AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionWorld;

	// Describes an command which creates a bunch of new evolution objects
	class AbstractCreationCommand : public AbstractCommand
	{
	protected:
	public:
		virtual ~AbstractCreationCommand() {};
		// This method should create the wished count of objects inside the given world
		virtual void execute(AbstractEvolutionWorld& world, std::vector<AbstractEvolutionObject*>* notUsedObjects) = 0;
	};
}

#endif
