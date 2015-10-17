#pragma once

#ifndef _ABSTRACTCREATIONCOMMAND_H_
#define _ABSTRACTCREATIONCOMMAND_H_

// Library Includes

// Forward declarations

class AbstractEvolutionWorld;

class AbstractCreationCommand
{
protected:
	bool enableDebugOutput;
public:
	AbstractCreationCommand(bool enableDebugOutput_);
	virtual void execute(AbstractEvolutionWorld& world) = 0;
};

#endif
