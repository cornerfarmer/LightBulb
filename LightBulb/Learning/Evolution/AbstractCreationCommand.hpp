#pragma once

#ifndef _ABSTRACTCREATIONCOMMAND_H_
#define _ABSTRACTCREATIONCOMMAND_H_

// Library Includes

// Forward declarations

class AbstractEvolutionWorld;

// Describes an command which creates a bunch of new evolution objects
class AbstractCreationCommand
{
protected:
	bool enableDebugOutput;
public:
	virtual ~AbstractCreationCommand() {};
	AbstractCreationCommand(bool enableDebugOutput_);
	// This method should create the wished count of objects inside the given world
	virtual void execute(AbstractEvolutionWorld& world) = 0;
};

#endif
